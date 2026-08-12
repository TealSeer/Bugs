#pragma once
#include "Game.h"
#include "Defines.h"
#include <SFML/Graphics.hpp>

class Application {
private:
	Game m_game;
	bool m_showDebugWindow = false;
	sf::Clock m_deltaClock;
	sf::RenderWindow m_window{ sf::VideoMode{{ WINDOW_WIDTH, WINDOW_HEIGHT }}, "Bugs", sf::Style::Close };
	sf::RenderTexture m_windowTexture{ { BUFFER_WIDTH, BUFFER_HEIGHT } };
public:
	bool init();
	void run();
	bool isRunning() { return m_window.isOpen(); }
	void shutdown();
};