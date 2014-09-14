#include <iostream>
#include <ctime>
#include "ResponseHeader.h"

class Response {
public:
    Response();
    ~Response();

    char *serialize();
    void setBody(std::string contentType, char *messageBody, int length);
    void setHeader(ResponseHeader *responseHeader);

private:
    ResponseHeader *responseHeader;
    char *messageBody;
};