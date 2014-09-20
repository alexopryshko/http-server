#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include "thread_pool/event_factory.h"
#include "thread_pool/thread_pool.h"
#include "socket_exception.h"

class server {
public:
    server();
    ~server();
    void run();

    static void accept(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *addr, int sock_len, void *arg );
    static void accept_error(struct evconnlistener *listener, void *arg);

private:
    struct event_base *base;
    struct evconnlistener *listener;
    struct sockaddr_in sin;
    int port;
    thread_pool *_thread_pool;
};