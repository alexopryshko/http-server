#include "request_header.h"
#include "utilities.h"

request_header::request_header(std::string data) {
    this->parse(data);
}

void request_header::parse(std::string data) {
    std::vector<std::string> splitData = utilities::split(data, "\n");
    std::vector<std::string> splitLine = utilities::split(splitData[0], " ");
    method = splitLine[0];
    path = splitLine[1];
    httpVersion = splitLine[2];
}