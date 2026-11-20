

#include "../include/FileManager.h"

#include <fstream>
#include <sstream>

bool FileManager::createFile(
    const std::filesystem::path& path,
    const std::string& content
) {

    std::ofstream file(path);

    if (!file.is_open()) {
        return false;
    }

    file << content;

    file.close();

    return true;
}


bool FileManager::readFile(
    const std::filesystem::path& path,
    std::string& content
) {

    std::ifstream file(path);

    if (!file.is_open()) {
        return false;
    }

    std::stringstream buffer;

    buffer << file.rdbuf();

    content = buffer.str();

    file.close();

    return true;
}
