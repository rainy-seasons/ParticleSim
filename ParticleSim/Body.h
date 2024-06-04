#pragma once
#include <SFML/Graphics.hpp>
class Body
{
private:
	sf::Vector2f position;
	float strength;
	sf::CircleShape shape;

public:
	Body(sf::Vector2f pos, float strength, sf::Color color = sf::Color::White)
	{
		position = pos;
		this->strength = strength;

		shape.setPosition(position);
		shape.setFillColor(color);
		shape.setRadius(12);
	}

	void Render(sf::RenderWindow& window) const
	{
		window.draw(shape);
	}

	sf::Vector2f GetPosition()
	{
		return this->position;
	}

	void SetPosition(sf::Vector2f pos)
	{
		shape.setPosition(pos);
		this->position = pos;
	}

	float GetStrength()
	{
		return this->strength;
	}

	sf::FloatRect GetBounds()
	{
		return shape.getGlobalBounds();
	}
};
