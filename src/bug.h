#pragma once
#include <stdint.h>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "defines.h"

class Bug
{
private:
	unsigned int x = 0;
	unsigned int y = 0;
	uint8_t health = 0;
	sf::Color color;
public:
	Bug(unsigned int x, unsigned int y);
	Bug(unsigned int x, unsigned int y, sf::Color color);
	unsigned int getX() const { return x; }
	unsigned int getY() const { return y; }
	uint8_t getHealth() const { return health; }
	sf::Color getColor() const { return color; }
	sf::Color getNewColor() const;
	void setX(unsigned int x) { this->x = x; }
	void setY(unsigned int y) { this->y = y; }
	void setHealth(uint8_t health) { this->health = health; }
	void setColor(sf::Color color) { this->color = color; }
	int tick();
};
