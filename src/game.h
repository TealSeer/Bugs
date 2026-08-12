#pragma once
#include "bug.h"
#include <array>
#include <optional>
#include "defines.h"

class Game : public sf::Drawable {
private:
	std::optional<std::pair<unsigned int, unsigned int>> findAdjacent(unsigned int x, unsigned int y);
	bool checkCoords(unsigned int x, unsigned int y);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	uint32_t m_bugsAlive = 0;
	std::array<std::array<std::optional<Bug>, BUFFER_HEIGHT>, BUFFER_WIDTH> m_bugList;
public:
	Game();
	void start();
	void tick();
	void killAll();
	bool addBug(unsigned int x, unsigned int y, sf::Color color);
	uint32_t getBugsAlive() const { return m_bugsAlive; }
	bool m_exhaustiveSearch = false; // public because ImGui does not support getter/setters to control GUI elements
};
