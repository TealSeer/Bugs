#include "Game.h"
#include <vector>
#include <algorithm>
#include <random>

Game::Game() {
	std::array<std::optional<Bug>, BUFFER_HEIGHT> column;
	column.fill({});
	m_bugList.fill(column);
	m_pixelBuffer.resize(BUFFER_HEIGHT * BUFFER_WIDTH);
}

void Game::updateBuffer() {
	m_pixelBuffer.clear();
	for(auto& bugColumn : m_bugList) {
		for(auto& bug : bugColumn) {
			if(!bug.has_value()) continue;
			sf::Vertex newPixel;
			newPixel.position = sf::Vector2f(bug->getX(), bug->getY() + 1); // top left of view is x,y = 0,1
			newPixel.color = bug->getColor();
			m_pixelBuffer.append(newPixel);
		}
	}
}

bool Game::addBug(unsigned int x, unsigned int y, sf::Color color) {
	if(!checkCoords(x, y)) return false;
	m_bugList[x][y] = Bug(x, y, color);
	m_bugsAlive++;
	return true;
}

void Game::tick() {
	for(auto& bugColumn : m_bugList) {
		for(auto& bug : bugColumn) {
			if(!bug.has_value()) continue;
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
	updateBuffer();
}

std::optional<std::pair<unsigned int, unsigned int>> Game::findAdjacent(unsigned int x, unsigned int y) {
	std::array directions{ 0, 1, 2, 3, 4, 5, 6, 7 };
	std::random_device rd;
	std::mt19937 gen{ rd() };
	std::ranges::shuffle(directions, gen);
	std::pair<unsigned int, unsigned int> newCoords;
	for(auto dir : directions) {
		newCoords = { x, y };
		switch(dir) {
			case 0:
				newCoords.first--;
				newCoords.second++;
				break;
			case 1:
				newCoords.second++;
				break;
			case 2:
				newCoords.first++;
				newCoords.second++;
				break;
			case 3:
				newCoords.first--;
				break;
			case 4:
				newCoords.first++;
				break;
			case 5:
				newCoords.first--;
				newCoords.second--;
				break;
			case 6:
				newCoords.second--;
				break;
			case 7:
				newCoords.first++;
				newCoords.second--;
				break;
		}
		if(checkCoords(newCoords.first, newCoords.second)) {
			return { newCoords };
		}
		else {
			if(!m_exhaustiveSearch) return {};
		}
	}
	return {};
}

void Game::killAll() {
	for(auto& bugColumn : m_bugList) {
		bugColumn.fill({});
	}
	m_bugsAlive = 0;
	updateBuffer();
}

bool Game::checkCoords(unsigned int x, unsigned int y) {
	if((x >= BUFFER_WIDTH || x < 0) || (y >= BUFFER_HEIGHT || y < 0)) return false;
	auto& potentialBug = m_bugList[x][y];
	return !(potentialBug.has_value());
}
