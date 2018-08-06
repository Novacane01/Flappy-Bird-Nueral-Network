#include "stdafx.h"
#include "NeuralNetwork.h"
#include "Matrix.h"
#include <stdlib.h>

NeuralNetwork::NeuralNetwork(int il, int hl, int ol):weights_ih(hl,il),weights_ho(ol,hl),
input_layer(il,1),hidden_layer(hl,1),output_layer(ol,1){
	weights_ih.randomize();
	weights_ho.randomize();
	bias_h = (float)rand() / RAND_MAX;
	bias_o = (float)rand() / RAND_MAX;
}

Matrix NeuralNetwork::feedforward(std::vector<double> input_array) {
	input_layer = fromArray(input_array);
	Matrix hlSum = weights_ih.multiply(input_layer);
	hlSum = hlSum.add(bias_h);
	hlSum = hlSum.sigmoid();
	Matrix output = weights_ho.multiply(hlSum);
	output = output.add(bias_o);
	output = output.sigmoid();
	return output;
}

Matrix NeuralNetwork::fromArray(std::vector<double> input) {
	Matrix newMatrix(input.size(), 1);
	for (int i = 0;i < input.size();i++) {
		newMatrix.matrix[i][0] = input[i];
	}
	return newMatrix;
}


