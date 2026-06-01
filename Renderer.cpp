#include "Renderer.h"
#include "Settings.h"

Renderer::Renderer(Settings& gameSettings)
    : settings(&gameSettings), cellSize(gameSettings.getCellSize()),
    gridWidth(gameSettings.getGridWidth()), gridHeight(gameSettings.getGridHeight()),
    windowWidth(gameSettings.getWindowWidth()), windowHeight(gameSettings.getWindowHeight()) {
    font.loadFromFile("ArialRegular.ttf");
    reloadWindow();
}

Renderer::~Renderer() {
    if (window.isOpen()) {
        window.close();
    }
}

float Renderer::getOffsetX() {
    if (settings->isFullscreen()) {
        sf::Vector2u desktopSize = window.getSize();
        return (desktopSize.x - windowWidth) / 2.0f;
    }
    return 0;
}

float Renderer::getOffsetY() {
    if (settings->isFullscreen()) {
        sf::Vector2u desktopSize = window.getSize();
        return (desktopSize.y - windowHeight) / 2.0f;
    }
    return 0;
}

void Renderer::applySettings() {
    window.setVerticalSyncEnabled(settings->isVsync());
    window.setFramerateLimit(settings->getFpsLimit());
}

void Renderer::reloadWindow() {
    bool wasOpen = window.isOpen();

    cellSize = settings->getCellSize();
    windowWidth = settings->getWindowWidth();
    windowHeight = settings->getWindowHeight();

    if (wasOpen) {
        sf::Vector2i oldPosition = window.getPosition();
        window.close();

        window.create(settings->getVideoMode(), settings->getWindowTitle(), settings->getWindowStyle());
        applySettings();

        if (!settings->isFullscreen() && wasOpen) {
            window.setPosition(oldPosition);
        }
        else if (!settings->isFullscreen()) {
            sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
            window.setPosition(sf::Vector2i(
                (desktop.width - windowWidth) / 2,
                (desktop.height - windowHeight) / 2
            ));
        }
    }
    else {
        window.create(settings->getVideoMode(), settings->getWindowTitle(), settings->getWindowStyle());
        applySettings();

        if (!settings->isFullscreen()) {
            sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
            window.setPosition(sf::Vector2i(
                (desktop.width - windowWidth) / 2,
                (desktop.height - windowHeight) / 2
            ));
        }
    }

    if (settings->isFullscreen()) {
        float offsetX = getOffsetX();
        float offsetY = getOffsetY();
        sf::View view(sf::FloatRect(offsetX, offsetY, windowWidth, windowHeight));
        window.setView(view);
    }
    else {
        window.setView(sf::View(sf::FloatRect(0, 0, windowWidth, windowHeight)));
    }
}

void Renderer::clear() {
    if (settings->isFullscreen()) {
        window.clear(sf::Color::Black);

        sf::RectangleShape gameArea(sf::Vector2f(windowWidth, windowHeight));
        gameArea.setFillColor(sf::Color(20, 20, 30));
        gameArea.setPosition(getOffsetX(), getOffsetY());
        window.draw(gameArea);
    }
    else {
        window.clear(sf::Color(20, 20, 30));
    }
}

void Renderer::drawGrid() {
    float offsetX = getOffsetX();
    float offsetY = getOffsetY();

    for (int i = 0; i <= gridWidth; i++) {
        sf::RectangleShape line(sf::Vector2f(1, windowHeight));
        line.setPosition(offsetX + i * cellSize, offsetY);
        line.setFillColor(sf::Color(40, 40, 50));
        window.draw(line);
    }
    for (int i = 0; i <= gridHeight; i++) {
        sf::RectangleShape line(sf::Vector2f(windowWidth, 1));
        line.setPosition(offsetX, offsetY + i * cellSize);
        line.setFillColor(sf::Color(40, 40, 50));
        window.draw(line);
    }
}

void Renderer::drawSnake(const std::deque<sf::Vector2i>& snake) {
    float offsetX = getOffsetX();
    float offsetY = getOffsetY();

    for (size_t i = 0; i < snake.size(); i++) {
        sf::RectangleShape rect(sf::Vector2f(cellSize - 2, cellSize - 2));
        rect.setPosition(offsetX + snake[i].x * cellSize + 1,
            offsetY + snake[i].y * cellSize + 1);

        if (i == 0) {
            rect.setFillColor(sf::Color::Green);
        }
        else {
            rect.setFillColor(sf::Color(0, 180, 0));
        }

        window.draw(rect);
    }
}

void Renderer::drawFood(const sf::Vector2i& food) {
    float offsetX = getOffsetX();
    float offsetY = getOffsetY();

    sf::CircleShape foodCircle(cellSize / 2 - 4);
    foodCircle.setFillColor(sf::Color::Red);
    foodCircle.setPosition(offsetX + food.x * cellSize + 4,
        offsetY + food.y * cellSize + 4);
    window.draw(foodCircle);
}

