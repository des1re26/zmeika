#include "Settings.h"

Settings::Settings()
    : cellSize(30), gridWidth(20), gridHeight(20),
    fullscreen(false), vsync(true), fpsLimit(60),
    windowTitle("Snake Game") {
    updateWindowSize();
}

void Settings::setCellSize(int size) {
    if (size >= 20 && size <= 50) {
        cellSize = size;
        updateWindowSize();
    }
}

void Settings::setFullscreen(bool enabled) {
    fullscreen = enabled;
}

void Settings::setVsync(bool enabled) {
    vsync = enabled;
}

void Settings::setFpsLimit(int limit) {
    if (limit > 0) {
        fpsLimit = limit;
    }
}

void Settings::updateWindowSize() {
    windowWidth = gridWidth * cellSize;
    windowHeight = gridHeight * cellSize;
}

sf::VideoMode Settings::getVideoMode() const {
    if (fullscreen) {
        return sf::VideoMode::getDesktopMode();
    }
    return sf::VideoMode(windowWidth, windowHeight);
}

sf::Uint32 Settings::getWindowStyle() const {
    if (fullscreen) {
        return sf::Style::Fullscreen;
    }
    return sf::Style::Titlebar | sf::Style::Close;
}