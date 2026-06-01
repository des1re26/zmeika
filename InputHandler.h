#pragma once

#include <SFML/Graphics.hpp>

class InputHandler {
private:
    bool upPressed;
    bool downPressed;
    bool leftPressed;
    bool rightPressed;
    bool escapePressed;
    bool restartPressed;
    bool exitPressed;

public:
    InputHandler();
    void update();
    void handleEvents(sf::RenderWindow& window);

    int getDirection();
    bool isEscapePressed();
    bool isRestartPressed();
    bool isExitPressed();
    void clearEscapeFlag(); // Добавляем для очистки флага
};
