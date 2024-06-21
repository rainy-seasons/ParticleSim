#include "../headers/Particle.h"

// Sets the starting position for the particles. Reccommended to spread them out with rand()
void Particle::SetPosition()
{
	for (std::size_t i = 0; i < m_particles.size(); i++)
	{
		//m_vertices[i].position = sf::Vector2f(rand() % 1200, rand() % 400); // Doubled values for now
		m_vertices[i].position = sf::Vector2f(rand() % 600, rand() % 200); 
		m_particles[i].accel = sf::Vector2f(0, 0);
		m_particles[i].velocity = sf::Vector2f(0, 0);
		hyp = 0;
		inverse_distance = 0;
		normalized_distance = sf::Vector2f(0, 0);
		inverse_square = 0;
		dist = sf::Vector2f(0, 0);
	}
}

void Particle::Update(std::vector<Body>& bodies)
{
	for (std::size_t i = 0; i < m_particles.size(); ++i)
	{
		nParticle& p = m_particles[i];

		for (auto& body : bodies)
		{
			dist = body.GetPosition() - m_vertices[i].position; // distance between gravity source object and particle
			hyp = sqrt((dist.x * dist.x) + (dist.y * dist.y)); // pythagorean theorem to find line between point and body
			inverse_distance = 1.0f / hyp;

			normalized_distance = inverse_distance * dist;

			inverse_square = inverse_distance * inverse_distance; // Double the distance = 1/4th strength. 1/x * 1/x = ((1*1)/(x*x)) = 1/x^2
			p.accel = normalized_distance * (float)body.GetStrength() * inverse_square; // Get the acceleration using inverse square

			p.velocity += p.accel;

			m_vertices[i].position += p.velocity;
		}
	}
}

int Particle::GetCount() const
{
	return this->m_count;
}

void Particle::SetCount(int n)
{
	m_particles.resize(n);
	m_vertices.resize(n);
	m_count = n;
}
