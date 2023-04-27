#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <winsock.h>
#include "programConstants.hpp"
#include "nnkit.hpp"
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

#define uchar unsigned char

// DATA READ FROM FILES
int numImg1, numImg2, prows, pcols;
img_28x28 imgs1[60000], imgs2[10000];

int next_int(ifstream& st)
{
	int in; st.read((char*)(&in), sizeof(in));
	return ntohl(in);
}
int next_byte(ifstream& st)
{
	uchar in; st.read((char*)(&in), 1);
	return in;
}
img_28x28 read_img(ifstream& st)
{
	img_28x28 curr;
	for (int i = 0; i < prows; ++i)
		for (int j = 0; j < pcols; ++j)
			curr.pixels[i][j] = next_byte(st);
	return curr;
}
void read_imgs()
{
	for (int i = 0; i < numImg1; ++i)
		imgs1[i] = read_img(imgsFile1), 
		imgs1[i].label = next_byte(labelsFile1);
	for (int i = 0; i < numImg2; ++i)
		imgs2[i] = read_img(imgsFile2),
		imgs2[i].label = next_byte(labelsFile2);
}
void input_data()
{
	printf("reading data...\n");
	next_int(imgsFile1); next_int(imgsFile2); //flush magic number

	numImg1 = next_int(imgsFile1),
		numImg2 = next_int(imgsFile2),
		prows = next_int(imgsFile1),
		pcols = next_int(imgsFile1); //read in metas
	next_int(imgsFile2), next_int(imgsFile2); //flush
	next_int(labelsFile1), next_int(labelsFile1),
		next_int(labelsFile2), next_int(labelsFile2); // more flush
	read_imgs();
	printf(" finished\n");
}

// PROGRAM DATA
FCNN model;


void evaluate_model()
{
	printf("\nEvaluating model...\n");

	int numCorrect = 0;
	for (int imgID = 0; imgID < numImg2; imgID++)
	{
		vector<double> output = model.forward_prop(imgs2[imgID]);
		double hc = -1; int netAns = -1, ans = int(imgs2[imgID].label);
		for (int i = 0; i < output.size(); i++)
		{
			if (hc < output[i])
				hc = output[i], netAns = i;
		}
		if (imgID % 3700 == 0)
		{
			imgs2[imgID].display();
			printf("network answer: %d\n", netAns);
		}
		if (netAns == ans) numCorrect++;
	}

	printf("Accurracy: %.4f\n\n", (double)numCorrect / numImg2);
}


void train_stochastic(int epochs)
{
	//evaluate_model();
	printf("Training...\n");
	for(int epoch = 0; epoch < epochs; epoch++)
	{
		printf("EPOCH: %d\n", epoch);
		int trainIID = 0, interval = 3000; double approxAcc = 0;
		while (trainIID < numImg1)
		{
			//test image
			if (trainIID == numImg1) break;
			vector<double> output = model.forward_prop(imgs1[trainIID]);
			vector<double> dEdO = vector<double>(10);
			int ans = int(imgs1[trainIID].label), netAns = -1; double maxCertainty = 0;
			for (int i = 0; i < 10; ++i)
			{
				if (maxCertainty < output[i])
					maxCertainty = output[i], netAns = i;
				if (i == ans)
				{
					dEdO[i] = (output[i] - 1);
				}
				else
				{
					dEdO[i] = output[i];
				}
			}
			model.backward_prop(dEdO, imgs1[trainIID]);
			model.updateWB(learnRate);
			trainIID++;
			if (netAns == ans) approxAcc += 1.0;
			if (trainIID % interval == 0)
			{
				approxAcc /= interval;
				printf("%18s%d/%d\n", "progress: ", trainIID, numImg1);
				printf("%18s%.6f\n", "learning rate: ", learnRate);
				printf("%18s%.2f%%\n\n", "approx. accuracy: ", approxAcc * 100);
				//cout << "ex. label: \t\t" << int(imgs1[trainIID].label) << '\n';
				//cout << "ex. predicted: \t" << netAns << "\n\n";
				approxAcc = 0.0;
			}
		}
		evaluate_model();
	}
	printf("Training finished\n");
}

