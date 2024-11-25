#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"

class EntityManager;

class Character : public Entity
{
public:
	Character(EntityManager* l_entityManager);
	virtual ~Character();

	void MoveInDirection(const Direction& l_dir);

	virtual void Load() = 0;

	int GetMaxHitPoints();
	void SetMaxHitpoints(int l_maxHitPoints);
	int GetHitPoints();
	void SetHitpoints(int l_hitPoints);

	void Update(float l_deltaTime);
	void Draw(sf::RenderWindow* l_window);

protected:
	sf::Sprite m_sprite;
	sf::IntRect m_textureRect;

	int m_maxHitPoints;
	int m_hitPoints;
};
