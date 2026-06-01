#include "PauseMenu.h"
#include "SettingsMenu.h"

PauseMenu::PauseMenu(Settings& gameSettings, Renderer* gameRenderer)
    : Menu(400, 350, "PAUSE"), settings(gameSettings), renderer(gameRenderer) {
    menuItems = { "RESUME", "SETTINGS", "MAIN MENU" };
}

int PauseMenu::show() {
    window.create(sf::VideoMode(windowWidth, windowHeight), title);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return 1; // Продолжаем игру
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
                    if (selectedItem == 0) return 1; // RESUME
                    if (selectedItem == 1) {
                        // SETTINGS - показываем меню настроек
                        bool needRecreate = false;
                        SettingsMenu settingsMenu(settings, needRecreate);
                        settingsMenu.show();

                        // Если изменились настройки окна - обновляем рендерер
                        if (needRecreate && renderer) {
                            renderer->reloadWindow();
                        }
                        return 1; // Возвращаемся в игру
                    }
                    if (selectedItem == 2) return 2; // MAIN MENU
                }
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                    return 1; // Resume on Escape
                }
            }
        }

        window.clear(sf::Color(20, 20, 30, 200));
        drawTitle();
        drawMenu();
        drawControls();
        window.display();
    }

    return 1;
}