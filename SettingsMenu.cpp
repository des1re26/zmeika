#include "SettingsMenu.h"

SettingsMenu::SettingsMenu(Settings& gameSettings, bool& restartFlag)
    : Menu(500, 480, "SETTINGS"), settings(gameSettings), needRestart(restartFlag) {
    menuItems = { "Cell Size: ", "Fullscreen: ", "VSync: ", "FPS Limit: ", "APPLY & BACK" };
}

std::string SettingsMenu::getValueDisplay(int index) {
    switch (index) {
    case 0: return std::to_string(settings.getCellSize()) + " px";
    case 1: return settings.isFullscreen() ? "ON" : "OFF";
    case 2: return settings.isVsync() ? "ON" : "OFF";
    case 3: return std::to_string(settings.getFpsLimit());
    default: return "";
    }
}

void SettingsMenu::drawMenu() {
    int startY = 100;
    for (size_t i = 0; i < menuItems.size(); i++) {
        sf::Color color = (i == selectedItem) ? sf::Color::Yellow : sf::Color(200, 200, 200);
        std::string displayText = menuItems[i];

        if (i < 4) {
            displayText += getValueDisplay(i);
        }

        drawText(displayText, 80, startY + i * 55, 22, color);
    }
}

void SettingsMenu::drawControls() {
    drawText("ARROWS to change | ENTER to select | ESC to exit",
        50, windowHeight - 50, 14, sf::Color(150, 150, 150));
}

int SettingsMenu::show() {
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
                if (event.key.code == sf::Keyboard::Left) {
                    if (selectedItem == 0) {
                        int newSize = settings.getCellSize() - 5;
                        if (newSize >= 20) {
                            settings.setCellSize(newSize);
                            needRestart = true;
                        }
                    }
                    if (selectedItem == 1) {
                        settings.setFullscreen(!settings.isFullscreen());
                        needRestart = true;
                    }
                    if (selectedItem == 2) {
                        settings.setVsync(!settings.isVsync());
                        needRestart = true;
                    }
                    if (selectedItem == 3) {
                        int newLimit = settings.getFpsLimit() - 15;
                        if (newLimit >= 30) {
                            settings.setFpsLimit(newLimit);
                            needRestart = true;
                        }
                    }
                }
                if (event.key.code == sf::Keyboard::Right) {
                    if (selectedItem == 0) {
                        int newSize = settings.getCellSize() + 5;
                        if (newSize <= 50) {
                            settings.setCellSize(newSize);
                            needRestart = true;
                        }
                    }
                    if (selectedItem == 1) {
                        settings.setFullscreen(!settings.isFullscreen());
                        needRestart = true;
                    }
                    if (selectedItem == 2) {
                        settings.setVsync(!settings.isVsync());
                        needRestart = true;
                    }
                    if (selectedItem == 3) {
                        int newLimit = settings.getFpsLimit() + 15;
                        if (newLimit <= 240) {
                            settings.setFpsLimit(newLimit);
                            needRestart = true;
                        }
                    }
                }
                if (event.key.code == sf::Keyboard::Enter) {
                    if (selectedItem == 4) {
                        window.close();
                        return needRestart ? 1 : 0;
                    }
                }
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                    return needRestart ? 1 : 0;
                }
            }
        }

        window.clear(sf::Color(20, 20, 40));
        drawTitle();
        drawMenu();
        drawControls();
        window.display();
    }

    return needRestart ? 1 : 0;
}