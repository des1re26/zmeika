#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Settings {
private:
    int cellSize;
    int gridWidth;
    int gridHeight;
    int windowWidth;
    int windowHeight;
    bool fullscreen;
    bool vsync;
    int fpsLimit;
    std::string windowTitle;

public:
    Settings();

    // Геттеры
    int getCellSize() const { return cellSize; }
    int getGridWidth() const { return gridWidth; }
    int getGridHeight() const { return gridHeight; }
    int getWindowWidth() const { return windowWidth; }
    int getWindowHeight() const { return windowHeight; }
    bool isFullscreen() const { return fullscreen; }
    bool isVsync() const { return vsync; }
    int getFpsLimit() const { return fpsLimit; }
    std::string getWindowTitle() const { return windowTitle; }

    // Сеттеры
    void setCellSize(int size);
    void setFullscreen(bool enabled);
    void setVsync(bool enabled);
    void setFpsLimit(int limit);

    // Обновить размер окна на основе настроек
    void updateWindowSize();

    // Создать видеорежим
    sf::VideoMode getVideoMode() const;

    // Стили окна
    sf::Uint32 getWindowStyle() const;
};