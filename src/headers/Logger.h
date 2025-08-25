//
// Created by issbe on 17/08/2025.
//
#pragma once

#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <iostream>
#include <ctime>
#include <deque>
#include <sstream>
#include <filesystem>
#include <vector>

enum LOG_LEVEL {
    DEBUG,
    INFO,
    ERROR,
    WARNING
};

class Logger {
public:
    Logger(const std::string filename) {
        if (std::filesystem::exists(filename)) {
            file.open(filename, std::ios::app);
        }else {
            file.open(filename);
        }

        if (!file.is_open()) {
            std::cerr << "Failed to open the logger" << std::endl;
        }
    }

    ~Logger() {
        Log(INFO, "Closing the logger !");
        file.close();
    }

    void Log(LOG_LEVEL level, std::string message) {
        // time - level - message
        time_t now = time(0);
        tm* timeinfo = localtime(&now);
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp),
                 "%Y-%m-%d %H:%M:%S", timeinfo);

        std::ostringstream str;
        str << "[ " << timestamp << " ] - " << GetStringLogLevel(level) << " : " << message << std::endl;
        std::cout << str.str();

        history.push_back(str.str());
        if (file.is_open()) {
            file << str.str();
            file.flush(); // write immediately

        }
    }

    std::deque<std::string> GetLogHistory(){return history;}

private:
    std::ofstream file;
    std::deque<std::string> history;
private:
    std::string GetStringLogLevel(LOG_LEVEL level) {
        switch (level) {
            case DEBUG: return "[ DEBUG ]";
            case INFO: return "[ INFO ]";
            case ERROR: return "[ ERROR ]";
            case WARNING: return "[ WARNING ]";
            default: return "Unknown";
        }
    }
};


#endif //LOGGER_H
