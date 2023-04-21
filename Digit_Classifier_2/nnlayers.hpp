#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;
#define uchar unsigned char

class Layer
{
	double* dat = nullptr;
	Layer* prevLayer = nullptr, *nextLayer = nullptr;
	int len = 0;
public:
	Layer(int length, double* dat)
	{
		len = length;
	}
	double* getDat() { return dat; }
	double* setDat(double* nd) { dat = nd; }
	Layer* getNext() { return nextLayer; }

	int getLen() { return len; }
	void setLen(int nl) { len = nl; }

	virtual string getType() = 0;

	virtual void forward_prop() = 0;

	virtual void back_prop() = 0;
};

class InputLayer : public Layer
{
public:
	InputLayer(int len, double* dat) : Layer(len, dat) { }
	string getType() { return "Input"; }
	void back_prop() { return; };
};

class Img_28x28 : public InputLayer
{
public:
	Img_28x28(double imgdat[28][28]) : InputLayer(28 * 28, *imgdat) { }
	string getType() { return "Img_28x28"; }
	void forward_prop();
};

class HiddenLayer : public Layer
{
public:
	string getType() { return "Hidden"; }
};

class FCLayer : public HiddenLayer
{
	double* weights = nullptr, *biases = nullptr;
public:
	FCLayer(const int numUnits)
	{

	}

	string getType() { return "FC"; }
};

// Implementation for pooling layers later...
class PoolingLayer : public HiddenLayer
{
public:
	string getType() { return "Pooling"; }

};

class MaxPoolingLayer : public PoolingLayer
{
public:
	string getType() { return "Pooling Max"; }

};

class AvgPoolingLayer : public PoolingLayer
{
public:
	string getType() { return "Pooling Avg"; }

};

class OutputLayer : public Layer
{
public:

};

inline void Img_28x28::forward_prop()
{
	// TODO
	double* dat = getDat();
	Layer* nextLayer = getNext();
	double* nextDat = nextLayer->getDat();
	std::stringstream ss(nextLayer->getType());
	string nextType; ss >> nextType;
	if (nextType == "FC")
	{
		FCLayer* fcl = (FCLayer*)nextLayer;
		// TODO
	}
	else
	{
		cout << "Warning: No suitable forward feed algorithm from Img_28x28 to " << nextType << " was found.\n";
	}
	return;
}