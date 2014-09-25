#include "utility.h"
#include <regex>

std::string get_file_type(std::string path) {
    std::regex extension_regex("\\.([\\w]+)\\/?$");
    std::smatch extension;
    if (std::regex_search(path, extension, extension_regex) && extension.size() > 0) {
        return extension[1];
    }
}