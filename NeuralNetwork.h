#pragma once
#include "Matrix.h"
#include <vector>

class NeuralNetwork {
public:
	NeuralNetwork(int, int, int);
	Matrix feedforward(std::vector<double>);
	Matrix fromArray(std::vector<double>);
	Matrix weights_ih;
	Matrix weights_ho;
	Matrix input_layer;
	Matrix hidden_layer;
	Matrix output_layer;
	float bias_h = 0.f;
	float bias_o = 0.f;
private:

};
