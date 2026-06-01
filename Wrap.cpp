#include "Wrap.h"

Wrap::Wrap() : Game() {
    setMode(1);
}

void Wrap::onWallCollision(sf::Vector2i& head) {
    if (head.x < 0) head.x = 19;
    if (head.x >= 20) head.x = 0;
    if (head.y < 0) head.y = 19;
    if (head.y >= 20) head.y = 0;
}

int Wrap::getSelfCollisionStartIndex() {
    return 2;
}