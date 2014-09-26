#include "server.h"

server::server() {
    int port = 8080;
    if ((base = event_base_new()) == NULL) {
        //throw new event_exception();
    }
    memset( &sin, 0, sizeof(sin) );
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl( INADDR_ANY );
    sin.sin_port = htons( port );

    _thread_pool = new thread_pool();

    listener = evconnlistener_new_bind( base, accept, _thread_pool,
            (LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE),
            -1, (struct sockaddr *)&sin, sizeof(sin) );
    if( !listener ) {
        //throw new listener_exception();
    }
    evconnlistener_set_error_cb( listener, accept_error);
    _thread_pool->run();
}

server::~server() {
    event_base_free(base);
    base = NULL;
}

void server::run() {
    event_base_dispatch(base);
}

void server::accept(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *addr, int sock_len, void *arg) {
    thread_pool *_thread_pool = (thread_pool*) arg;
    _thread_pool->get_factory()->add(fd);
    _thread_pool->shift_queue();
}

void server::accept_error(struct evconnlistener *listener, void *arg) {
    struct event_base *base = evconnlistener_get_base( listener );
    int error = EVUTIL_SOCKET_ERROR();
    fprintf( stderr, "Ошибка %d (%s) в мониторе соединений. Завершение работы.\n",
            error, evutil_socket_error_to_string( error ) );
    event_base_loopexit( base, NULL );
}