#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"
#include "Body.h"
#include "Particle.h"
#include "GUI.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

void UpdateBodies(sf::RenderWindow& window, std::vector<Body>& Bodies, std::thread& MoveBodyThread);
void MoveBody(sf::RenderWindow& window, Body& body);
void MoveBodyThreadHandler(sf::RenderWindow& window, std::thread& MoveBodyThread, Body& body);


int main()
{
	bool isPaused = true;

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "GravSim");
	ImGui::SFML::Init(window);
	ImGui::StyleColorsDark;


	window.setFramerateLimit(60);

	sf::Clock clock; 
	sf::Font font;

	// pos.x, pos.y, strength
	Body body(sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), 100, sf::Color::Red);

	std::vector<Body> Bodies{
			Body(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT/2), 100),
			Body(sf::Vector2f(200, 400), 400),
			Body(sf::Vector2f(200, 300), 400),
	};

	Particle particles(100000);

	particles.SetPosition();

	GUI* UI = new GUI(particles, isPaused); // Initialize GUI


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
			ImGui::SFML::ProcessEvent(event);
			while (event.type == sf::Event::Closed)
				window.close();
		}

		ImGui::SFML::Update(window, clock.restart());
		ImGui::Begin("Controls");

		UI->Render(window);

		if (!isPaused) { particles.Update(Bodies); } // Only update particle position if the simulation is not paused

		window.clear();

		window.draw(particles);

		UpdateBodies(window, Bodies, MoveBodyThread);
		ImGui::End();

		//window.draw(FrameCounter);
		ImGui::SFML::Render(window);
		window.display();
	}
	delete(UI);
	ImGui::SFML::Shutdown();

	return 0;
}

void UpdateBodies(sf::RenderWindow& window, std::vector<Body>& Bodies, std::thread& MoveBodyThread)
{
	// ImGui UI
	if (ImGui::Button("Add Body"))
	{
		// Create a new body in the vector with position offset from the first Body's position
		Bodies.push_back(Body(sf::Vector2f(Bodies[0].GetPosition().x + 25, Bodies[0].GetPosition().y + 25), 400));
	}

	for (size_t i = 0; i < Bodies.size(); ++i)
	{
		std::string bodyLabel = "Body " + std::to_string(i + 1);

		if (ImGui::TreeNode(bodyLabel.c_str()))  // Tree node for structuring body traits into drop down menus
		{
			// Handle deleting bodies
			if (ImGui::Button("Delete"))
			{
				if (Bodies.size() > 1)
				{
					Bodies.erase(Bodies.begin() + i);
					ImGui::TreePop();
					continue;
				}
			}

			// Handle setting strength for bodies
			int strength = Bodies[i].GetStrength();
			if (ImGui::InputInt("Strength", &strength, 1, 50)) 
			{
				Bodies[i].SetStrength(strength);
			}

			// Convert color for ImGui
			sf::Color col = Bodies[i].GetColor();
			float color[3] = { col.r / 255.0f, col.g / 255.0f, col.b / 255.0f };

			if (ImGui::ColorEdit3("Color", color))
			{
				// Convert color back to sf::Color object
				Bodies[i].SetColor(sf::Color(
					static_cast<sf::Uint8>(color[0] * 255),
					static_cast<sf::Uint8>(color[1] * 255),
					static_cast<sf::Uint8>(color[2] * 255)
				));
			}

			ImGui::TreePop();
		}
		MoveBodyThreadHandler(window, MoveBodyThread, Bodies[i]);
		Bodies[i].Render(window);
	}
}

// Updates the body position if it's being moved
void MoveBody(sf::RenderWindow &window, Body &body)
{
	while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		body.SetPosition(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

// Handles the thread for moving bodies
void MoveBodyThreadHandler(sf::RenderWindow& window, std::thread& MoveBodyThread, Body& body)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && body.GetBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
	{
		// Check if a thread is already running
		if (!MoveBodyThread.joinable())
		{
			// Start a new thread to move the body
			MoveBodyThread = std::thread(MoveBody, std::ref(window), std::ref(body));
		}
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && MoveBodyThread.joinable())
	{
		MoveBodyThread.join();
	}
}
