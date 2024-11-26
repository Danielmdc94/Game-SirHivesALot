#include "../include/Skeleton.h"
#include "../include/EntityManager.h"
#include "../include/SharedContext.h"

#include "../include/MathUtils.h"

#include <iostream>


Skeleton::Skeleton(EntityManager* l_entityManager) : Character(l_entityManager)
{
	Load();
}

Skeleton::~Skeleton()
{

}

void Skeleton::Load()
{
	sf::Rect viewSpace = m_entityManager->GetContext()->m_window->GetViewSpace();
	TextureManager* textureManager = m_entityManager->GetContext()->m_textureManager;

	int screenWidth = m_entityManager->GetContext()->m_window->GetWindowSize().x;
	int screenHeight = m_entityManager->GetContext()->m_window->GetWindowSize().y;

	float innerPadding = 20.0f;
	float outerPadding = 10.0f;

	float randomXPos = 0;
	float randomYPos = 0;

	int side = rand() % 4;

	switch (side)
	{
	case 0:
		randomXPos = outerPadding + (rand() % (int)(screenWidth - 2 * outerPadding));
		randomYPos = innerPadding;
		break;
	case 1:
		randomXPos = outerPadding + (rand() % (int)(screenWidth - 2 * outerPadding));
		randomYPos = screenHeight - innerPadding;
		break;
	case 2:
		randomXPos = innerPadding;
		randomYPos = outerPadding + (rand() % (int)(screenHeight - 2 * outerPadding));
		break;
	case 3:
		randomXPos = screenWidth - innerPadding;
		randomYPos = outerPadding + (rand() % (int)(screenHeight - 2 * outerPadding));
		break;
	}

	sf::Vector2f spawnPosition(randomXPos, randomYPos);


	m_type = EntityType::Skeleton;
	m_name = "Skeleton";

	m_position = spawnPosition;
	m_state = EntityState::Moving;

	SetSize(64, 64);
	m_textureRect = sf::IntRect(0, m_size.y * 2, m_size.x, m_size.y);

	textureManager->RequireResource("Skeleton");
	m_sprite.setTexture(*textureManager->GetResource("Skeleton"));
	m_sprite.setTextureRect(m_textureRect);
	m_sprite.setOrigin(m_textureRect.width / 2.0f, m_textureRect.height / 2.0f);
	m_sprite.setPosition(m_position);
}

void Skeleton::Update(float l_deltaTime)
{
	if (m_isKilled)
		return;

	Player* player = m_entityManager->GetPlayer();

	if (m_boxCollider.collidesWith(player->GetSpearCollider()))
	{
		setIsKilled(true);
		MarkForDeletion();
		player->SetGold(player->GetGold() + 1);
		return;
	}

	for (const auto& arrow : m_entityManager->GetArrows())
	{
		Rectangle arrowRect = arrow->GetBoxCollider();
		if (m_boxCollider.collidesWith(arrowRect))
		{
			player->SetGold(player->GetGold() + 1);
			setIsKilled(true);
			MarkForDeletion();
			arrow->MarkForDeletion();
			break;
		}
	}

	if (m_boxCollider.collidesWith(player->GetBoxCollider()))
	{
		if (player->GetHasShield())
			player->SetHitpoints(player->GetHitPoints() - 20);
		else
			player->SetHitpoints(player->GetHitPoints() - 40);
		setIsKilled(true);
		MarkForDeletion();
	}	

	sf::Vector2f playerPosition = player->GetPosition();
	sf::Vector2f direction = playerPosition - m_position;

	float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (magnitude != 0)
		direction /= magnitude;

	float speed = 190.0f;
	Move(direction * speed * l_deltaTime);
	m_sprite.setPosition(m_position);
	Character::Update(l_deltaTime);
}

void Skeleton::Draw(sf::RenderWindow* l_window)
{
	Character::Draw(l_window);
}