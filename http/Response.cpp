#include "response.h"

response::response() {
    responseHeader = NULL;
    messageBody = NULL;
}

response::~response() {
    delete(responseHeader);
    delete []messageBody;
}

void response::setBody(std::string contentType, char *messageBody, int length) {
    this->messageBody = messageBody;
    responseHeader->setContentLength(length);
    responseHeader->setContentType(contentType);
}

void response::setHeader(response_header *responseHeader) {
    this->responseHeader = responseHeader;
}

char *response::serialize() {
    std::string header = responseHeader->getHeader();
    char *buffer = new char[header.size() + responseHeader->getContentLength()];
    strcat(buffer, header.c_str());
    strcat(buffer, messageBody);
    return buffer;
}