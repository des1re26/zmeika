#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
protected:
    sf::RenderWindow window;
    int windowWidth;
    int windowHeight;
    int selectedItem;
    std::vector<std::string> menuItems;
    std::string title;

    virtual void drawTitle();
    virtual void drawMenu();
    virtual void drawControls();
    void drawText(const std::string& text, int x, int y, int size, sf::Color color);

public:
    Menu(int width, int height, const std::string& menuTitle);
    virtual ~Menu();
    virtual int show(); // ¬озвращает выбранный пункт (0 - выход/назад)
};