#include "Snake.h"

Snake::Snake(int width, int height) : gridWidth(width), gridHeight(height) {
    init();
}

void Snake::init() {
    body.clear();
    body.push_back(sf::Vector2i(10, 10));
    body.push_back(sf::Vector2i(9, 10));
    body.push_back(sf::Vector2i(8, 10));
    dir = 0;      // вправо
    nextDir = 0;
    growFlag = false;
}

void Snake::reset() {
    init();
}

void Snake::setDirection(int newDir) {
    if ((newDir == 0 && dir != 1) ||
        (newDir == 1 && dir != 0) ||
        (newDir == 2 && dir != 3) ||
        (newDir == 3 && dir != 2)) {
        nextDir = newDir;
    }
}

void Snake::updateMove(sf::Vector2i newHead) {
    body.push_front(newHead);
}

void Snake::finishMove() {
    dir = nextDir;

    if (!growFlag) {
        body.pop_back();
    }
    else {
        growFlag = false;
    }
}

bool Snake::checkSelfCollision() const {
    for (size_t i = 1; i < body.size(); i++) {
        if (body[i].x == body.front().x && body[i].y == body.front().y) {
            return true;
        }
    }
    return false;
}

bool Snake::isOnBody(sf::Vector2i pos) const {
    for (const auto& segment : body) {
        if (segment.x == pos.x && segment.y == pos.y) {
            return true;
        }
    }
    return false;
}