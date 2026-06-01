#pragma once
#include <deque>
#include <SFML/System/Vector2.hpp>
#include "Snake.h"

class Game {
private:
    Snake snake;
    sf::Vector2i food;
    bool gameOver;
    float timer;
    int score;
    int mode;
    bool justSwapped;

    bool isOnSnake(sf::Vector2i pos);

protected:
    virtual void onWallCollision(sf::Vector2i& head);
    virtual void onFoodEaten();
    virtual bool shouldCheckSelfCollision();
    virtual int getSelfCollisionStartIndex();

    void spawnFood();

    // Доступ для наследников
    Snake& getSnake() { return snake; }
    sf::Vector2i& getFoodRef() { return food; }
    bool& getGameOverRef() { return gameOver; }
    float& getTimer() { return timer; }
    int& getScoreRef() { return score; }
    bool& getJustSwapped() { return justSwapped; }

public:
    Game();
    virtual ~Game() {}

    void init();
    void reset();
    void setDirection(int newDir);
    void setMode(int newMode) { mode = newMode; }
    virtual void update(float dt);

    // Геттеры для отрисовки - возвращаем body змейки
    const std::deque<sf::Vector2i>& getSnakeBody() const { return snake.getBody(); }
    const sf::Vector2i& getFood() const { return food; }
    bool isGameOver() const { return gameOver; }
    int getScore() const { return score; }
    int getMode() const { return mode; }


};