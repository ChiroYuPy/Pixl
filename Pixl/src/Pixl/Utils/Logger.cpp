//
// Created by ChiroYuki on 04/08/2025.
//

#include "Pixl/Utils/Logger.h"

namespace Pixl {

    void Logger::info(const std::string &message) {
        log("INFO", COLOR_INFO, message);
    }

    void Logger::warn(const std::string &message) {
        log("WARN", COLOR_WARN, message);
    }

    void Logger::error(const std::string &message) {
        log("ERROR", COLOR_ERROR, message);
    }

    void Logger::debug(const std::string &message) {
        log("DEBUG", COLOR_DEBUG, message);
    }

    void Logger::fatal(const std::string &message) {
        log("FATAL", COLOR_FATAL, message);
    }

    void Logger::log(const std::string &level, const std::string &color, const std::string &message) {
        std::cout << "[" << currentTime() << "] "
                  << color << "[" << level << "]" << COLOR_RESET << " "
                  << message << std::endl;
    }

    std::string Logger::currentTime() {
        using namespace std::chrono;
        auto now = system_clock::now();
        std::time_t time = system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&time);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%H:%M:%S");
        return oss.str();
    }

}