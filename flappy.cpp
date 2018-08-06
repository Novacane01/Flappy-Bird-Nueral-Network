#include "stdafx.h"
#include "flappy.h"
#include "DNA.h"

Player::Player() {
	texture.loadFromFile("C:\\Users\\Novacane\\Pictures\\flappy_bird2.png");
	sprite.setPosition((WINDOW_WIDTH*.20), (WINDOW_LENGTH / 2));
}

void Player::Draw(sf::RenderWindow &window) {
	sprite.setTexture(texture);
	window.draw(sprite);
}

//****************************POLISH PHYSICS LATER************************
void Player::Update(float dt) {
	if (!dead) {
		if (acceleration > -9.8) {
			acceleration -= .5;
			/*if(sprite.getRotation()>-180){
				sprite.rotate(-.1);
			}*/
		}
		else {
			acceleration = -9.8;
		}

		if (sprite.getPosition().y <= 0) {
			acceleration = -9.8;
		}
		sprite.setPosition(sprite.getPosition().x + (255 * dt), sprite.getPosition().y - (acceleration*dt * 20));
	}
	else {
		sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y);
	}
}

void Player::Fly() {
	acceleration = 20;
	/*if (sprite.getRotation() < 90) {
		sprite.setRotation(sprite.getRotation() + 5);
	}*/
}
//********************************************************************

Obstacle::Obstacle(sf::View cam){
	int n = rand()%(WINDOW_LENGTH/2-100)+100; //Possibly look at later for improvement
	obstacle_top.setFillColor(sf::Color::White);
	obstacle_top.setSize(sf::Vector2f(50,n));
	obstacle_top.setPosition(cam.getCenter().x+WINDOW_WIDTH/2, 0);
	obstacle_bottom.setFillColor(sf::Color::White);
	obstacle_bottom.setSize(sf::Vector2f(50, -(WINDOW_LENGTH-n-200)));
	obstacle_bottom.setPosition(cam.getCenter().x + WINDOW_WIDTH / 2,WINDOW_LENGTH);
}

void Obstacle::Update(float dt) {
	//obstacle_top.setPosition(obstacle_top.getPosition().x - (dt*225), obstacle_top.getPosition().y);
	//obstacle_bottom.setPosition(obstacle_bottom.getPosition().x -(dt*225), obstacle_bottom.getPosition().y);
}

void Obstacle::Draw(sf::RenderWindow &window) {
	window.draw(obstacle_top);
	window.draw(obstacle_bottom);
}