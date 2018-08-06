#include "stdafx.h"
#include "Population.h"
Population::Population(int il, int hl, int ol,int size){
	populationSize = size;
	this->il = il;
	this->hl = hl;
	this->ol = ol;
	for (int i = 0;i < populationSize;i++) {
		population.push_back(DNA(il,hl,ol));
	}
}

void Population::calcFitness() {
	double totalfitness = 0;
	for (int i = 0; i < populationSize;i++) {
		totalfitness += population[i].fitness;
	}
	for (int i = 0; i < populationSize;i++) {
		population[i].fitness /= totalfitness;
	}
}

DNA Population::selection(std::vector<DNA> genepool) {
	double r = (float)rand() / RAND_MAX;
	int index = 0;
	while (r >= 0) {
		r -= genepool[index++].fitness;
	}
	index--;
	return genepool[index];
}

DNA Population::selectElite(std::vector<DNA> genepool) {
	DNA elitist(il,hl,ol);
	double highest_fitness = 0;
	int elite_index = 0;
	for (int i = 0;i < populationSize;i++) {
		if (genepool[i].fitness > highest_fitness) {
			highest_fitness = genepool[i].fitness;
			elite_index = i;
		}
	}
	for (int i = 0;i < elitist.nn.weights_ih.matrix.size();i++) {
		for (int j = 0;j < elitist.nn.weights_ih.matrix[0].size();j++) {
			elitist.nn.weights_ih.matrix[i][j] = genepool[elite_index].nn.weights_ih.matrix[i][j];
		}
	}
	for (int i = 0;i < elitist.nn.weights_ho.matrix.size();i++) {
		for (int j = 0;j < elitist.nn.weights_ho.matrix[0].size();j++) {
			elitist.nn.weights_ho.matrix[i][j] = genepool[elite_index].nn.weights_ho.matrix[i][j];
		}
	}
	elitist.nn.bias_h = genepool[elite_index].nn.bias_h;
	elitist.nn.bias_o = genepool[elite_index].nn.bias_o;
	return elitist;
}