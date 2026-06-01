#pragma once
#include <SFML/Graphics.hpp>
#include <deque>

class Settings;

class Renderer {
private:
    sf::RenderWindow window;
    Settings* settings;
    int cellSize;
    int gridWidth;
    int gridHeight;
    int windowWidth;
    int windowHeight;
    sf::Font font;  // Добавляем шрифт

    void applySettings();
    float getOffsetX();
    float getOffsetY();

public:
    Renderer(Settings& gameSettings);
    ~Renderer();

    void clear();
    void drawSnake(const std::deque<sf::Vector2i>& snake);
    void drawFood(const sf::Vector2i& food);
    void drawGrid();
    void drawScore(int score);  // Новый метод
    void drawGameOver();
    void display();
    bool isOpen();
    void close();
    void handleEvents();
    void reloadWindow();

    sf::RenderWindow& getWindow() { return window; }

    void drawRecord(int record, int mode);
    void drawNewRecord();
};