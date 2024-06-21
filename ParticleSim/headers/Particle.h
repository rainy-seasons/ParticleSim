#pragma once
#include "Body.h"
class Particle : public sf::Drawable, public sf::Transformable
{
public:
	Particle(unsigned int count) :
		m_particles(count),
		m_vertices(sf::Points, count),
		m_count(count)
	{};
	//Particle(unsigned int count);

	void Update(std::vector<Body>& bodies);
	void SetPosition();
	void SetCount(int n);
	int  GetCount() const;

private:
	struct nParticle
	{
		sf::Vector2f velocity;
		sf::Vector2f accel;
	};

	sf::VertexArray m_vertices;
	std::vector<nParticle> m_particles;

	sf::Vector2f dist;
	sf::Vector2f normalized_distance;

	float hyp;
	int   m_count;
	float inverse_distance;
	float inverse_square;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = NULL;
		target.draw(m_vertices, states);
	}
};
