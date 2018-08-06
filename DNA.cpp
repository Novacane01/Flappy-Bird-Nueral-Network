#include "stdafx.h"
#include "DNA.h"
#include "Population.h"

DNA::DNA(int il, int hl, int ol) :nn(il, hl, ol) {
	this->il = il;
	this->hl = hl;
	this->ol = ol;
}

void DNA::Update(double dt) {
	bird.Update(dt);
}

void DNA::Draw(sf::RenderWindow &window) {
	bird.Draw(window);
}

DNA DNA::crossover(DNA parentB) {
	double r;
	DNA child(parentB.il,parentB.hl,parentB.ol);
	for (int i = 0; i < nn.weights_ih.matrix.size();i++) {
		for (int j = 0; j < nn.weights_ih.matrix[0].size();j++) {
			r = (float)rand() / RAND_MAX;
			if (r < .5) {
				child.nn.weights_ih.matrix[i][j] = nn.weights_ih.matrix[i][j];
			}
			else {
				child.nn.weights_ih.matrix[i][j] = parentB.nn.weights_ih.matrix[i][j];
			}
		}
	}
	if (r < .5) {
		child.nn.bias_h = nn.bias_h;
	}
	else {
		child.nn.bias_h = parentB.nn.bias_h;
	}
	for (int i = 0; i < nn.weights_ho.matrix.size();i++) {
		for (int j = 0; j < nn.weights_ho.matrix[0].size();j++) {
			r = (float)rand() / RAND_MAX;
			if (r < .5) {
				child.nn.weights_ho.matrix[i][j] = nn.weights_ho.matrix[i][j];
			}
			else {
				child.nn.weights_ho.matrix[i][j] = parentB.nn.weights_ho.matrix[i][j];
			}
		}
	}
	if (r < .5) {
		child.nn.bias_o = nn.bias_o;
	}
	else {
		child.nn.bias_o = parentB.nn.bias_o;
	}
	return child;
}

void DNA::mutate() {
	double r;
	for (int i = 0; i < nn.weights_ih.matrix.size();i++) {
		for (int j = 0; j < nn.weights_ih.matrix[0].size();j++) {
			r = (float)rand() / RAND_MAX;
			if (r < mutationRate) {
				nn.weights_ih.matrix[i][j] = ((float)rand() / RAND_MAX) * 2 - 1;
//				std::cout << "Mutation in the ih weights" << std::endl;
			}
		}
		if (r < mutationRate) {
			nn.bias_h = (float)rand() / RAND_MAX;
	//		std::cout << "Mutation in the hidden bias" << std::endl;
		}
		for (int i = 0; i < nn.weights_ho.matrix.size();i++) {
			for (int j = 0; j < nn.weights_ho.matrix[0].size();j++) {
				double r = (float)rand() / RAND_MAX;
				if (r < mutationRate) {
					nn.weights_ho.matrix[i][j] = ((float)rand() / RAND_MAX) * 2 - 1;
		//			std::cout << "Mutation in the ho weights" << std::endl;
				}
			}
		}
		if (r < mutationRate) {
			nn.bias_o = (float)rand() / RAND_MAX;
			//std::cout << "Mutation in the output bias" << std::endl;
		}
	}
}