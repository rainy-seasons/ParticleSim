#include "Particle.h"

void Particle::Render(sf::RenderWindow& window)
{
	shape.setPosition(position);
	window.draw(shape);
}

sf::Vector2f Particle::GetPosition()
{
	return this->position;
}

void Particle::InvertVelocity()
{
	velocity.x = velocity.x * -1;
	velocity.y = velocity.y * -1;
}


void Particle::Update(std::vector<Body>& bodies)
{
	for (auto body : bodies)
	{
		float dist_x = body.GetPosition().x - position.x;
		float dist_y = body.GetPosition().y - position.y;
		float distance = sqrt((dist_x * dist_x) + (dist_y * dist_y)); // Pythagorean theorem to get distance between the body and particle

		float inverse_distance = 1.f / distance; // Inverse distance for preferring closer objects over farther ones

		float normalized_x = inverse_distance * dist_x;
		float normalized_y = inverse_distance * dist_y;

		float inverse_square = inverse_distance * inverse_distance; // Double the distance = 1/4th strength. 1/x * 1/x = ((1*1)/(x*x)) = 1/x^2

		// Acceleration using inverse square.
		float accel_x = normalized_x * body.GetStrenth() * inverse_square;
		float accel_y = normalized_y * body.GetStrenth() * inverse_square;

		if (accel_x > 3)
			accel_x = 3;
		if (accel_y > 3)
			accel_y = 3;

		velocity.x += accel_x;
		velocity.y += accel_y;


		position.x += velocity.x;
		position.y += velocity.y;
	}
}
