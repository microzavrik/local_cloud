#ifndef LOG_HPP
#define LOG_HPP

#include <string>

namespace logger
{
    void logInfo(const std::string& message);
    void logWarning(const std::string& message);
    void logError(const std::string& message);
}

#endif