#pragma once

#include "../include/Character.h"

class Skeleton : public Character
{
public:
    Skeleton(EntityManager* l_entityManager);
    ~Skeleton();

    void Load();

    void Update(float l_deltaTime);
    void Draw(sf::RenderWindow* l_window);

    void setIsKilled(bool l_isKilled) { m_isKilled = l_isKilled; }
    bool isKilled() { return m_isKilled; }

private:
    bool m_isKilled = false;
};