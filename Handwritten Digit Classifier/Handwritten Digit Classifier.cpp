#include <windows.h>
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
	for (int epoch = 0; epoch < epochs; epoch++)
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
	ofstream file("model_save.bin");
	cout << "saving model...\n";
	file << model.numLayers << '\n' << model.prepared_weights << '\n';
	for (fcLayer& layer : model.layers)
	{
		file << layer.len << '\n' << layer.w[0].size() << '\n' << (int)(layer.allocated) << '\n' << layer.minW << '\n' << layer.maxW << '\n';

		write_vector1D(layer.A, file);
		write_vector1D(layer.B, file);

		write_vector1D(layer.dA, file);

		write_vector1D(layer.b, file);
		write_vector1D(layer.db, file);

		write_vector2D(layer.w, file);
		write_vector2D(layer.dw, file);
	}
	file.close();
	cout << "finished.\n";
}

void read_model()
{
	ifstream file("model_save.bin");
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

		read_vector1D(layer.A, file);
		read_vector1D(layer.B, file);

		read_vector1D(layer.dA, file);

		read_vector1D(layer.b, file);
		read_vector1D(layer.db, file);

		layer.w.resize(len, vector<double>(wsize)),
			layer.dw.resize(len, vector<double>(wsize));

		read_vector2D(layer.w, file);
		read_vector2D(layer.dw, file);
	}

	cout << "finished.\n";
}

string prompt(string message) { cout << message << '\n'; string in; cin >> in; return in; }

const TCHAR szAppName[] = TEXT("GridDrawing");
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {

    ios_base::sync_with_stdio(false);

    if (prompt("Do you want to use a pretrained model? ( 'y' / 'n' )") == "n")
    {
        // getting datasets ready
        input_data();
        printf("Metas (# of training images, # of testing images, rows of pixels per image, columns of pixels per image): \n%d, %d, %d, %d\n", numImg1, numImg2, prows, pcols); //display metas

        // start training
        model = FCNN({ 450, 250, 10 }, 28 * 28);
        train_stochastic(1);
        if (prompt("Do you want to save this model? ( 'y' / 'n' )") == "y") save_model();
    }
    else
    {
        // getting datasets ready
        read_model();
        while (true)
        {
            string action = prompt("What do you want to do with this model?\n\t- test accuracy ('T')\n\t- play ('P')\n\t- quit ('Q')");
            if (action == "Q") break;
            if (action == "T")
            {
                input_data(), evaluate_model();
                continue;
            }
            if (action == "P")
            {
				HWND hwnd;
				MSG msg;
				WNDCLASS wc;

				wc.style = CS_HREDRAW | CS_VREDRAW;
				wc.lpfnWndProc = WndProc;
				wc.cbClsExtra = 0;
				wc.cbWndExtra = 0;
				wc.hInstance = hInstance;
				wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
				wc.hCursor = LoadCursor(NULL, IDC_ARROW);
				wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
				wc.lpszMenuName = NULL;
				wc.lpszClassName = szAppName;

				if (!RegisterClass(&wc)) {
					MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
					return 0;
				}

				hwnd = CreateWindow(szAppName, TEXT("Grid Drawing"),
					WS_OVERLAPPEDWINDOW,
					CW_USEDEFAULT, CW_USEDEFAULT,
					CW_USEDEFAULT, CW_USEDEFAULT,
					NULL, NULL, hInstance, NULL);

				ShowWindow(hwnd, iCmdShow);
				UpdateWindow(hwnd);

				while (GetMessage(&msg, NULL, 0, 0)) {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				return msg.wParam;
                continue;
            }
            cout << "Invalid input. ignored...\n";
        }
    }

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;

    switch (message) {
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);

        GetClientRect(hwnd, &rect);
        DrawText(hdc, TEXT("Draw on this grid!"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        EndPaint(hwnd, &ps);
        return 0;
    case WM_LBUTTONDOWN:
        int xPos, yPos;
        xPos = LOWORD(lParam);
        yPos = HIWORD(lParam);

        hdc = GetDC(hwnd);
        SetPixel(hdc, xPos, yPos, RGB(0, 0, 0));
        ReleaseDC(hwnd, hdc);
        return 0;
    case WM_MOUSEMOVE:
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}