#include <iostream>
#include <ctime>
#include "ResponseHeader.h"

class Response {
public:
    Response();
    ~Response();

    char *serialize();
    void setBody(std::string contentType, char *, int length);
    void setHeader(ResponseHeader *);

private:
    ResponseHeader *responseHeader;
    char *messageBody;
};