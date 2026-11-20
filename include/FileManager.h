

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <filesystem>

class FileManager {

public:

    static bool createFile(
        const std::filesystem::path& path,
        const std::string& content
    );

    static bool readFile(
        const std::filesystem::path& path,
        std::string& content
    );

};

#endif

