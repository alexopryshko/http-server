#include <iostream>
//#include <ifstream>
#include <fstream>
#include <map>
#include "file.h"


class file_system {
public:
    file_system();
    file_system(std::string document_root);

    file* get(std::string path);
private:

    std::map<std::string, file*> cache;
    std::string document_root;

    //bool is_directory(std::string path);
};