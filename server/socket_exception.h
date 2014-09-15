#include <exception>

class socket_exception : public std::exception {
public:
    socket_exception() {};
};
class event_exception: public std::exception {
public:
    event_exception() {};
};

class listener_exception: public socket_exception {
public:
    listen_exception() {};
};
