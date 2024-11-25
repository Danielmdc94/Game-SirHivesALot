#pragma once

#include "Window.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "EntityManager.h"
#include "HUDManager.h"

class StateManager;

struct SharedContext
{
	SharedContext() : m_window(nullptr), m_eventManager(nullptr), m_textureManager(nullptr), m_entityManager(nullptr), m_stateManager(nullptr), m_hudManager(nullptr) {}

	Window* m_window;
	EventManager* m_eventManager;
	TextureManager* m_textureManager;
	EntityManager* m_entityManager;
	StateManager* m_stateManager;
	HUDManager* m_hudManager;
};