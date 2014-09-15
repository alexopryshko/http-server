#include <exception>

class socket_exception : public std::exception {
public:
    socket_exception() {};
};

class listen_exception: public socket_exception {
public:
    listen_exception() {};
};

class bind_exception: public socket_exception {
public:
    bind_exception() {};
};

class nonblocking_exception: public socket_exception {
public:
    nonblocking_exception() {};
};