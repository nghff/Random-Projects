// Layer Classes
// below contains classes of layers used by the Nueral Network Modeling Kit (nnkit.hpp)#pragma once
#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <future>
#include <time.h>
#include <winsock.h>
#include "actfuncs.hpp"
using namespace std;

#define uchar unsigned char



class fcLayer; class img_28x28; class cLayer; class cUnit; class pUnit;

class img_28x28
{
public:
	uchar pixels[28][28];
	uchar label;
	img_28x28()
	{

	}
	void display()
	{
		for (int i = 0; i < 28; ++i)
		{
			for (int j = 0; j < 28; ++j)
				printf("%-2d", int(pixels[i][j]) / 10);
			cout << '\n';
		}
		cout << "label: " << int(label) << '\n';
	}
	void backProp(fcLayer& nextLayer);
};

class cUnit
{
public:
	int r, c;
	vector<vector<double>> pix, w, b, out;
	cUnit(int r, int c)
	{
		w.resize(3, vector<double>(3));
		b.resize(r, vector<double>(c));
		pix.resize(r, vector<double>(c));
		initWB();
	}

	void initWB();

	void fromUnit(const img_28x28& im);

	void activate();
};

class pUnit
{
public:
	int r, c;
	vector<vector<double>> pix;
	pUnit(int r, int c)
	{
		pix.resize(r, vector<double>(c));
	}

	void fromUnit(const cUnit& cu);
};

class cLayer
{
public:
	int len;
	vector<cUnit> units;
	cLayer(int len, int rows, int columns)
	{
		this->len = len;
		units = vector<cUnit>(len, cUnit(rows, columns));
	}

	void fromImg(const img_28x28& im)
	{
		for (cUnit& unit : units)
			unit.fromUnit(im);
	}
};

class pLayer
{
public:
	int len;
	vector<pUnit> units;
	pLayer(int len, int rows, int cols)
	{
		this->len = len;
		units.resize(len, pUnit(rows, cols));
	}

	void fromLayer(const cLayer& cl)
	{
		if (cl.len != len) return;
		for (int i = 0; i < len; i++)
			units[i].fromUnit(cl.units[i]);
	}
};

class fcLayer
{
public:
	int len;
	// w is the array of weights of the edges to the !PREVIOUS! layer.
	vector<double> A, B, dA, b, db; vector<vector<double>> w, dw;
	bool allocated;
	double minW, maxW;

	fcLayer() {}
	fcLayer(const int& len, const double& minW, const double& maxW) 
	{ 
		this->minW = minW; this->maxW = maxW;
		allocated = false;
		this->len = len;
		A.resize(len),
			dA.resize(len),
			B.resize(len),
			b.resize(len),
			db.resize(len);
	}

	void fromLayer(const vector<double>& fcl);
	void fromLayer(const img_28x28& im);

	void backProp(const vector<double>& dEdO);
	void backProp(fcLayer& nextLayer);

	void updateWB(const double& learnRate);
	void activate();
};

inline void img_28x28::backProp(fcLayer& nextLayer)
{
	vector<double>& dX = nextLayer.dA;
	for (int i = 0; i < nextLayer.len; ++i)
		nextLayer.db[i] += dX[i];

	for (int x = 0; x < 28; ++x)
		for (int y = 0; y < 28; ++y)
			for (int j = 0; j < nextLayer.len; ++j)
				nextLayer.dw[j][x * 28 + y] += dX[j] * pixels[x][y];
}

