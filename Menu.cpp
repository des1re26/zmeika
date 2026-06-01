#include "Menu.h"

Menu::Menu(int width, int height, const std::string& menuTitle)
    : windowWidth(width), windowHeight(height), selectedItem(0), title(menuTitle) {
}

Menu::~Menu() {
    if (window.isOpen()) {
        window.close();
    }
}

void Menu::drawText(const std::string& text, int x, int y, int size, sf::Color color) {
    sf::Font font;
    font.loadFromFile("ArialRegular.ttf");

    sf::Text sfText;
    if (font.getInfo().family != "") {
        sfText.setFont(font);
    }
    sfText.setString(text);
    sfText.setCharacterSize(size);
    sfText.setFillColor(color);
    sfText.setPosition(x, y);
    window.draw(sfText);
}

void Menu::drawTitle() {
    drawText(title, windowWidth / 2 - title.length() * 12, 50, 40, sf::Color::Green);
}

void Menu::drawMenu() {
    int startY = 120;
    for (size_t i = 0; i < menuItems.size(); i++) {
        sf::Color color = (i == selectedItem) ? sf::Color::Yellow : sf::Color::White;
        drawText(menuItems[i], windowWidth / 2 - 100, startY + i * 50, 24, color);
    }
}

void Menu::drawControls() {
    drawText("Use UP/DOWN to navigate | ENTER to select | ESC to exit",
        40, windowHeight - 50, 14, sf::Color(150, 150, 150));
}

int Menu::show() {
    window.create(sf::VideoMode(windowWidth, windowHeight), title);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return 0;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    selectedItem = (selectedItem - 1 + menuItems.size()) % menuItems.size();
                }
                if (event.key.code == sf::Keyboard::Down) {
                    selectedItem = (selectedItem + 1) % menuItems.size();
                }
                if (event.key.code == sf::Keyboard::Enter) {
                    window.close();
                    return selectedItem + 1;
                }
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                    return 0;
                }
            }
        }

        window.clear(sf::Color(20, 20, 30));
        drawTitle();
        drawMenu();
        drawControls();
        window.display();
    }

    return 0;
}