void Renderer::drawScore(int score) {
    float offsetX = getOffsetX();
    float offsetY = getOffsetY();

    if (font.getInfo().family != "") {
        // Фон для счета
        sf::RectangleShape scoreBg(sf::Vector2f(120, 40));
        scoreBg.setFillColor(sf::Color(0, 0, 0, 150));
        scoreBg.setPosition(offsetX + 10, offsetY + 10);
        window.draw(scoreBg);

        // Текст "SCORE"
        sf::Text scoreLabel;
        scoreLabel.setFont(font);
        scoreLabel.setString("SCORE");
        scoreLabel.setCharacterSize(16);
        scoreLabel.setFillColor(sf::Color(200, 200, 200));
        scoreLabel.setPosition(offsetX + 15, offsetY + 12);
        window.draw(scoreLabel);

        // Значение счета
        sf::Text scoreValue;
        scoreValue.setFont(font);
        scoreValue.setString(std::to_string(score));
        scoreValue.setCharacterSize(24);
        scoreValue.setFillColor(sf::Color::Yellow);
        scoreValue.setStyle(sf::Text::Bold);
        scoreValue.setPosition(offsetX + 70, offsetY + 10);
        window.draw(scoreValue);
    }
    else {
        // Если нет шрифта - рисуем примитивами
        int tempScore = score;
        int x = offsetX + 10;
        int y = offsetY + 10;

        // Рисуем фон
        sf::RectangleShape bg(sf::Vector2f(100, 30));
        bg.setFillColor(sf::Color(0, 0, 0, 150));
        bg.setPosition(x, y);
        window.draw(bg);

        // Рисуем кружочки вместо цифр
        for (int i = 0; i < tempScore / 10 && i < 10; i++) {
            sf::CircleShape dot(5);
            dot.setFillColor(sf::Color::Yellow);
            dot.setPosition(x + 10 + i * 8, y + 10);
            window.draw(dot);
        }
    }
}

void Renderer::drawGameOver() {
    float offsetX = getOffsetX();
    float offsetY = getOffsetY();

    sf::RectangleShape overlay(sf::Vector2f(windowWidth, windowHeight));
    overlay.setFillColor(sf::Color(0, 0, 0, 200));
    overlay.setPosition(offsetX, offsetY);
    window.draw(overlay);

    if (font.getInfo().family != "") {
        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setString("GAME OVER");
        gameOverText.setCharacterSize(60);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setStyle(sf::Text::Bold);

        sf::FloatRect bounds = gameOverText.getLocalBounds();
        gameOverText.setPosition(offsetX + windowWidth / 2 - bounds.width / 2,
            offsetY + windowHeight / 2 - bounds.height / 2 - 40);
        window.draw(gameOverText);

        sf::Text restartText;
        restartText.setFont(font);
        restartText.setString("Press R to restart | ESC to exit");
        restartText.setCharacterSize(20);
        restartText.setFillColor(sf::Color(200, 200, 200));

        sf::FloatRect restartBounds = restartText.getLocalBounds();
        restartText.setPosition(offsetX + windowWidth / 2 - restartBounds.width / 2,
            offsetY + windowHeight / 2 + 40);
        window.draw(restartText);
    }
}

void Renderer::display() {
    window.display();
}

bool Renderer::isOpen() {
    return window.isOpen();
}

void Renderer::close() {
    window.close();
}

void Renderer::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        if (event.type == sf::Event::Resized && !settings->isFullscreen()) {
            sf::FloatRect view(0, 0, event.size.width, event.size.height);
            window.setView(sf::View(view));
        }
    }
}
void Renderer::drawRecord(int record, int mode) {
    float offsetX = getOffsetX();
    float offsetY = getOffsetY();

    if (font.getInfo().family != "") {
        // Фон для рекорда
        sf::RectangleShape recordBg(sf::Vector2f(180, 40));
        recordBg.setFillColor(sf::Color(0, 0, 0, 150));
        recordBg.setPosition(offsetX + windowWidth - 190, offsetY + 10);
        window.draw(recordBg);

        // Текст "BEST"
        sf::Text bestLabel;
        bestLabel.setFont(font);
        bestLabel.setString("BEST");
        bestLabel.setCharacterSize(14);
        bestLabel.setFillColor(sf::Color(200, 200, 200));
        bestLabel.setPosition(offsetX + windowWidth - 185, offsetY + 12);
        window.draw(bestLabel);

        // Значение рекорда
        sf::Text recordValue;
        recordValue.setFont(font);

        // Название режима
        std::string modeName;
        switch (mode) {
        case 0: modeName = "CLS"; break;
        case 1: modeName = "WRP"; break;
        case 2: modeName = "SWP"; break;
        default: modeName = ""; break;
        }

        recordValue.setString(modeName + ": " + std::to_string(record));
        recordValue.setCharacterSize(18);
        recordValue.setFillColor(sf::Color(255, 215, 0)); // Золотой
        recordValue.setStyle(sf::Text::Bold);
        recordValue.setPosition(offsetX + windowWidth - 180, offsetY + 28);
        window.draw(recordValue);
    }
}

void Renderer::drawNewRecord() {
    float offsetX = getOffsetX();
    float offsetY = getOffsetY();

    if (font.getInfo().family != "") {
        sf::Text newRecordText;
        newRecordText.setFont(font);
        newRecordText.setString("NEW RECORD!");
        newRecordText.setCharacterSize(24);
        newRecordText.setFillColor(sf::Color(255, 215, 0));
        newRecordText.setStyle(sf::Text::Bold);

        sf::FloatRect bounds = newRecordText.getLocalBounds();
        newRecordText.setPosition(offsetX + windowWidth / 2 - bounds.width / 2,
            offsetY + 60);
        window.draw(newRecordText);
    }
}