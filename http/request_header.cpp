#include "request_header.h"
#include <iostream>
std::regex request_line_regex("(GET|PUT|POST|DELETE|HEAD)\\s(.*)\\s(\\S+)");

bool request_header::parse(unsigned char* data, long size) {
    size_t pos = 0;
    std::string buffer((char*)data);
    std::string token;
    if ((pos = buffer.find("\n")) != std::string::npos) {
        token = buffer.substr(0, pos);
    }
    else {
        return false;
    }
    std::cout << token << "\n";
    std::smatch request_line;
    if (std::regex_search(token, request_line, request_line_regex) && request_line.size() > 3) {
        method = request_line[1];
        std::cout << method << "\n";
        path = request_line[2];
        std::cout << path << "\n";
        http_version = request_line[3];
        std::cout << http_version << "\n";
    }
    else {
        return false;
    }
    return true;
}