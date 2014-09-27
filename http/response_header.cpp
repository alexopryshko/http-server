#include "response_header.h"

std::map<int, std::string> response_status_code = {
        {200, "OK"},
        {403, "Forbidden"},
        {404, "Not Found"},
        {405, "Method Not Allowed"}
};
std::map<std::string, std::string> response_content = {
        {"html", "text/html"},
        {"css", "text/css"},
        {"js", "text/javascript"},
        {"jpg", "image/jpeg"},
        {"jpeg", "image/jpeg"},
        {"png", "image/png"},
        {"gif", "image/gif"},
        {"swf", "application/x-shockwave-flash"},
        {"unknown", "application/octet-stream"}
};

//std::regex extension_regex("\\.([^.]+)$");
std::regex extension_regex("\\.([\\w]+)\\/?$");

response_header::response_header() {
    http_version = "HTTP/1.1";
    date = time(0);
    server = "tech-mail.ru http-server (via alexopryshko)";
}

void response_header::set_content_length(long _content_length) {
    content_length = _content_length;
}

void response_header::set_content_type(std::string _content_type) {
    try {
        content_type = response_content.at(_content_type);
    }
    catch (...) {
        content_type = "application/octet-stream";
    }
}

void response_header::set_status_code(int _status_code) {
    try {
        reason_phrase = response_status_code.at(_status_code);
        status_code = _status_code;
    }
    catch (...) {
        _status_code = 500;
    }
}
std::string response_header::getHeader() {
    std::string buffer = "";
    buffer += http_version;
    buffer += SplitChars::SP;
    buffer += std::to_string(status_code);
    buffer += SplitChars::SP;
    buffer += reason_phrase;
    buffer += SplitChars::CRLF;
    //buffer += SplitChars::LF;
    buffer += "Connection: close";
    buffer += SplitChars::CRLF;
    struct tm *info = gmtime(&date);
    char buf[32];
    strftime(buf, 32, "%a, %d %b %Y %X ", info);
    std::string strData(buf);
    buffer += "Date: " + strData + "GMT";
    buffer += SplitChars::CRLF;
    buffer += "Server: " + server;
    buffer += SplitChars::CRLF;
    buffer += "Content-Length: " + std::to_string(content_length);
    buffer += SplitChars::CRLF;
    buffer += "Content-Type: " + content_type;// + "; " + "charset='utf-8'";
    buffer += SplitChars::CRLF + SplitChars::CRLF;

    return buffer;
}