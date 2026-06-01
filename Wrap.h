#pragma once
#include "Game.h"

class Wrap : public Game {
protected:
    void onWallCollision(sf::Vector2i& head);
    int getSelfCollisionStartIndex();

public:
    Wrap();
};