#include "Game.h"
#include <cstdlib>
#include <ctime>

// ==========  ŒÕ—“–” “Œ– ==========
Game::Game() : gameOver(false), timer(0), score(0), mode(0), justSwapped(false) {
    srand(time(nullptr));
    init();
}

// ========== »Õ»÷»¿À»«¿÷»ﬂ ==========
void Game::init() {
    snake.init();
    gameOver = false;
    score = 0;
    timer = 0;
    justSwapped = false;
    spawnFood();
}

void Game::reset() {
    init();
}

// ========== ≈ƒ¿ ==========
void Game::spawnFood() {
    do {
        food.x = rand() % 20;
        food.y = rand() % 20;
    } while (isOnSnake(food));
}

bool Game::isOnSnake(sf::Vector2i pos) {
    return snake.isOnBody(pos);
}

// ========== ”œ–¿¬À≈Õ»≈ ==========
void Game::setDirection(int newDir) {
    snake.setDirection(newDir);
}

// ========== ¬»–“”¿À‹Õ€≈ Ã≈“Œƒ€ (¡¿«Œ¬€≈) ==========
void Game::onWallCollision(sf::Vector2i& head) {
    if (head.x < 0 || head.x >= 20 || head.y < 0 || head.y >= 20) {
        gameOver = true;
    }
}

void Game::onFoodEaten() {
    snake.setGrow(true);
    score += 10;
}

bool Game::shouldCheckSelfCollision() {
    return true;
}

int Game::getSelfCollisionStartIndex() {
    if (justSwapped) {
        justSwapped = false;
        return 3;
    }
    return 1;
}

// ========== Œ¡ÕŒ¬À≈Õ»≈ ==========
void Game::update(float dt) {
    if (gameOver) return;

    timer += dt;

    if (timer >= 0.15f) {
        timer = 0;

        sf::Vector2i newHead = snake.getHead();
        int dir = snake.getDirection();

        if (dir == 0) newHead.x++;
        if (dir == 1) newHead.x--;
        if (dir == 2) newHead.y--;
        if (dir == 3) newHead.y++;

        onWallCollision(newHead);
        if (gameOver) return;

        snake.updateMove(newHead);
        snake.finishMove();

        if (snake.getHead().x == food.x && snake.getHead().y == food.y) {
            onFoodEaten();
            spawnFood();
        }

        if (shouldCheckSelfCollision()) {
            int startIndex = getSelfCollisionStartIndex();
            const auto& body = snake.getBody();
            for (size_t i = startIndex; i < body.size(); i++) {
                if (body[i].x == body.front().x && body[i].y == body.front().y) {
                    gameOver = true;
                    break;
                }
            }
        }
    }
}