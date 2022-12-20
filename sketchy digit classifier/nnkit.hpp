// Neural Network Modeling Kit
// below contains my custom-made neural network modeling tools

#pragma once
#include "layerClasses.hpp"

class FCNN
{
public:
	int numLayers;
	vector<fcLayer> layers;
	bool prepared_weights;
	FCNN() {}
	FCNN(const vector<int>& layerSizes, const int& inDim)
	{
		//TODO: xaviers
		prepared_weights = true;
		numLayers = layerSizes.size();
		layers.resize(numLayers);
		double pr = 6.0 / sqrt(inDim + layerSizes[0]);
		layers[0] = fcLayer(layerSizes[0], -pr, pr);
		for (int i = 1; i < numLayers; ++i)
		{
			pr = 6.0 / sqrt(layerSizes[i - 1] + layerSizes[i]);
			layers[i] = fcLayer(layerSizes[i], -pr, pr);
		}
	}

	vector<double> forward_prop(const img_28x28& im);
	vector<double> forward_prop(const vector<double>& in);
	void updateWB(const double& learnRate);
	void backward_prop(const vector<double>& dEdO, img_28x28& inputImg);
	void xaviers(const int& input_size);
};

inline vector<double> FCNN::forward_prop(const img_28x28& im)
{
	if (!prepared_weights) xaviers(28 * 28);
	layers[0].fromLayer(im), layers[0].activate();
	for (int i = 1; i < numLayers; ++i)
		layers[i].fromLayer(layers[i - 1].B), layers[i].activate();
	return layers[numLayers - 1].B;
}
inline vector<double> FCNN::forward_prop(const vector<double>& in)
{
	if (!prepared_weights) xaviers(in.size());
	layers[0].fromLayer(in), layers[0].activate();
	for (int i = 1; i < numLayers; ++i)
		layers[i].fromLayer(layers[i - 1].B), layers[i].activate();
	return layers[numLayers - 1].B;
}
inline void FCNN::updateWB(const double& learnRate)
{
	for (fcLayer& fcl : layers)
		fcl.updateWB(learnRate);
}
inline void FCNN::backward_prop(const vector<double>& dEdO, img_28x28& inputImg)
{
	// FIX: missing backProp for first layer from input
	layers[numLayers - 1].backProp(dEdO);
	for(int i = numLayers - 2; i >= 0; --i)
		layers[i].backProp(layers[i + 1]);
	inputImg.backProp(layers[0]);
}
inline void FCNN::xaviers(const int& input_size)
{//TODO: xaviers
}