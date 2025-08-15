//
// Created by ChiroYuki on 04/08/2025.
//

#ifndef PIXLENGINE_LOGGER_H
#define PIXLENGINE_LOGGER_H


#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

namespace Pixl {

#define COLOR_RESET   "\033[0m"
#define COLOR_INFO    "\033[32m"  // Green
#define COLOR_WARN    "\033[33m"  // Yellow
#define COLOR_ERROR   "\033[31m"  // Red
#define COLOR_FATAL   "\033[31m"  // Red
#define COLOR_DEBUG   "\033[36m"  // Cyan

    class Logger {
    public:
        static void info(const std::string& message);
        static void warn(const std::string& message);
        static void error(const std::string& message);
        static void debug(const std::string& message);
        static void fatal(const std::string& message);

        template<typename... Args>
        static void info(const std::string& format, Args&&... args) {
            log("INFO", COLOR_INFO, formatMessage(format, std::forward<Args>(args)...));
        }

        template<typename... Args>
        static void warn(const std::string& format, Args&&... args) {
            log("WARN", COLOR_WARN, formatMessage(format, std::forward<Args>(args)...));
        }

        template<typename... Args>
        static void error(const std::string& format, Args&&... args) {
            log("ERROR", COLOR_ERROR, formatMessage(format, std::forward<Args>(args)...));
        }

        template<typename... Args>
        static void debug(const std::string& format, Args&&... args) {
            log("DEBUG", COLOR_DEBUG, formatMessage(format, std::forward<Args>(args)...));
        }

        template<typename... Args>
        static void fatal(const std::string& format, Args&&... args) {
            log("FATAL", COLOR_FATAL, formatMessage(format, std::forward<Args>(args)...));
        }

    private:
        static void log(const std::string& level, const std::string& color, const std::string& message);
        static std::string currentTime();

        template<typename T>
        static std::string toString(T&& value) {
            std::ostringstream oss;
            oss << std::forward<T>(value);
            return oss.str();
        }

        template<typename... Args>
        static std::string formatMessage(const std::string& format, Args&&... args) {
            return formatMessageImpl(format, toString(std::forward<Args>(args))...);
        }

        static std::string formatMessageImpl(const std::string& format) {
            return format;
        }

        template<typename... Args>
        static std::string formatMessageImpl(const std::string& format, const std::string& arg, Args&&... args) {
            size_t pos = format.find("{}");
            if (pos != std::string::npos) {
                std::string result = format.substr(0, pos) + arg + format.substr(pos + 2);
                return formatMessageImpl(result, std::forward<Args>(args)...);
            }
            return format;
        }
    };

}

#endif //PIXLENGINE_LOGGER_H
