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
    buffer += SplitChars::SP;
    buffer += std::to_string(statusCode);
    buffer += SplitChars::SP;
    buffer += reasonPhrase;

    buffer += SplitChars::LF;
    buffer += "Connection: close";
    buffer += SplitChars::LF;
    std::string strData(ctime(&date));
    buffer += "Date: " + strData;
    buffer += SplitChars::LF;
    buffer += "Server: " + server;
    buffer += SplitChars::LF;
    buffer += "Content-Length: " + std::to_string(contentLength);
    buffer += "Content-Type: " + contentType + "; " + "charset='utf-8'";
    buffer += SplitChars::CRLF + SplitChars::CRLF;
    return buffer;
}