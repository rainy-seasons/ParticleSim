#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include "Particle.h"

class GUI
{
public:
	GUI(Particle& particles, bool& isPaused);
	~GUI();

	void Render(sf::RenderWindow& window);

private:
	Particle* m_pParticles;
	bool* m_isPaused;
};



#endif