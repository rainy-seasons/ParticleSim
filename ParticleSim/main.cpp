#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include <functional>
#include <atomic>
#include <condition_variable>
#include "Body.h"
#include "Particle.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

void MoveBody(sf::RenderWindow &window, Body &body);
bool isMovingBody = false;

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "GravSim");
	window.setFramerateLimit(60);

	sf::Font font;

	// x_pos, y_pos, strength
	Body body(sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), 100);
	Body body2(sf::Vector2f(200, 400), 60);
	Body body3(sf::Vector2f(400, 600), 40);

	std::vector<Body> Bodies{
			Body(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 100),
			Body(sf::Vector2f(200, 400), 60),
			Body(sf::Vector2f(400, 600), 40)
	};

	Particle particles(500000);
	particles.SetPosition();


	if (!font.loadFromFile("verdana.ttf"))
	{
		throw("COULD NOT LOAD FONT");
		return -1;
	}
	sf::Text FrameCounter;
	FrameCounter.setFont(font);

	std::thread MoveBodyThread(MoveBody, std::ref(window), std::ref(body));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Clock clock; 
		float currentTime = clock.restart().asSeconds();
		float FPS = 1.0f / currentTime;
		FrameCounter.setString("FPS: " + std::to_string(FPS));

		window.clear();

		particles.Update(Bodies);
		window.draw(particles);

		for (auto& body : Bodies)
		{
			body.Render(window);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && body.GetBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				isMovingBody = true;
				// Check if a thread is already running
				if (!MoveBodyThread.joinable())
				{
					// Start a new thread to move the body
					MoveBodyThread = std::thread(MoveBody, std::ref(window), std::ref(body));
				}
			}
		}
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			isMovingBody = false;
		}
		if (MoveBodyThread.joinable() && !isMovingBody)
		{
			MoveBodyThread.join();
		}

		window.draw(FrameCounter);
		window.display();

	}
	return 0;
}

void MoveBody(sf::RenderWindow &window, Body &body)
{
	while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		body.SetPosition(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
	}
}

