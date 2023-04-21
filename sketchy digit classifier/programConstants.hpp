#pragma once
#include <string>
#include <fstream>
using namespace std;

// PROGRAM CONSTANTS
string
imgs1fn = "train-images-idx3-ubyte.dat",
imgs2fn = "t10k-images-idx3-ubyte.dat",
labels1fn = "train-labels-idx1-ubyte.dat",
labels2fn = "t10k-labels-idx1-ubyte.dat";
ifstream
imgsFile1(imgs1fn, ios::in | ios::binary),
imgsFile2(imgs2fn, ios::in | ios::binary),
labelsFile1(labels1fn, ios::in | ios::binary),
labelsFile2(labels2fn, ios::in | ios::binary);
const int batchSize = 64;
double learnRate = 0.05;