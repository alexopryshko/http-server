#include "Utilities.h"

namespace status_code {
    int OK =                    200;
    int NOT_FOUND =             404;
    int METHOD_NOT_ALLOWED =    405;
}
namespace reason {
    std::string OK =                    "OK";
    std::string NOT_FOUND =             "Not Found";
    std::string METHOD_NOT_ALLOWED =    "Method Not Allowed";
}
namespace content_type {
    std::string html =      "text/html";
    std::string css =       "text/css";
    std::string js =        "text/javascript";
    std::string jpg =       "image/jpeg";
    std::string jpeg =      "image/jpeg";
    std::string png =       "image/png";
    std::string gif =       "image/gif";
    std::string swf =       "application/x-shockwave-flash";
    std::string unknown =   "application/octet-stream";
}

class ResponseHeader {
    ResponseHeader();
    ~ResponseHeader() {};

    void setStatusCode(int statusCode, std::string reasonPhrase);
    void setContentType(std::string contentType);
    void setContentLength(int contentLength);
    int getContentLength() { return contentLength; }
    std::string *getHeader();

private:
    //status-line
    std::string httpVersion;
    int statusCode;
    std::string reasonPhrase;
    //general-header
    std::time_t date;
    //response-header
    std::string server;
    //entity-header
    int contentLength;
    std::string contentType;
};