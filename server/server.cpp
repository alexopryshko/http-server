#include "Server.h"

server::server() {
    if (listenSocket = socket(AF_INET, SOCK_STREAM, 0) < 0) {
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
    if (setnonblock(listenfd) < 0) {
        throw new nonblocking_exception();
    }

    base = event_base_new();
    event_set(&ev_accept, listenfd, EV_READ|EV_PERSIST, accept, /*(void *)&workqueue*/ NULL);
    event_base_set(base, &ev_accept);
    event_add(&ev_accept, NULL);
}

server::~server() {
    event_base_free(base);
    base = NULL;
    close(listenfd);
}

void server::accept(int fd, short ev, void *arg) {

}

void server::run() {
    event_base_dispatch(base);
}