#pragma GCC optimize("O2","unroll-loops")
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
		/*if (imgID % 3700 == 0)
		{
			imgs2[imgID].display();
			printf("network answer: %d\n", netAns);
		}*/
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
			learnRate /= 1.00002;
			learnRate = max(learnRate, 0.0008);
		}
		evaluate_model();
	}
	printf("Training finished\n");
}
int main()
{
	ios_base::sync_with_stdio(false);

	//getting ready
	input_data();
	printf("Metas (# of training images, # of testing images, rows of pixels per image, columns of pixels per image): \n%d, %d, %d, %d\n", numImg1, numImg2, prows, pcols); //display metas

	//start the stuff
	model = FCNN({ 450, 450, 10 }, 28 * 28);
	train_stochastic(3);
}