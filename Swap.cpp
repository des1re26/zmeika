#include "Swap.h"
#include <algorithm>

Swap::Swap() : Game() {
    setMode(2);
}

void Swap::onFoodEaten() {
    getSnake().setGrow(true);
    getScoreRef() += 10;

    std::deque<sf::Vector2i>& body = getSnake().getBodyRef();

    if (body.size() >= 3) {
        sf::Vector2i oldTail = body.back();

        // Разворачиваем змейку
        std::reverse(body.begin(), body.end());

        // Новая голова - старый хвост
        body.front() = oldTail;

        // Меняем направление на противоположное
        int oldDir = getSnake().getDirection();
        int newDir = oldDir;

        if (oldDir == 0) newDir = 1;
        else if (oldDir == 1) newDir = 0;
        else if (oldDir == 2) newDir = 3;
        else if (oldDir == 3) newDir = 2;

        getSnake().getDirRef() = newDir;
        getSnake().getNextDirRef() = newDir;

        getScoreRef() += 5;
        getJustSwapped() = true;
    }
}

// Добавляем реализацию метода
int Swap::getSelfCollisionStartIndex() {
    if (getJustSwapped()) {
        getJustSwapped() = false;
        return 999; // Пропускаем проверку на этом ходу
    }
    return 1;
}