#pragma once
#include "SFML\Graphics.hpp"

extern int WINDOW_LENGTH, WINDOW_WIDTH;

class Player {
public:
	Player();
	void Update(float);
	void Draw(sf::RenderWindow &);
	void Fly();
	bool dead = false;
	sf::Sprite sprite;
private:
	double acceleration = 0;
	sf::Texture texture;

};

class Obstacle {
public:
	Obstacle(sf::View);
	void Update(float);
	void Draw(sf::RenderWindow &);
	sf::RectangleShape obstacle_top;
	sf::RectangleShape obstacle_bottom;
private:
	sf::Texture texture;
};
