#include "GameApplication.h"
#include "Game.h"
#include "Wrap.h"
#include "Swap.h"
#include "Renderer.h"
#include "MainMenu.h"
#include "GameModeMenu.h"
#include "PauseMenu.h"
#include "InputHandler.h"
#include "SettingsMenu.h"
#include <SFML/Graphics.hpp>

GameApplication::GameApplication() : running(true) {}

GameApplication::~GameApplication() {}

void GameApplication::showMainMenu() {
    MainMenu mainMenu;
    int menuChoice = mainMenu.show();

    if (menuChoice == 0 || menuChoice == 3) {
        running = false;
    }
    else if (menuChoice == 2) {
        showSettings();
    }
    else if (menuChoice == 1) {
        startGame();
    }
}

void GameApplication::showSettings() {
    bool needRecreate = false;
    SettingsMenu settingsMenu(settings, needRecreate);
    settingsMenu.show();
}

void GameApplication::startGame() {
    GameModeMenu modeMenu;
    int mode = modeMenu.show();
    if (mode == 0) return;

    int gameMode = 0;
    if (mode == 2) gameMode = 1;      // Wrap
    else if (mode == 3) gameMode = 2; // Swap
    else gameMode = 0;                 // Classic

    runGameLoop(gameMode);
}

void GameApplication::runGameLoop(int gameMode) {
    bool gameRunning = true;

    while (gameRunning) {
        Game* game = nullptr;

        if (gameMode == 1) {
            game = new Wrap();
        }
        else if (gameMode == 2) {
            game = new Swap();
        }
        else {
            game = new Game();
            game->setMode(0);
        }

        Renderer renderer(settings);
        InputHandler input;

        sf::Clock clock;
        float gameTimer = 0;
        float updateInterval = 0.15f;
        bool inGame = true;
        bool newRecordAchieved = false;

        while (inGame && renderer.isOpen()) {
            input.handleEvents(renderer.getWindow());
            input.update();

            // Меню паузы
            if (!game->isGameOver() && input.isEscapePressed()) {
                PauseMenu pauseMenu(settings, &renderer);
                int pauseChoice = pauseMenu.show();

                if (pauseChoice == 2) {
                    inGame = false;
                    gameRunning = false;
                    break;
                }
                continue;
            }

            // Выход в главное меню
            if (input.isExitPressed() && game->isGameOver()) {
                inGame = false;
                gameRunning = false;
                break;
            }

            // Рестарт игры
            if (game->isGameOver() && input.isRestartPressed()) {
                inGame = false;
                break;
            }

            // Управление
            if (!game->isGameOver()) {
                int direction = input.getDirection();
                if (direction != -1) game->setDirection(direction);
            }

            // Обновление игры
            float dt = clock.restart().asSeconds();
            if (dt > 0.05f) dt = 0.05f;

            gameTimer += dt;

            if (gameTimer >= updateInterval) {
                game->update(gameTimer);
                gameTimer = 0;
            }

            // Проверка нового рекорда
            if (game->isGameOver() && !newRecordAchieved) {
                int finalScore = game->getScore();
                if (recordManager.updateRecord(gameMode, finalScore)) {
                    newRecordAchieved = true;
                }
            }

            // Отрисовка
            renderer.clear();
            renderer.drawGrid();
            renderer.drawFood(game->getFood());
            renderer.drawSnake(game->getSnakeBody());
            renderer.drawScore(game->getScore());
            renderer.drawRecord(recordManager.getRecord(gameMode), gameMode);

            if (game->isGameOver()) {
                if (newRecordAchieved) {
                    renderer.drawNewRecord();
                }
                renderer.drawGameOver();
            }

            renderer.display();
        }

        delete game;
    }
}

void GameApplication::run() {
    while (running) {
        showMainMenu();
    }
}