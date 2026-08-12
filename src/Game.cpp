#include "Game.h"
#include "Application.h"
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
	std::array<std::pair<int, int>, 8> directions = { {
		{-1, -1}, // NW
		{0, -1}, // N
		{1, -1}, // NE
		{1, 0}, // E
		{1, 1}, // SE
		{0, 1}, // S
		{-1, 1}, // SW
		{-1, 0}, // W
	} };
	std::ranges::shuffle(directions, Application::getRandomDevice());
	std::pair<unsigned int, unsigned int> newCoords;
	for(auto dir : directions) {
		newCoords = { x + dir.first, y + dir.second };
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
