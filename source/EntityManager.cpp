#include "../include/EntityManager.h"
#include "../include/SharedContext.h"

#include <iostream>

EntityManager::EntityManager(SharedContext* context) : m_context(context)
{
	ResetVampireSpawner();
}

EntityManager::~EntityManager()
{

}

void EntityManager::Update(float l_deltaTime)
{
	VampireSpawner(l_deltaTime);

	for (const auto& entity : m_entities)
	{
		entity->Update(l_deltaTime);
	}

	for (const auto& arrow : m_arrows)
	{
		arrow->Update(l_deltaTime);
	}

	for (const auto& vampire : m_vampires)
	{
		vampire->Update(l_deltaTime);
	}

	std::erase_if(m_entities, [](const std::unique_ptr<Entity>& entity)
		{
			return entity->IsMarkedForDeletion();
		});
	std::erase_if(m_arrows, [](const std::unique_ptr<Arrow>& arrow)
		{
			return arrow->IsMarkedForDeletion();
		});
	std::erase_if(m_vampires, [](const std::unique_ptr<Vampire>& vampire)
		{
			return vampire->IsMarkedForDeletion();
		});
}

void EntityManager::Draw()
{
	for (const auto& entity : m_entities)
	{
		entity->Draw(GetContext()->m_window->GetRenderWindow());
	}
	for (const auto& vampire : m_vampires)
	{
		vampire->Draw(GetContext()->m_window->GetRenderWindow());
	}
	for (const auto& arrow : m_arrows)
	{
		arrow->Draw(GetContext()->m_window->GetRenderWindow());
	}
}

Player* EntityManager::GetPlayer()
{
	return m_player;
}

std::vector<std::unique_ptr<Arrow>>& EntityManager::GetArrows()
{
	return m_arrows;
}

std::vector<std::unique_ptr<Vampire>>& EntityManager::GetVampires()
{
	return m_vampires;
}

void EntityManager::CreateEntity(const EntityType& l_type)
{
	std::unique_ptr<Entity> newEntity = nullptr;
	if (l_type == EntityType::Player)
	{
		newEntity = std::make_unique<Player>(this);
		m_player = dynamic_cast<Player*>(newEntity.get());
	}
	else if (l_type == EntityType::Arrow)
	{
		auto arrow = std::make_unique<Arrow>(this);
		m_arrows.push_back(std::move(arrow));
		return;
	}
	else if (l_type == EntityType::Vampire)
	{
		auto vampire = std::make_unique<Vampire>(this);
		m_vampires.push_back(std::move(vampire));
		return;
	}
	else
		return;

	m_entities.push_back(std::move(newEntity));
}

void EntityManager::ClearEntities()
{
	m_entities.clear();
	m_arrows.clear();
	m_vampires.clear();
}

void EntityManager::VampireSpawner(float l_deltaTime)
{
	if (m_vampireCooldown > 0.0f)
	{
		m_vampireCooldown -= l_deltaTime;
		return;
	}

	CreateEntity(EntityType::Vampire);

	m_spawnCount++;
	if (m_spawnCount % (5 * m_spawnWave) == 0 && m_nextVampireCooldown > 0.2)
	{
		if (m_nextVampireCooldown > 2.f)
			m_nextVampireCooldown -= 0.5f;
		else if (m_nextVampireCooldown > 1.f)
			m_nextVampireCooldown -= 0.05f;
		else if (m_nextVampireCooldown > 0.2f)
			m_nextVampireCooldown -= 0.01f;
		else
			m_nextVampireCooldown = 0.2f;
		m_spawnWave++;
	}
	m_vampireCooldown = m_nextVampireCooldown;
}

void EntityManager::ResetVampireSpawner()
{
	m_vampireCooldown = 0.0f;
	m_nextVampireCooldown = 2.5f;
	m_spawnCount = 0;
	m_spawnWave = 1;
}

SharedContext* EntityManager::GetContext()
{
	return m_context;
}
