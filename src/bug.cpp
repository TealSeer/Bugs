#include "bug.h"

Bug::Bug(unsigned int x, unsigned int y) : Bug::Bug(x, y, sf::Color::White) {}

Bug::Bug(unsigned int x, unsigned int y, sf::Color color) : x{ x }, y{ y }, health{ 100 }, color{ color } {}

int Bug::tick() {
	int status = 0;
	if (health > 0) --health;
	if (health <= 0) status |= TICK_DIE;
	if ((rand() % 60) == 0) status |= TICK_REPRODUCE;
	return status;
}

sf::Color Bug::getNewColor() const {
	sf::Color newColor = color;
	if ((rand() % 5) == 0) {
		int field = rand() % 3;
		int modify = rand() % 2;
		switch (field) {
		case 0:
			if (newColor.r == 255) {
				newColor.r -= 5;
			}
			else if (newColor.r == 0) {
				newColor.r += 5;
			}
			else if (modify == 0) {
				newColor.r -= 5;
			}
			else if (modify == 1) {
				newColor.r += 5;
			}
			break;
		case 1:
			if (newColor.g == 255) {
				newColor.g -= 5;
			}
			else if (newColor.g == 0) {
				newColor.g += 5;
			}
			else if (modify == 0) {
				newColor.g -= 5;
			}
			else if (modify == 1) {
				newColor.g += 5;
			}
			break;
		case 2:
			if (newColor.b == 255) {
				newColor.b -= 5;
			}
			else if (newColor.b == 0) {
				newColor.b += 5;
			}
			else if (modify == 0) {
				newColor.b -= 5;
			}
			else if (modify == 1) {
				newColor.b += 5;
			}
			break;
		}
	}
	return newColor;
}