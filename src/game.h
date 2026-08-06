#pragma once
#include "bug.h"
#include <array>
#include <optional>
#include "defines.h"

class Game
{
private:
	uint8_t timer = 5;
	std::optional<std::pair<unsigned int, unsigned int>> findAdjacent(unsigned int x, unsigned int y);
	bool checkCoords(unsigned int x, unsigned int y);
public:
	uint32_t bugsAlive = 0;
	Game();
	void tick();
	void killall();
	bool addBug(unsigned int x, unsigned int y, sf::Color color);
	std::array<std::array<std::optional<Bug>, BUFFER_HEIGHT>, BUFFER_WIDTH> buglist;
};
