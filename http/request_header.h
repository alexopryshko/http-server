#include <string>

class request_header {
public:
    request_header() {};
    request_header(std::string data);

    std::string getPath() { return path; }
    std::string getMethod() { return method; }
    std::string getHttpVersion() { return httpVersion; }

private:
    std::string method;
    std::string path;
    std::string httpVersion;

    void parse(std::string data);
};