void write_vector1D(vector<double>& v, ofstream& file)
{
	file << '\n';
	for (double d : v) file << d << '\n';
	file << '\n';
}

void write_vector2D(vector<vector<double>>& v, ofstream& file)
{
	file << '\n';
	for (vector<double> vd : v) for (double d : vd) file << d << '\n';
	file << '\n';
}

void read_vector1D(vector<double>& v, ifstream& file)
{
	for (double& d : v) file >> d;
}

void read_vector2D(vector<vector<double>>& v, ifstream& file)
{
	for (vector<double>& vd : v) for (double& d : vd) file >> d;
}

void save_model()
{
	ofstream file("model_save.txt");
	cout << "saving model...\n";
	file << model.numLayers << '\n' << model.prepared_weights << '\n';
	for (fcLayer& layer : model.layers)
	{
		file << layer.len << '\n' << layer.w[0].size() << '\n' << (int)(layer.allocated) << '\n' << layer.minW << '\n' << layer.maxW << '\n';

		write_vector1D(layer.b, file);

		write_vector2D(layer.w, file);
	}
	file.close();
	cout << "finished.\n";
}

void read_model()
{
	ifstream file("model_save.txt");
	cout << "reading model...\n";
	file >> model.numLayers >> model.prepared_weights; model.layers.resize(model.numLayers);
	for (fcLayer& layer : model.layers)
	{
		int wsize, len;
		file >> layer.len >> wsize >> layer.allocated >> layer.minW >> layer.maxW;
		len = layer.len;
		layer.A.resize(len),
			layer.dA.resize(len),
			layer.B.resize(len),
			layer.b.resize(len),
			layer.db.resize(len);

		read_vector1D(layer.b, file);

		layer.w.resize(len, vector<double>(wsize)),
			layer.dw.resize(len, vector<double>(wsize));

		read_vector2D(layer.w, file);
	}

	cout << "finished.\n";
}

string prompt(string message) { cout << message << '\n'; string in; cin >> in; return in; }

int main()
{
	ios_base::sync_with_stdio(false);

	string mode = prompt("What do you want to do?\n1. use pretrained model\n2. trained new model\n3. save readable test data\n");

	if(mode == "1")
	{
		// getting datasets ready
		input_data();
		printf("Metas (# of training images, # of testing images, rows of pixels per image, columns of pixels per image): \n%d, %d, %d, %d\n", numImg1, numImg2, prows, pcols); //display metas

		// start training
		model = FCNN({ 450, 450, 10 }, 28 * 28);
		train_stochastic(1);
		if(prompt("Do you want to save this model? ( 'y' / 'n' )") == "y") save_model();
	}
	else if(mode == "2")
	{
		// getting datasets ready
		read_model();
		while (true)
		{
			string action = prompt("What do you want to do with this model?\n\t- test accuracy ('T')\n\t- use file ('P')\n\t- quit ('Q')");
			if (action == "Q") break;
			if (action == "T")
			{
				input_data(), evaluate_model();
				continue;
			}
			if (action == "P")
			{
				cout << "to be implemented...\n";
				continue;
			}
			cout << "Invalid input. ignored...\n";
		}
	}
	else if(mode == "3")
	{
		ofstream fout("test_imgs_readable.txt");

		for (int i = 0; i < 100; i++)
		{
			fout << "{ ";
			for (int x = 0; x < 28; x++)
			{
				fout << "{";
				for (int y = 0; y < 28; y++)
				{
					fout << int(imgs2[i].pixels[x][y]) << ", ";
				}

				fout << "}";
				if (x != 27) fout << ", \n";
			}
			fout << "}\n\n";
		}
	}
}