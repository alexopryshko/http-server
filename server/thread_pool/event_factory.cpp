#include "event_factory.h"


event_factory::event_factory() {
    base = event_base_new();
    parent_id_thread = -1;
}

void event_factory::set_parent_id_thread(int parent_id_thread) {
    this->parent_id_thread = parent_id_thread;
}

void event_factory::add(evutil_socket_t fd) {
    struct bufferevent *buf_ev = bufferevent_socket_new( this->base, fd, BEV_OPT_CLOSE_ON_FREE );
    bufferevent_setcb( buf_ev, echo_read_cb, NULL, echo_event_cb, NULL );
    bufferevent_enable( buf_ev, (EV_READ | EV_WRITE) );
}

void event_factory::job() {
    event_base_loop(base, EVLOOP_NONBLOCK);
    //event_base_dispatch(base);
}

void event_factory::echo_event_cb(struct bufferevent *buf_ev, short events, void *arg) {
    if( events & BEV_EVENT_ERROR )
        perror( "Ошибка объекта bufferevent" );
    if( events & (BEV_EVENT_EOF | BEV_EVENT_ERROR) )
        bufferevent_free( buf_ev );
}

void event_factory::echo_read_cb(struct bufferevent *buf_ev, void *arg) {
    struct evbuffer *buf_input = bufferevent_get_input(buf_ev);
    struct evbuffer *buf_output = bufferevent_get_output(buf_ev);
    //evbuffer_add_buffer(buf_output, buf_input);
    evbuffer_add(buf_output,
            (void *) "HTTP/1.1 200 OK\r\nServer: nginx/1.2.4\r\nDate: Sun, 14 Sep 2014 18:35:55 GMT\r\nContent-Type: text/html; charset=windows-1251\r\nContent-Length: 44\r\nConnection: close\r\n\r\n <html><body><h1>It works!</h1></body></html>",
            strlen(  "HTTP/1.1 200 OK\r\nServer: nginx/1.2.4\r\nDate: Sun, 14 Sep 2014 18:35:55 GMT\r\nContent-Type: text/html; charset=windows-1251\r\nContent-Length: 44\r\nConnection: close\r\n\r\n <html><body><h1>It works!</h1></body></html>"));
    //std::cerr << "recive message\n";
}
