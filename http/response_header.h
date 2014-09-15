#include <iostream>
#include "utilities.h"
#include "constants.h"

class response_header {
public:
    response_header();
    ~response_header() {};

    void setStatusCode(int statusCode, std::string reasonPhrase);
    void setContentType(std::string contentType);
    void setContentLength(int contentLength);
    int getContentLength() { return contentLength; }
    std::string getHeader();

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