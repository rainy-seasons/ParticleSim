#include <SFML/Graphics.hpp>
#include <iostream>
#include "Body.h"
#include "Particle.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "GravSim");
	window.setFramerateLimit(60);
	sf::Font font;
	sf::Text FrameCounter;
	FrameCounter.setFont(font);

	// x_pos, y_pos, strength
	Body body(200, 300, 100);
	Body body2(640, 200, 300);

	std::vector<Body> Bodies;

	Bodies.push_back(body);
	Bodies.push_back(body2);


	std::vector<Particle> particles;
	for (int i = 0; i < 3000; i++) // # of particles
	{
		sf::Color color;
		if (i % 2 == 0)
		{
			color = sf::Color::Green;
		}
		else
		{
			color = sf::Color::Red;
		}
		particles.push_back(Particle(rand() % 100, rand() % 100, rand() % 3, 0, color));
	}

	if (!font.loadFromFile("verdana.ttf"))
	{
		throw("COULD NOT LOAD FONT");
		return -1;
	}

	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		float currentTime = clock.restart().asSeconds();
		float FPS = 1.0f / currentTime;
		FrameCounter.setString("FPS: " + std::to_string(FPS));

		window.clear();



		for (auto particle = particles.begin(); particle != particles.end();)
		{
			particle->Update(Bodies);
			particle->Render(window);
			if (particle->GetPosition().x > SCREEN_WIDTH || particle->GetPosition().x < -1 || particle->GetPosition().y > SCREEN_HEIGHT || particle->GetPosition().y < -1)
			{
				// The InvertVelocity() call makes them bounce off the edges of the screen.
				// The erase() call makes them not bounce but deletes them if they fly off.
				particle->InvertVelocity();
				//particle = particles.erase(particle);
			}
			// Wrap this in an else statement if using particles.erase(particle)
			particle++;
		}

		for (auto& body : Bodies)
		{
			body.Render(window);
		}
		window.draw(FrameCounter);

		window.display();
	}
}
