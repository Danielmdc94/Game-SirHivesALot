#pragma once

#include "../include/Character.h"

class Vampire : public Character
{
public:
    Vampire(EntityManager* l_entityManager);
    ~Vampire();

    void Load();

    void Update(float l_deltaTime);
    void Draw(sf::RenderWindow* l_window);

    void setIsKilled(bool l_isKilled) { m_isKilled = l_isKilled; }
    bool isKilled() { return m_isKilled; }

private:
    bool m_isKilled = false;
};