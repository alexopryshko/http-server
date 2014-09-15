#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include "thread_pool/client.h"
#include "thread_pool/thread_pool.h"
#include "socket_exception.h"

class server {
    server();
    ~server();
    void run();

private:
    int listenSocket;
    struct event_base *base;
    //struct event *ev_accept;
    struct evconnlistener *listener;
    struct sockaddr_in sin;
    int port;

    //void accept(int fd, short ev, void *arg);
    void accept( struct evconnlistener *listener,
            evutil_socket_t fd, struct sockaddr *addr, int sock_len,
            void *arg );
    void read(struct bufferevent *buf_ev, void *arg);
    void job(client *client);
};