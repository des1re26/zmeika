#pragma once
#include "Settings.h"
#include "RecordManager.h"

class GameApplication {
private:
    Settings settings;
    RecordManager recordManager;
    bool running;

    void showMainMenu();
    void showSettings();
    void startGame();
    void runGameLoop(int gameMode);

public:
    GameApplication();
    ~GameApplication();

    void run();  // Главный метод запуска
};
