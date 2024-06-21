#include "../headers/Body.h"

Body::Body(sf::Vector2f pos, int strength, sf::Color color)
{
	this->m_color = color;
	this->m_position = pos;
	this->m_strength = strength;
	this->m_shape.setPosition(m_position);
	this->m_shape.setFillColor(color);
	this->m_shape.setRadius(12);
	this->isMovingBody = false;
}

void Body::Render(sf::RenderWindow& window) const
{
	window.draw(m_shape);
}

sf::Vector2f Body::GetPosition() const
{
	return this->m_position;
}

void Body::SetPosition(sf::Vector2f pos)
{
	m_shape.setPosition(pos);
	this->m_position = pos;
}

int Body::GetStrength() const
{
	return this->m_strength;
}

void Body::SetStrength(int str)
{
	if (str < INT_MAX)
	{
		this->m_strength = str;
	}
}

void Body::SetColor(sf::Color color)
{
	this->m_color = color;
	this->m_shape.setFillColor(color);
}

sf::Color Body::GetColor() const
{
	return this->m_color;
}

sf::FloatRect Body::GetBounds() const
{
	return this->m_shape.getGlobalBounds();
}
