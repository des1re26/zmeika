#include "GameModeMenu.h"

GameModeMenu::GameModeMenu()
    : Menu(550, 450, "SELECT GAME MODE") {
    menuItems = { "CLASSIC (walls kill you)",
                 "WRAP (teleport through walls)",
                 "SWAP (head & tail swap)",
                 "BACK" };
}

int GameModeMenu::show() {
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
                    if (selectedItem == 3) return 0; // BACK
                    return selectedItem + 1; // 1,2,3
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