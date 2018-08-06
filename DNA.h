#pragma once
#include "NeuralNetwork.h"
#include "flappy.h"

class DNA {
public:
	DNA(int il, int hl, int ol);
	void Update(double);
	void Draw(sf::RenderWindow &);
	DNA crossover(DNA);
	void mutate();
	NeuralNetwork nn;
	Player bird;
	int il, hl, ol;
	double fitness = 0;
	sf::Sprite sprite;
private:
	sf::Texture texture;
};