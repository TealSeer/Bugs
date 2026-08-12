#include "Application.h"
#include "EventVisitor.h"
#include <imgui.h>
#include <imgui-SFML.h>

std::random_device Application::m_randomDevice{};

bool Application::init() {
	m_window.setFramerateLimit(60);
	if(!ImGui::SFML::Init(m_window)) return false;
	// Disable ImGui config file being created
	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = NULL;
	sf::View scaledView(sf::Vector2f(BUFFER_WIDTH / PIXEL_SCALE, BUFFER_HEIGHT / PIXEL_SCALE), sf::Vector2f(BUFFER_WIDTH, BUFFER_HEIGHT));
	m_window.setView(scaledView);
	m_game.start();
	return true;
}

void Application::run() {
	while(const std::optional event = m_window.pollEvent()) {
		event->visit(EventVisitor(m_window, m_showDebugWindow));
	}
	m_game.tick();
	ImGui::SFML::Update(m_window, m_deltaClock.restart());
	if(m_showDebugWindow) {
		ImGui::Begin("Debug", &m_showDebugWindow, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("Total bugs: %d", m_game.getBugsAlive());
		ImGui::Separator();
		ImGui::Checkbox("Exhaustive search", &m_game.m_exhaustiveSearch);
		if(ImGui::Button("Reset")) {
			m_game.killAll();
			m_game.start();
		}
		ImGui::End();
	}
	m_windowTexture.clear(sf::Color(16, 16, 16));
	m_windowTexture.draw(m_game);
	m_windowTexture.display();
	m_window.clear(sf::Color(16, 16, 16));
	m_window.draw(sf::Sprite{ m_windowTexture.getTexture() });
	ImGui::SFML::Render(m_window);
	m_window.display();
}

void Application::shutdown() {
	ImGui::SFML::Shutdown(m_window);
}