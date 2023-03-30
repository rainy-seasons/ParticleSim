#pragma once
#include <SFML/Graphics.hpp>
class Body
{
private:
	sf::Vector2f position;
	float strength;
	sf::CircleShape shape;

public:
	Body(float pos_x, float pos_y, float strength, sf::Color color = sf::Color::White)
	{
		position.x = pos_x;
		position.y = pos_y;
		this->strength = strength;

		shape.setPosition(position);
		shape.setFillColor(color);
		shape.setRadius(8);
	}

	void Render(sf::RenderWindow& window)
	{
		window.draw(shape);
	}

	sf::Vector2f GetPosition()
	{
		return this->position;
	}

	float GetStrenth()
	{
		return this->strength;
	}
};
