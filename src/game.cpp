#include "game.h"
#include <vector>

Game::Game() {
	std::array<std::optional<Bug>, BUFFER_HEIGHT> column;
	column.fill({});
	buglist.fill(column);
}

bool Game::addBug(unsigned int x, unsigned int y, sf::Color color) {
	if (!checkCoords(x, y)) return false;
	Bug newBug(x, y, color);
	buglist[x][y] = newBug;
	bugsAlive++;
	return true;
}

void Game::tick() {
	for (auto& bugColumn : buglist) {
		for (auto& bug : bugColumn) {
			if (!bug.has_value()) {
				continue;
			}
			int status = bug->tick();

			if (status & TICK_DIE) {
				bug.reset();
				bugsAlive--;
				continue;
			}

			if (status & TICK_REPRODUCE) {
				std::optional<std::pair<unsigned int, unsigned int>> newCoords = findAdjacent(bug->getX(), bug->getY());
				if (!newCoords.has_value()) continue;
				addBug(newCoords->first, newCoords->second, bug->getNewColor());
			}
		}
	}
}

std::optional<std::pair<unsigned int, unsigned int>> Game::findAdjacent(unsigned int x, unsigned int y) {
	int direction = rand() % 8;
	unsigned int newX = 0, newY = 0;
	switch (direction) {
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
	if (checkCoords(newX, newY)) {
		return { { newX, newY } };
	}
	else {
		return {};
	}
}

void Game::killall() {
	for (auto& bugColumn : buglist) {
		bugColumn.fill({});
	}
	bugsAlive = 0;
}

bool Game::checkCoords(unsigned int x, unsigned int y) {
	if ((x >= BUFFER_WIDTH || x < 0) || (y >= BUFFER_HEIGHT || y < 11)) {
		return false;
	}

	auto& potentialBug = buglist[x][y];
	return !(potentialBug.has_value());
}
