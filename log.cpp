#include "log.hpp"
#include <iostream>
#include <chrono>
#include <ctime>

namespace logger
{
    void logInfo(const std::string& message)
    {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << "\033[1;32m[INFO " << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S") << "] " << message << "\033[0m\n";
    }
    
    void logWarning(const std::string& message)
    {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << "\033[1;33m[WARNING " << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S") << "] " << message << "\033[0m\n";
    }
    
    void logError(const std::string& message)
    {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << "\033[1;31m[ERROR " << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S") << "] " << message << "\033[0m\n";
    }
}