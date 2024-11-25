#include "../include/Character.h"
#include "../include/EntityManager.h"
#include "../include/SharedContext.h"
#include <iostream>

Character::Character(EntityManager* l_entityManager) : Entity(l_entityManager)
{
	m_name = "Character";
}

Character::~Character()
{

}

void Character::MoveInDirection(const Direction& l_dir)
{
	bool didMove = false;

	if (l_dir == Direction::Up)
	{
		Accelerate(0, -m_speed.y);
		didMove = true;
	}
	else if (l_dir == Direction::Down)
	{
		Accelerate(0, m_speed.y);
		didMove = true;
	}
	else if (l_dir == Direction::Left)
	{
		Accelerate(-m_speed.x, 0);
		didMove = true;
	}
	else if (l_dir == Direction::Right)
	{
		Accelerate(m_speed.x, 0);
		didMove = true;
	}
	if (didMove && GetState() == EntityState::Idle)
	{
		SetState(EntityState::Moving);
	}
}

int Character::GetMaxHitPoints()
{
	return m_maxHitPoints;
}

void Character::SetMaxHitpoints(int l_maxHitPoints)
{
	m_maxHitPoints = l_maxHitPoints;
}

int Character::GetHitPoints()
{
	return m_hitPoints;
}

void Character::SetHitpoints(int l_hitPoints)
{
	if (l_hitPoints < 0)
		l_hitPoints = 0;
	if (l_hitPoints > m_maxHitPoints)
		l_hitPoints = m_maxHitPoints;
	m_hitPoints = l_hitPoints;
}

void Character::Update(float l_deltaTime)
{
	Entity::Update(l_deltaTime);
	if (abs(m_velocity.x) >= 0.1f || abs(m_velocity.y) >= 0.1f)
		SetState(EntityState::Moving);
	else
		SetState(EntityState::Idle);
	m_sprite.setPosition(m_position);
	m_boxCollider = Rectangle(sf::Vector2f(GetSize().x - 34, GetSize().y - 14), GetPosition());
}

void Character::Draw(sf::RenderWindow* l_window)
{
	l_window->draw(m_sprite);
}