#pragma once

#include "Player.h"

struct SharedContext;

class HUDManager
{
public:
	HUDManager(SharedContext* context);
	~HUDManager();

	void CreateHUD();

	void Update(float l_deltaTime);
	void Draw();

	SharedContext* GetContext();

private:

	SharedContext* m_context;

	sf::Font m_font;

	sf::Texture m_arrowTexture;
	sf::Sprite m_arrowSprite;
	sf::Text m_arrowText;

	sf::Texture m_coinTexture;
	sf::Sprite m_coinSprite;
	sf::Text m_coinText;

	sf::Texture m_healthFrameTexture;
	sf::Sprite m_healthFrameSprite;

	sf::Texture m_healthBarTexture;
	sf::Sprite m_healthBarSprite;
	sf::IntRect m_healthBarRect;
};