#include <string>

class RequestHeader {
public:
    RequestHeader() {};
    RequestHeader(std::string data);

    std::string getPath() { return path; }
    std::string getMethod() { return method; }
    std::string getHttpVersion() { return httpVersion; }

private:
    std::string method;
    std::string path;
    std::string httpVersion;

    void parse(std::string data);
};
