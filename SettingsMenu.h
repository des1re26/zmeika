#pragma once
#include "Menu.h"
#include "Settings.h"

class SettingsMenu : public Menu {
private:
    Settings& settings;
    bool& needRestart;

    void drawMenu() override;
    void drawControls() override;
    std::string getValueDisplay(int index);

public:
    SettingsMenu(Settings& gameSettings, bool& restartFlag);
    int show() override;
};