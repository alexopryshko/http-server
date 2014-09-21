#include "file_system.h"

file_system::file_system() {
    document_root = "/Users/alexander/Development/http-server/data/";
}

file_system::file_system(std::string document_root) {
    this->document_root = document_root;
}

file* file_system::get(std::string path) {
    file *_file;//= cache.find(path);
    //if (_file != NULL) {
    //    return _file;
    //}
    std::ifstream b_file;
    b_file.exceptions (std::ifstream::failbit | std::ifstream::badbit );
    char *data = NULL;
    long long int size = 0;
    try {
        b_file.open(document_root + path, std::ios::binary);
        b_file.seekg (0, b_file.end);
        size = b_file.tellg();
        b_file.seekg (0, b_file.beg);
        data = new char[size];
        b_file.read(data, size);
        b_file.close();
    }
    catch (std::ifstream::failure e) {
        return NULL;
    }
    _file = new file(data, size);
    cache[path] = _file;
    return _file;
}