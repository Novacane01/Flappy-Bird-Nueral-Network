#pragma once
#include "DNA.h"
#include <iostream>
#include <vector>

extern double mutationRate;

class Population {
public:
	Population(int, int, int, int);
	void calcFitness();
	DNA selection(std::vector<DNA>);
	std::vector<DNA> population;
	DNA selectElite(std::vector<DNA>);
	int il, hl, ol;
private:
	int generations = 0;
    int	populationSize = 0;
};