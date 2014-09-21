#include "file.h"

file::file(char *data, long long int size/*, std::string type*/) {
    this->data = data;
    this->size = size;
    //this->type = type;
}