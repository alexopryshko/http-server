#include <iostream>
#include <vector>

class utilities {
public:
    static std::vector<std::string> split(std::string data, std::string delimiter) {
        std::vector<std::string> buffer;
        size_t pos = 0;
        std::string token;
        while ((pos = data.find(delimiter)) != std::string::npos) {
            token = data.substr(0, pos);
            buffer.push_back(token);
            data.erase(0, pos + delimiter.length());
        }
        buffer.push_back(data);
        return buffer;
    };
};
