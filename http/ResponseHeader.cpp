#include <Foundation/Foundation.h>
#include "ResponseHeader.h"

ResponseHeader::ResponseHeader() {
    httpVersion = "HTTP/1.1";
    date = time(0);
    server = "tech-mail.ru http-server (via alexopryshko)";
}

void ResponseHeader::setContentLength(int contentLength) {
    this->contentLength = contentLength;
}

void ResponseHeader::setContentType(std::string contentType) {
    this->contentType = contentType;
}

void ResponseHeader::setStatusCode(int statusCode, std::string reasonPhrase) {
    this->statusCode = statusCode;
    this->reasonPhrase = reasonPhrase;
}

std::string ResponseHeader::getHeader() {
    std::string buffer = "";
    buffer += httpVersion;
    buffer += characters::SP;
    buffer += (std::string) statusCode;
    buffer += characters::SP;
    buffer += reasonPhrase;

    buffer += characters::LF;
    buffer += "Connection: close";
    buffer += characters::LF;
    buffer += "Date: " + ctime(&date);
    buffer += characters::LF;
    buffer += "Server: " + server;
    buffer += characters::LF;
    buffer += "Content-Length: " + contentLength;
    buffer += "Content-Type: " + contentType + "; " + "charset='utf-8'";
    buffer += characters::CRLF + characters::CRLF;
    return buffer;
}