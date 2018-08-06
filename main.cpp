// Image Render.cpp : Defines the entry point for the console application.
//

/**************************TO-DO***************************

~Edit inputs to deal with randomized terrain

~Implement fitness and crossover function

----Later----

~Store neural network weights in a text file and be able to read from that file

---Much Later---- 

~Add sprites and background
~Add UI


**********************************************************/

#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include "flappy.h"
#include "NeuralNetwork.h"
#include "Population.h"
#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

int WINDOW_LENGTH = 720, WINDOW_WIDTH = 900;

double mutationRate = 0.05;

double distance(double, double, double, double);

void start(sf::RenderWindow &, Population);

int populationSize = 10;
int current_population = populationSize;

int main()
{
	srand(time(0));
	
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_LENGTH),"Flappy Bird");

	//Population
	int input_layers = 4;
	int hidden_layers = 6;
	int output_layers = 1;
	Population population(input_layers, hidden_layers, output_layers, populationSize);

	start(window,population);

    return 0;
}

void start(sf::RenderWindow &window, Population population) {
	DNA test(4, 6, 1);
	test.nn.bias_h = 0.991851568;
	test.nn.bias_o = 0.715597987;
	test.nn.weights_ih.matrix[0][0] = -0.23319190740585327;
	test.nn.weights_ih.matrix[0][1] = -0.44383066892623901;
	test.nn.weights_ih.matrix[0][2] = -0.71691030263900757;
	test.nn.weights_ih.matrix[0][3] = -0.98840296268463135;

	test.nn.weights_ih.matrix[1][0] = 0.87768185138702393;
	test.nn.weights_ih.matrix[1][1] = -0.27542954683303833;
	test.nn.weights_ih.matrix[1][2] = -0.91473126411437988;
	test.nn.weights_ih.matrix[1][3] = -0.20780050754547119;

	test.nn.weights_ih.matrix[2][0] = 0.89861750602722168;
	test.nn.weights_ih.matrix[2][1] = 0.60570085048675537;
	test.nn.weights_ih.matrix[2][2] = -0.29184848070144653;
	test.nn.weights_ih.matrix[2][3] = 0.92809844017028809;

	test.nn.weights_ih.matrix[3][0] = -0.83123266696929932;
	test.nn.weights_ih.matrix[3][1] = 0.70543539524078369;
	test.nn.weights_ih.matrix[3][2] = 0.85930967330932617;
	test.nn.weights_ih.matrix[3][3] = 0.63939332962036133;

	test.nn.weights_ih.matrix[4][0] = 0.45841848850250244;
	test.nn.weights_ih.matrix[4][1] = 0.57036042213439941;
	test.nn.weights_ih.matrix[4][2] = 0.092562675476074219;
	test.nn.weights_ih.matrix[4][3] = -0.59471416473388672;

	test.nn.weights_ih.matrix[5][0] = 0.39976191520690918;
	test.nn.weights_ih.matrix[5][1] = 0.88628804683685303;
	test.nn.weights_ih.matrix[5][2] = -0.51963865756988525;
	test.nn.weights_ih.matrix[5][3] = -0.059785783290863037;

	test.nn.weights_ho.matrix[0][0] = 0.018097519874572754;
	test.nn.weights_ho.matrix[0][1] = -0.56712543964385986;
	test.nn.weights_ho.matrix[0][2] = -0.32987457513809204;
	test.nn.weights_ho.matrix[0][3] = 0.69170200824737549;
	test.nn.weights_ho.matrix[0][4] = -0.28153324127197266;
	test.nn.weights_ho.matrix[0][5] = -0.75438702106475830;
	population.population[0] = test;
	//View
	sf::View view(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_LENGTH / 2), sf::Vector2f(WINDOW_WIDTH, WINDOW_LENGTH));

	//Genetic Algorithm
	vector<DNA> genepool;

	//Obstacles
	vector<Obstacle> obstacles;

	//Clocks
	sf::Clock fpsClock;
	sf::Clock spawnClock;

	window.setVerticalSyncEnabled(false);
	window.setKeyRepeatEnabled(false);


	//NN Inputs
	double i1, i2, i3, i4;


	double x = 255;

	obstacles.push_back(Obstacle(view));

	//Game Loop
	while (window.isOpen()) {
		sf::Time time = fpsClock.restart();

		view.move(x * time.asSeconds(), 0);
		window.setView(view);

		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		//Obtsacle Spawn
		if (spawnClock.getElapsedTime().asSeconds() >= 2.f) {
			spawnClock.restart();
			obstacles.push_back(Obstacle(view));
		}

		window.clear();

		for (int i = 0;i < populationSize;i++) {
			float pX = population.population[i].bird.sprite.getPosition().x;
			float pY = population.population[i].bird.sprite.getPosition().y;

			//Neural Network
			i1 = WINDOW_LENGTH-pY;
			i2 = obstacles[0].obstacle_top.getPosition().x-pX;
			i3 = -obstacles[0].obstacle_bottom.getSize().y;
			i4 = obstacles[0].obstacle_top.getSize().y;
			vector<double> input = { i1,i2,i3,i4 };   //distance from top window to player, distance from obstacle -----Maybe???
			Matrix output = population.population[i].nn.feedforward(input);

			if (output.matrix[0][0] > 0.5) {
				population.population[i].bird.Fly();
			}

			population.population[i].Update(time.asSeconds());
			population.population[i].Draw(window);
		}
		for (int i = 0;i < obstacles.size();i++) {
			obstacles[i].Update(time.asSeconds());
			obstacles[i].Draw(window);
			for (int j = 0; j < populationSize;j++) {
				population.population[j].fitness = population.population[j].bird.sprite.getPosition().x;
				if (population.population[j].bird.sprite.getPosition().x > obstacles[i].obstacle_bottom.getPosition().x) {
					population.population[j].fitness *= 5;
				}
				if ((population.population[j].bird.sprite.getGlobalBounds().intersects(obstacles[i].obstacle_top.getGlobalBounds()) || population.population[j].bird.sprite.getGlobalBounds().intersects(obstacles[i].obstacle_bottom.getGlobalBounds())
					|| population.population[j].bird.sprite.getPosition().y>(WINDOW_LENGTH) || population.population[j].bird.sprite.getPosition().y<0) && !population.population[j].bird.dead) {
					population.population[j].bird.dead = true;
					current_population--;
				}
			}
			if (obstacles[i].obstacle_bottom.getPosition().x <= view.getCenter().x-WINDOW_WIDTH/2) {
				obstacles.erase(obstacles.begin() + i);
			}
		}

		//Reset
		if (current_population == 0) {
			obstacles.clear();
			for (int i = 0;i < populationSize;i++) {
				genepool.push_back(population.population[i]);
			}
			view.setCenter(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_LENGTH / 2));
			population.calcFitness();
			for (int i = 0;i < populationSize - 1;i++) {
				DNA parentA = population.selection(genepool);
				DNA parentB = population.selection(genepool);
				DNA child = parentA.crossover(parentB);
				child.mutate();
				population.population[i] = child;
			}
			population.population[populationSize - 1] = population.selectElite(genepool);
			current_population = populationSize;
			spawnClock.restart();
			window.display();
			start(window,population);
		}
		window.display();
	}
}
double distance(double x1, double y1, double x2, double y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
