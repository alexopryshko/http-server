#include <iostream>
#include "request_header.h"
#include "constants.h"
#include <map>

class response_header {
public:
    response_header();

    void set_status_code(int _status_code);
    void set_content_type(std::string _content_type);
    void set_content_length(long _content_length);

    std::string getHeader();

private:
    //status-line
    std::string http_version;
    int status_code;
    std::string reason_phrase;
    //general-header
    std::time_t date;
    //response-header
    std::string server;
    //entity-header
    long content_length;
    std::string content_type;
};