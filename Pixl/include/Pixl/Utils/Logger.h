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
        static void info(const std::string& message);

        static void warn(const std::string& message);

        static void error(const std::string& message);

        static void debug(const std::string& message);

    private:
        static void log(const std::string& level, const std::string& color, const std::string& message);

        static std::string currentTime();
    };

}

#endif //PIXLENGINE_LOGGER_H
