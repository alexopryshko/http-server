#include "request_header.h"
#include <iostream>

std::regex request_line_regex("(GET|PUT|POST|DELETE|HEAD)\\s(\\/[^\\?]*)\\?{0,1}(.*)\\s(\\S+)");

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
    std::smatch request_line;
    if (std::regex_search(token, request_line, request_line_regex) && request_line.size() > 4) {
        method = request_line[1];
        path = path_decoder(request_line[2]);
        http_version = request_line[4];
    }
    else {
        //delete (data);
        return false;
    }
    //delete (data);
    return true;
}