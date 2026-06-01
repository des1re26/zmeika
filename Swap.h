#pragma once
#include "Game.h"

class Swap : public Game {
protected:
    void onFoodEaten() override;

public:
    Swap();
    int getSelfCollisionStartIndex() override;  // Добавляем
};