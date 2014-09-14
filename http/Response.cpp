#include "Response.h"

Response::Response() {
    responseHeader = NULL;
    messageBody = NULL;
}

Response::~Response() {
    delete(responseHeader);
    delete []messageBody;
}

void Response::setBody(std::string contentType, char *messageBody, int length) {
    this->messageBody = messageBody;
    responseHeader->setContentLength(length);
    responseHeader->setContentType(contentType);
}

void Response::setHeader(ResponseHeader *responseHeader) {
    this->responseHeader = responseHeader;
}

char *Response::serialize() {
    std::string header = responseHeader->getHeader();
    char *buffer = new char[header.size() + responseHeader->getContentLength()];
    strcat(buffer, header.c_str());
    strcat(buffer, messageBody);
    return buffer;
}