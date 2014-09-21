#include <iostream>
#include <string>

class file {
public:
    file(char *data, long long int size/*, std::string type*/);
    char *get_content() { return data; }
    long long int get_size() { return size; }
    //std::string get_type() {return this->type;}
private:
    char *data;
    long long int size;
    //std::string type;
};