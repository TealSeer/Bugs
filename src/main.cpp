#include <SFML/Graphics.hpp>
#include "defines.h"
#include "game.h"
#include <imgui.h>
#include <imgui-SFML.h>

Game* game;

struct EventVisitor {
	sf::RenderWindow& window;
	bool& show_debug;

	explicit EventVisitor(sf::RenderWindow& window, bool& show_debug) : window(window), show_debug(show_debug) {}
	void operator()(const sf::Event::Closed& closed) {
		ImGui::SFML::ProcessEvent(window, closed);
		window.close();
	}
	void operator()(const sf::Event::KeyPressed& keyPressed) {
		ImGui::SFML::ProcessEvent(window, keyPressed);
		if(keyPressed.scancode == sf::Keyboard::Scancode::Q) {
			window.close();
		}
		else if(keyPressed.scancode == sf::Keyboard::Scancode::Space) {
			show_debug = !show_debug;
		}
	}
	template <typename T>
	void operator()(const T& event) {
		ImGui::SFML::ProcessEvent(window, event);
	}
};

int main() {
	bool show_debug_window = false;
	sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Bugs", sf::Style::Close);
	window.setFramerateLimit(60);
	if(!ImGui::SFML::Init(window)) return -1;
	// Disable ImGui config file being created
	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = NULL;

	sf::View scaledView(sf::Vector2f(BUFFER_WIDTH / 2, BUFFER_HEIGHT / 2), sf::Vector2f(BUFFER_WIDTH, BUFFER_HEIGHT));
	window.setView(scaledView);
	sf::RenderTexture buffer({ BUFFER_WIDTH, BUFFER_HEIGHT });
	game = new Game;
	srand(time(0));
	game->start();

	sf::Clock deltaClock;
	while(window.isOpen()) {
		while(const std::optional event = window.pollEvent()) {
			event->visit(EventVisitor(window, show_debug_window));
		}
		game->tick();

		ImGui::SFML::Update(window, deltaClock.restart());
		if(show_debug_window) {
			ImGui::Begin("Debug", &show_debug_window, ImGuiWindowFlags_AlwaysAutoResize);
			ImGui::Text("Total bugs: %d", game->getBugsAlive());
			ImGui::Separator();
			ImGui::Checkbox("Exhaustive search", &game->m_exhaustiveSearch);
			if(ImGui::Button("Reset")) {
				game->killAll();
				game->start();
			}
			ImGui::End();
		}

		buffer.clear(sf::Color(16, 16, 16));
		buffer.draw(*game);
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
