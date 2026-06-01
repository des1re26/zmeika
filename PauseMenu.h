#pragma once
#include "Menu.h"
#include "Settings.h"
#include "Renderer.h"

class PauseMenu : public Menu {
private:
    Settings& settings;
    Renderer* renderer; // ”казатель на рендерер дл€ обновлени€ окна

public:
    PauseMenu(Settings& gameSettings, Renderer* gameRenderer);
    int show(); // ¬озвращает: 1-продолжить, 2-выход в главное меню
};