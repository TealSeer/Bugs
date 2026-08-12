#pragma once
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>

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