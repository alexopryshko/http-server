#include "RequestHeader.h"
#include "Utilities.h"


RequestHeader::RequestHeader(std::string data) {
    this->parse(data);
}

void RequestHeader::parse(std::string data) {
    std::vector<std::string> splitData = Utilities::split(data, "\n");
    std::vector<std::string> splitLine = Utilities::split(splitData[0], " ");
    method = splitLine[0];
    path = splitLine[1];
    httpVersion = splitLine[2];
}