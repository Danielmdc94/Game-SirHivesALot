#pragma once

#include "Character.h"
#include "Player.h"
#include "Arrow.h"
#include "Vampire.h"

struct SharedContext;

class EntityManager
{
public:
	EntityManager(SharedContext* context);
	~EntityManager();

	void Update(float l_deltaTime);
	void Draw();

	Player* GetPlayer();
	std::vector<std::unique_ptr<Arrow>>& GetArrows();
	std::vector<std::unique_ptr<Vampire>>& GetVampires();

	void CreateEntity(const EntityType& l_type);
	void ClearEntities();

	void VampireSpawner(float l_deltaTime);
	void ResetVampireSpawner();

	SharedContext* GetContext();

private:

	SharedContext* m_context;

	std::vector<std::unique_ptr<Entity>> m_entities;
	std::vector<std::unique_ptr<Arrow>> m_arrows;
	std::vector<std::unique_ptr<Vampire>> m_vampires;

	Player* m_player;

	float m_vampireCooldown;
	float m_nextVampireCooldown;
	int m_spawnCount;
	int m_spawnWave;
};