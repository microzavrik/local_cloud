#include <iostream>
#include <fstream>

size_t get_file_size_in_bytes(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 0;
    }

    std::streampos fileSize = file.tellg();
    if (fileSize == -1) {
        std::cerr << "Error getting file size." << std::endl;
        return 0;
    }

    return static_cast<size_t>(fileSize);
}