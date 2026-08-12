#pragma once
#include <stdint.h>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Defines.h"

class Bug {
private:
	unsigned int m_x = 0;
	unsigned int m_y = 0;
	uint8_t m_health = 100;
	sf::Color m_color;
public:
	Bug(unsigned int x, unsigned int y);
	Bug(unsigned int x, unsigned int y, sf::Color color);
	unsigned int getX() const { return m_x; }
	unsigned int getY() const { return m_y; }
	uint8_t getHealth() const { return m_health; }
	sf::Color getColor() const { return m_color; }
	sf::Color getNewColor() const;
	void setX(unsigned int x) { this->m_x = x; }
	void setY(unsigned int y) { this->m_y = y; }
	void setHealth(uint8_t health) { this->m_health = health; }
	void setColor(sf::Color color) { this->m_color = color; }
	int tick();
};
