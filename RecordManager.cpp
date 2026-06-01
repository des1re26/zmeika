#include "RecordManager.h"
#include <fstream>
#include <iostream>

RecordManager::RecordManager() : filename("records.txt") {
    loadRecords();
}

void RecordManager::loadRecords() {
    std::ifstream file(filename);
    if (file.is_open()) {
        int mode, score;
        while (file >> mode >> score) {
            records[mode] = score;
        }
        file.close();
    }

    // ≈сли нет записей, инициализируем нул€ми
    for (int i = 0; i <= 2; i++) {
        if (records.find(i) == records.end()) {
            records[i] = 0;
        }
    }
}

void RecordManager::saveRecords() {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& pair : records) {
            file << pair.first << " " << pair.second << std::endl;
        }
        file.close();
    }
}

int RecordManager::getRecord(int mode) {
    auto it = records.find(mode);
    if (it != records.end()) {
        return it->second;
    }
    return 0;
}

bool RecordManager::updateRecord(int mode, int score) {
    if (score > records[mode]) {
        records[mode] = score;
        saveRecords();
        return true;
    }
    return false;
}

std::string RecordManager::getModeName(int mode) {
    switch (mode) {
    case 0: return "CLASSIC";
    case 1: return "WRAP";
    case 2: return "SWAP";
    default: return "UNKNOWN";
    }
}