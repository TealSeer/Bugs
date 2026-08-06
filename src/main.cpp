#include <SFML/Graphics.hpp>
#include "defines.h"
#include "game.h"
#include <imgui.h>
#include <imgui-SFML.h>

Game* game;

int main()
{
	bool show_debug_window = false;
	sf::RenderWindow window( sf::VideoMode( { WINDOW_WIDTH, WINDOW_HEIGHT } ), "Bugs", sf::Style::Close );
	window.setFramerateLimit(60);
	if (!ImGui::SFML::Init(window)) {
		return -1;
	}
	sf::View scaledView(sf::Vector2f(BUFFER_WIDTH / 2, BUFFER_HEIGHT / 2), sf::Vector2f(BUFFER_WIDTH, BUFFER_HEIGHT));
	window.setView(scaledView);
	sf::RenderTexture buffer({ BUFFER_WIDTH, BUFFER_HEIGHT });
	sf::VertexArray pixels(sf::PrimitiveType::Points, BUFFER_WIDTH * BUFFER_HEIGHT);
	game = new Game;
	srand(time(0));
	game->addBug(BUFFER_WIDTH / 2, BUFFER_HEIGHT / 2, sf::Color::White);

	const auto onKeyPressed = [&window, &show_debug_window](const sf::Event::KeyPressed& keyPressed) {
		if (keyPressed.scancode == sf::Keyboard::Scancode::Q) {
			window.close();
		}
		else if (keyPressed.scancode == sf::Keyboard::Scancode::Space) {
			show_debug_window = !show_debug_window;
		}
	};

	const auto onClose = [&window](const sf::Event::Closed&) {
		window.close();
	};

	sf::Clock deltaClock;
	while ( window.isOpen() )
	{
		window.handleEvents(onKeyPressed, onClose);
		game->tick();

		pixels.clear();
		for (auto& bugColumn : game->buglist) {
			for (auto& bug : bugColumn) {
				if (!bug.has_value()) continue;
				sf::Vertex newPixel;
				newPixel.position = sf::Vector2f(bug->getX(), bug->getY() + 1); // top left of view is x,y = 0,1
				newPixel.color = bug->getColor();
				pixels.append(newPixel);
			}
		}

		ImGui::SFML::Update(window, deltaClock.restart());
		if (show_debug_window) {
			ImGui::Begin("Debug", &show_debug_window, ImGuiWindowFlags_AlwaysAutoResize);
			ImGui::Text("Total bugs: %d", game->bugsAlive);
			if (ImGui::Button("Reset")) {
				game->killall();
				game->addBug(BUFFER_WIDTH / 2, BUFFER_HEIGHT / 2, sf::Color::White);
			}
			ImGui::End();
		}

		buffer.clear(sf::Color(16, 16, 16));
		buffer.draw(pixels);
		buffer.display();
		window.clear(sf::Color(16, 16, 16));
		sf::Sprite bufferSprite(buffer.getTexture());
		window.draw(bufferSprite);
		ImGui::SFML::Render(window);
		window.display();
	}
	ImGui::SFML::Shutdown();
	delete game;
	return 0;
}
