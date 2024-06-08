#pragma once
#include <thread>
#include <SFML/Graphics.hpp>
class Body
{
private:
	sf::Vector2f m_position;
	int m_strength;
	sf::CircleShape m_shape;
	sf::Color m_color;


public:
	bool isMovingBody;
	Body(sf::Vector2f pos, int strength, sf::Color color = sf::Color::Red);

	void Render(sf::RenderWindow& window) const;


	void SetPosition(sf::Vector2f pos);
	void SetStrength(int str);
	void SetColor(sf::Color color);

	int GetStrength();
	sf::Vector2f GetPosition();
	sf::FloatRect GetBounds();
	sf::Color GetColor();


};