inline void cUnit::initWB()
{
	// TODO: implement xaviers?
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			w[i][j] = double(rand() % 1000) / 1000 - 0.5;
	for (int i = 0; i < b.size(); i++)
		for (int j = 0; j < b[i].size(); j++)
			b[i][j] = 0.01;
}
inline void cUnit::fromUnit(const img_28x28& im)
{
	for (int i = 0; i < 28; i++)
	{
		for (int j = 0; j < 28; j++)
		{
			pix[i][j] = b[i][j];
			for (int di = -1; di < 2; di++)
				for (int dj = -1; dj < 2; dj++)
				{
					int ni = i + di, nj = j + dj;
					if (ni == -1 || ni == 28 || nj == -1 || nj == 28)
						continue;
					pix[i][j] += w[di + 1][dj + 1] * im.pixels[ni][nj];
				}
		}
	}
}
inline void cUnit::activate()
{
	for(int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
		{
			out[i][j] = fReLU(pix[i][j]);
		}
}

inline void pUnit::fromUnit(const cUnit& cu)
{
	const vector<vector<double>>& prev = cu.out;
	for(int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
		{
			pix[i][j] = prev[i * 2][j * 2];
			pix[i][j] = max(pix[i][j], prev[i * 2 + 1][j * 2]);
			pix[i][j] = max(pix[i][j], prev[i * 2][j * 2 + 1]);
			pix[i][j] = max(pix[i][j], prev[i * 2 + 1][j * 2 + 1]);
		}
}

inline void fcLayer::fromLayer(const vector<double>& fcl)
{
	//CHECK
	if (!allocated)
	{
		//set random weights & biases
		w.resize(len, vector<double>(fcl.size())),
			dw.resize(len, vector<double>(fcl.size()));
		// FIX: implement xavier's initialization
		for (vector<double>& r : w)
			for (int i = 0; i < r.size(); ++i)
				r[i] = (double(rand() % 1000) / 1000) * (maxW - minW) + minW;
		allocated = true;
	}
	for (int i = 0; i < len; ++i)
	{
		A[i] = b[i];
		for (int j = 0; j < fcl.size(); ++j)
			A[i] += w[i][j] * fcl[j];
	}
}
inline void fcLayer::fromLayer(const img_28x28& im) 
{
	if (!allocated)
	{
		//set random weights & biases
		w.resize(len, vector<double>(28 * 28)),
			dw.resize(len, vector<double>(28 * 28));
		// FIX: implement xavier's initialization
		for (vector<double>& r : w)
			for (int i = 0; i < r.size(); ++i)
				r[i] = (double(rand() % 1000) / 1000) * (maxW - minW) + minW;
		allocated = true;
	}
	for (int i = 0; i < len; ++i)
	{
		A[i] = b[i];
		for (int j = 0; j < 28 * 28; ++j)
			A[i] += w[i][j] * double(im.pixels[j / 28][j % 28]);
	}
}
inline void fcLayer::updateWB(const double& learnRate)
{
	for (int i = 0; i < len; ++i)
	{
		b[i] -= db[i] * learnRate, 
			db[i] = 0;
		for (int j = 0; j < w[i].size(); ++j)
		{
			w[i][j] -= dw[i][j] * learnRate,
				dw[i][j] = 0;
		}
	}
}

inline void fcLayer::backProp(const vector<double>& dEdO)
{
	for (int i = 0; i < dA.size(); ++i) dA[i] = bsigmoid(A[i]) * dEdO[i];
}
inline void fcLayer::backProp(fcLayer& nextLayer)
{
	const vector<double>& dX = nextLayer.dA;

	//adjust baises
	for (int i = 0; i < nextLayer.len; ++i)
		nextLayer.db[i] += dX[i];

	//adjust weights
	for (int i = 0; i < len; ++i)
		for (int j = 0; j < nextLayer.len; ++j)
			nextLayer.dw[j][i] += dX[j] * B[i];

	//prepare for previous layer
	for (int i = 0; i < len; ++i)
	{
		double ws = 0;
		for (int j = 0; j < nextLayer.len; ++j)
			ws += dX[j] * nextLayer.w[j][i];
		dA[i] = bsigmoid(A[i]) * ws;
	}
}

inline void fcLayer::activate()
{
	for (int i = 0; i < B.size(); ++i)
		B[i] = fsigmoid(A[i]);
}
