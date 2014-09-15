#include <iostream>
#include <ctime>
#include "response_header.h"

class response {
public:
    response();
    ~response();

    char *serialize();
    void setBody(std::string contentType, char *, int length);
    void setHeader(response_header *);

private:
    response_header *responseHeader;
    char *messageBody;
};