#include <Foundation/Foundation.h>
#include "Server.h"

server::server() {
    /*if (listenSocket = socket(AF_INET, SOCK_STREAM, 0) < 0) {
        throw new listen_exception();
    }
    memset( &sin, 0, sizeof(sin) );
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl( INADDR_ANY );
    sin.sin_port = htons( port );
    if (bind(listenfd, (struct sockaddr_in *)&sin, sizeof(sin)) < 0) {
        throw new bind_exception();
    }
    if (listen(listenfd, CONNECTION_BACKLOG) < 0) {
        throw new listen_exception();
    }
    int reuseaddr_on = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_on, sizeof(reuseaddr_on));
    int flags = fcntl(listenfd, F_GETFL);
    if (flags >= 0) {
        flags |= O_NONBLOCK;
        if (fcntl(listenfd, F_SETFL, flags) < 0)
            throw new nonblocking_exception();
    }
    base = event_base_new();
    event_set(&ev_accept, listenfd, EV_READ|EV_PERSIST, accept, (void *)&workqueue NULL);
    event_base_set(base, &ev_accept);
    event_add(&ev_accept, NULL);*/
    //struct evconnlistener *listener;
    //struct sockaddr_in sin;
    //int port = 8080;

    if ((base = event_base_new()) == NULL) {
        throw new event_exception();
    }
    memset( &sin, 0, sizeof(sin) );
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl( INADDR_ANY );
    sin.sin_port = htons( port );

    listener = evconnlistener_new_bind( base, accept_connection_cb, NULL,
            (LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE),
            -1, (struct sockaddr *)&sin, sizeof(sin) );
    if( !listener ) {
        throw new listener_exception();
    }
    //evconnlistener_set_error_cb( listener, accept_error_cb );
}

server::~server() {
    event_base_free(base);
    base = NULL;
    close(listenfd);
}

void server::read(struct bufferevent *buf_ev, void *arg) {

}

//void server::accept(int fd, short ev, void *arg) {
void server::accept(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *addr, int sock_len, void *arg) {
    /*int client_fd;
    struct sockaddr_in c_addr;
    int c_len = sizeof(c_addr);
    //workqueue_t *workqueue = (workqueue_t *)arg;
    //client_t *client;
    //job_t *job;

    client_fd = accept(fd, (struct sockaddr *)&c_addr, &c_len);
    if (client_fd < 0) {
        return;
    }
    int flags = fcntl(listenfd, F_GETFL);
    if (flags >= 0) {
        flags |= O_NONBLOCK;
        if (fcntl(listenfd, F_SETFL, flags) < 0)
            return;
    }
    struct event_base *ev_base;
    ev_base = event_base_new();*/
    struct event_base *base = event_base_new();
    struct bufferevent *buf_ev = bufferevent_socket_new( base, fd, BEV_OPT_CLOSE_ON_FREE );

    bufferevent_setcb( buf_ev, echo_read_cb, NULL, echo_event_cb, NULL );
    bufferevent_enable( buf_ev, (EV_READ | EV_WRITE) );
}

void server::job(client *client) {
    event_base_dispatch(client->base);
    //closeAndFreeClient(client);
    free(client);
}

void server::run() {
    event_base_dispatch(base);
}