#include <SFML/Graphics.hpp>
#include <iostream>
#include "Body.h"
#include "Particle.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "GravSim");
	window.setFramerateLimit(144);
	sf::Font font;
	sf::Text FrameCounter;
	FrameCounter.setFont(font);

	// x_pos, y_pos, strength
	Body body(400, 450, 200);
	Body body2(540, 200, 100);

	std::vector<Body> Bodies;

	Bodies.push_back(body);
	Bodies.push_back(body2);

	Particle particles(100000);
	particles.SetPosition();


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

		particles.Update(Bodies);
		window.draw(particles);

		for (auto& body : Bodies)
		{
			body.Render(window);
		}

		window.draw(FrameCounter);
		window.display();
	}
}
