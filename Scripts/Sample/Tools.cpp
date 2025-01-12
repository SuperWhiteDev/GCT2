#include <filesystem>
#include "Tools.hpp"

#pragma warning(disable : 4996)

std::string GetPathFromPATH(const std::string & folderName) {
    // Get the value of the PATH environment variable
    const char* path = std::getenv("PATH");
    if (path == nullptr) {
        return ""; // Return empty string if PATH variable is not found
    }

    std::string pathString(path);
    std::stringstream ss(pathString);
    std::string item;

    // Separate paths by separator
#ifdef _WIN32
    const std::string delimiter = ";";
#else
    const std::string delimiter = ":";
#endif

    while (std::getline(ss, item, delimiter[0])) {
        // Check if the folder name matches the found path
        std::filesystem::path dir(item);
        if (dir.filename() == folderName) {
            return dir.string(); // Return the full path to the folder
        }
    }

    return ""; // Return empty string if the folder is not found
}