#pragma once
#include <string>
#include <regex>
#include "utility.h"

class request_header {
public:
    request_header() {};

    std::string get_path() { return path; }
    std::string get_method() { return method; }
    std::string get_http_version() { return http_version; }
    bool parse(unsigned char* data, long size);

private:
    std::string method;
    std::string path;
    std::string http_version;

};
