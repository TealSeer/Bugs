#include <SFML/Graphics.hpp>
#include "defines.h"
#include "game.h"

Game* game;

int terminate(sf::RenderWindow& window) {
	window.close();
	delete game;
	return 0;
}

int main()
{
	sf::RenderWindow window( sf::VideoMode( { WINDOW_WIDTH, WINDOW_HEIGHT } ), "Bugs", sf::Style::Close );
	window.setFramerateLimit(60);
	sf::View scaledView(sf::Vector2f(BUFFER_WIDTH / 2, BUFFER_HEIGHT / 2), sf::Vector2f(BUFFER_WIDTH, BUFFER_HEIGHT));
	window.setView(scaledView);
	sf::RenderTexture buffer({ BUFFER_WIDTH, BUFFER_HEIGHT });
	sf::VertexArray pixels(sf::PrimitiveType::Points, BUFFER_WIDTH * BUFFER_HEIGHT);
	game = new Game;
	srand(time(0));
	game->addBug(BUFFER_WIDTH / 2, BUFFER_HEIGHT / 2, sf::Color::White);

	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if (event->is<sf::Event::Closed>()) {
				return terminate(window);
			}
			else if (const auto keyPressed = event->getIf<sf::Event::KeyPressed>()) {
				if (keyPressed->scancode == sf::Keyboard::Scancode::Q) {
					return terminate(window);
				}
			}
		}

		game->tick();

		pixels.clear();
		for (auto& bugColumn : game->buglist) {
			for (auto& bug : bugColumn) {
				if (!bug.has_value()) continue;
				sf::Vertex newPixel;
				newPixel.position = sf::Vector2f(bug->getX(), bug->getY() + 1);
				newPixel.color = bug->getColor();
				pixels.append(newPixel);
			}
		}

		buffer.clear(sf::Color(16, 16, 16));
		buffer.draw(pixels);
		buffer.display();
		window.clear(sf::Color(16, 16, 16));
		sf::Sprite bufferSprite(buffer.getTexture());
		window.draw(bufferSprite);
		window.display();
	}
}
