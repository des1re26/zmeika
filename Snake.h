#pragma once
#include <deque>
#include <SFML/System/Vector2.hpp>

class Snake {
private:
    std::deque<sf::Vector2i> body;
    int dir;
    int nextDir;
    bool growFlag;
    int gridWidth;
    int gridHeight;

public:
    Snake(int width = 20, int height = 20);
    ~Snake() {}

    // Инициализация
    void init();
    void reset();

    // Движение
    void setDirection(int newDir);
    void updateMove(sf::Vector2i newHead);
    void finishMove();

    // Рост
    void setGrow(bool grow) { growFlag = grow; }
    bool isGrowing() const { return growFlag; }

    // Геттеры
    sf::Vector2i getHead() const { return body.front(); }
    const std::deque<sf::Vector2i>& getBody() const { return body; }
    int getDirection() const { return dir; }
    int getNextDirection() const { return nextDir; }
    int getLength() const { return body.size(); }

    // Проверки
    bool checkSelfCollision() const;
    bool isOnBody(sf::Vector2i pos) const;

    // Для наследников
    std::deque<sf::Vector2i>& getBodyRef() { return body; }
    int& getDirRef() { return dir; }
    int& getNextDirRef() { return nextDir; }
};
