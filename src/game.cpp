#include "game.h"
#include <vector>

Game::Game() {
	std::array<std::optional<Bug>, BUFFER_HEIGHT> column;
	column.fill({});
	m_bugList.fill(column);
}

void Game::start() {
	addBug(BUFFER_WIDTH / 2, BUFFER_HEIGHT / 2, sf::Color::White);
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::VertexArray pixels(sf::PrimitiveType::Points, m_bugsAlive);
	for(auto& bugColumn : m_bugList) {
		for(auto& bug : bugColumn) {
			if(!bug.has_value()) continue;
			sf::Vertex newPixel;
			newPixel.position = sf::Vector2f(bug->getX(), bug->getY() + 1); // top left of view is x,y = 0,1
			newPixel.color = bug->getColor();
			pixels.append(newPixel);
		}
	}
	target.draw(pixels);
}

bool Game::addBug(unsigned int x, unsigned int y, sf::Color color) {
	if(!checkCoords(x, y)) return false;
	Bug newBug(x, y, color);
	m_bugList[x][y] = newBug;
	m_bugsAlive++;
	return true;
}

void Game::tick() {
	for(auto& bugColumn : m_bugList) {
		for(auto& bug : bugColumn) {
			if(!bug.has_value()) {
				continue;
			}
			int status = bug->tick();

			if(status & TICK_DIE) {
				bug.reset();
				m_bugsAlive--;
				continue;
			}

			if(status & TICK_REPRODUCE) {
				std::optional<std::pair<unsigned int, unsigned int>> newCoords = findAdjacent(bug->getX(), bug->getY());
				if(!newCoords.has_value()) continue;
				addBug(newCoords->first, newCoords->second, bug->getNewColor());
			}
		}
	}
}

std::optional<std::pair<unsigned int, unsigned int>> Game::findAdjacent(unsigned int x, unsigned int y) {
	int direction = rand() % 8;
	unsigned int newX = 0, newY = 0;
	switch(direction) {
		case 0:
			newX = x - 1;
			newY = y + 1;
			break;
		case 1:
			newX = x;
			newY = y + 1;
			break;
		case 2:
			newX = x + 1;
			newY = y + 1;
			break;
		case 3:
			newX = x - 1;
			newY = y;
			break;
		case 4:
			newX = x + 1;
			newY = y;
			break;
		case 5:
			newX = x - 1;
			newY = y - 1;
			break;
		case 6:
			newX = x;
			newY = y - 1;
			break;
		case 7:
			newX = x + 1;
			newY = y - 1;
			break;
	}
	if(checkCoords(newX, newY)) {
		return { { newX, newY } };
	}
	else {
		return {};
	}
}

void Game::killAll() {
	for(auto& bugColumn : m_bugList) {
		bugColumn.fill({});
	}
	m_bugsAlive = 0;
}

bool Game::checkCoords(unsigned int x, unsigned int y) {
	if((x >= BUFFER_WIDTH || x < 0) || (y >= BUFFER_HEIGHT || y < 0)) {
		return false;
	}

	auto& potentialBug = m_bugList[x][y];
	return !(potentialBug.has_value());
}
