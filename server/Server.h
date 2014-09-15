#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include "socket_exception.h"

class server {
    server();
    ~server();
    void run();

private:
    int listenSocket;
    struct event_base *base;
    struct event *ev_accept;
    struct sockaddr_in sin;
    int port;

    void accept(int fd, short ev, void *arg);
};