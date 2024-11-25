#include "../include/Game.h"
#include <iostream>

Game::Game() : m_window(WIN_NAME, sf::Vector2u(WIN_W, WIN_H)), m_stateManager(&m_context), m_eventManager(&m_context), m_entityManager(&m_context), m_hudManager(&m_context)
{
	m_clock.restart();
	srand(time(nullptr));

	m_context.m_window = &m_window;
	m_context.m_eventManager = &m_eventManager;
	m_context.m_textureManager = &m_textureManager;
	m_context.m_entityManager = &m_entityManager;
	m_context.m_stateManager = &m_stateManager;
	m_context.m_hudManager = &m_hudManager;
	m_stateManager.SwitchTo(StateType::Intro);
	PlayBackgroundMusic();
}

Game::~Game()
{

}

void Game::Update()
{
	m_window.Update();
	m_eventManager.Update();
	m_stateManager.Update(m_elapsed);
}

void Game::Render()
{
	m_window.BeginDraw();
	m_stateManager.Draw();
	m_window.EndDraw();
}

void Game::LateUpdate()
{
	RestartClock();
}

void Game::PlayBackgroundMusic()
{
	if (!m_mainTheme.openFromFile("Audio/MainTheme.ogg"))
	{
		std::cerr << "Error: Could not load background music from " << "Audio/MainTheme.ogg" << std::endl;
		return;
	}
	m_mainTheme.setVolume(10);
	m_mainTheme.setLoop(true);
	m_mainTheme.play();
}
