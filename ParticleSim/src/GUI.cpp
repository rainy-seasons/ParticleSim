#include "GUI.h"

GUI::GUI(Particle& particles, bool& isPaused)
{
	this->m_pParticles = &particles;
	this->m_isPaused = &isPaused;
}

GUI::~GUI()
{
	std::cout << "m_isPaused: " << m_isPaused << std::endl;
}

void GUI::Render(sf::RenderWindow& window)
{
	if (ImGui::Button("Pause/Unpause")) { *m_isPaused = !*m_isPaused; } // Pauses/unpauses the simulation on button press
	ImGui::SameLine();
	if (ImGui::Button("Restart"))
	{
		*m_isPaused = true; 
		m_pParticles->SetPosition();
	}
	int pCount = m_pParticles->GetCount();
	ImGui::PushItemWidth(150.0f); // Set width of InputInt() object
	if (ImGui::InputInt("# of Particles", &pCount, 10000, 100000))
	{
		m_pParticles->SetCount(pCount);
	}
	ImGui::PopItemWidth(); // Pop width so as to not affect other widgets
}