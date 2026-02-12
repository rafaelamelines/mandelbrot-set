#pragma once

#include <ctime>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#define MANDEL_LOG(...) logger::log(__FILE__, __LINE__, __VA_ARGS__)
#define MANDEL_WARN(...) logger::warn(__FILE__, __LINE__, __VA_ARGS__)
#define MANDEL_ERROR(...) logger::error(__FILE__, __LINE__, __VA_ARGS__)

namespace logger {
    std::string pad(int n);

    template<typename... Args>
    inline void log(const char* file, int line, Args&&... args) {
        std::string stringFile(file);
        std::string_view filename(stringFile.substr(stringFile.find_last_of("/\\") + 1));

        time_t timestamp = time(&timestamp);
        struct tm datetime = *localtime(&timestamp);

        std::cout << "[" << pad(datetime.tm_hour) << ":" << pad(datetime.tm_min) << ":" << pad(datetime.tm_sec) << "] " << filename << " at line " << line << ": ";
        (std::cout << ... << args) << "\n";
    }

    template<typename... Args>
    inline void warn(const char* file, int line, Args&&... args) {
        std::string stringFile(file);
        std::string_view filename(stringFile.substr(stringFile.find_last_of("/\\") + 1));

        time_t timestamp = time(&timestamp);
        struct tm datetime = *localtime(&timestamp);

        std::cout << "\033[93m[" << pad(datetime.tm_hour) << ":" << pad(datetime.tm_min) << ":" << pad(datetime.tm_sec) << "] " << filename << " at line " << line << ": ";
        (std::cout << ... << args) << "\033[m\n";
    }

    template<typename... Args>
    inline void error(const char* file, int line, Args&&... args) {
        std::string stringFile(file);
        std::string_view filename(stringFile.substr(stringFile.find_last_of("/\\") + 1));

        time_t timestamp = time(&timestamp);
        struct tm datetime = *localtime(&timestamp);

        std::cout << "\033[91m[" << pad(datetime.tm_hour) << ":" << pad(datetime.tm_min) << ":" << pad(datetime.tm_sec) << "] " << filename << " at line " << line << ": ";
        (std::cout << ... << args) << "\033[m\n";
    }

    void GLFWErrorCallback(int code, const char* description);
}