#include <string>

class HTTPRequest {
public:
    HTTPRequest() {};
    HTTPRequest(std::string data);

    void parse(std::string data);
    std::string getPath() { return path; }
    std::string getMethod() { return method; }
    std::string getHttpVersion() { return httpVersion; }

private:
    std::string method;
    std::string path;
    std::string httpVersion;
};
