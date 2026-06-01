#pragma once
#include "Menu.h"

class GameModeMenu : public Menu {
public:
    GameModeMenu();
    int show() override;
};