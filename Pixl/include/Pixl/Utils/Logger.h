//
// Created by ChiroYuki on 04/08/2025.
//

#ifndef PIXLENGINE_LOGGER_H
#define PIXLENGINE_LOGGER_H

#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace Pixl {

#define COLOR_RESET   "\033[0m"
#define COLOR_INFO    "\033[32m"  // Green
#define COLOR_WARN    "\033[33m"  // Yellow
#define COLOR_ERROR   "\033[31m"  // Red
#define COLOR_DEBUG   "\033[36m"  // Cyan

    class Logger {
    public:
        static void info(const std::string& message) {
            log("INFO", COLOR_INFO, message);
        }

        static void warn(const std::string& message) {
            log("WARN", COLOR_WARN, message);
        }

        static void error(const std::string& message) {
            log("ERROR", COLOR_ERROR, message);
        }

        static void debug(const std::string& message) {
            log("DEBUG", COLOR_DEBUG, message);
        }

    private:
        static void log(const std::string& level, const std::string& color, const std::string& message) {
            std::cout << "[" << currentTime() << "] "
                      << color << "[" << level << "]" << COLOR_RESET << " "
                      << message << std::endl;
        }

        static std::string currentTime() {
            using namespace std::chrono;
            auto now = system_clock::now();
            std::time_t time = system_clock::to_time_t(now);
            std::tm tm = *std::localtime(&time);

            std::ostringstream oss;
            oss << std::put_time(&tm, "%H:%M:%S");
            return oss.str();
        }
    };

}

#endif //PIXLENGINE_LOGGER_H
