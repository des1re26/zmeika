#include "InputHandler.h"

InputHandler::InputHandler()
    : upPressed(false), downPressed(false), leftPressed(false), rightPressed(false),
    escapePressed(false), restartPressed(false), exitPressed(false) {
}

void InputHandler::update() {
    upPressed = false;
    downPressed = false;
    leftPressed = false;
    rightPressed = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) upPressed = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) downPressed = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) leftPressed = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) rightPressed = true;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) escapePressed = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) restartPressed = true;

    // Добавляем обработку Esc как exit при Game Over
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        exitPressed = true;
    }
}

void InputHandler::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

int InputHandler::getDirection() {
    if (rightPressed) return 0;
    if (leftPressed) return 1;
    if (upPressed) return 2;
    if (downPressed) return 3;
    return -1;
}

bool InputHandler::isEscapePressed() {
    if (escapePressed) {
        escapePressed = false;
        return true;
    }
    return false;
}

bool InputHandler::isRestartPressed() {
    if (restartPressed) {
        restartPressed = false;
        return true;
    }
    return false;
}

bool InputHandler::isExitPressed() {
    if (exitPressed) {
        exitPressed = false;
        return true;
    }
    return false;
}

void InputHandler::clearEscapeFlag() {
    escapePressed = false;
}