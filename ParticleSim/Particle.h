#pragma once
#include "Body.h"
class Particle
{
private:
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::CircleShape shape;

public:
	Particle(float pos_x, float pos_y, float vel_x, float vel_y, sf::Color color)
	{
		position.x = pos_x;
		position.y = pos_y;

		velocity.x = vel_x;
		velocity.y = vel_y;

		shape.setPosition(position);
		shape.setFillColor(color);
		shape.setRadius(1);
	}
	void Render(sf::RenderWindow& window);
	void Update(std::vector<Body>& bodies);
	sf::Vector2f GetPosition();
	void InvertVelocity();
};
