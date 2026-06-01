#pragma once
#include <string>
#include <map>

class RecordManager {
private:
    std::map<int, int> records; // режим -> рекорд
    std::string filename;

    void loadRecords();
    void saveRecords();

public:
    RecordManager();

    int getRecord(int mode);      // получить рекорд для режима (0-classic, 1-wrap, 2-swap)
    bool updateRecord(int mode, int score); // обновить рекорд, вернуть true если новый рекорд
    std::string getModeName(int mode);
};
