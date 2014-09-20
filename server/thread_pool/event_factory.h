#pragma once
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <thread>

class event_factory {
public:
    event_factory();
    void job();
    void set_parent_id_thread(int parent_id_thread);
    int get_parent_id_thread() {return parent_id_thread;}
    void add(evutil_socket_t fd);
private:
    event_base *base;
    int parent_id_thread;
    static void echo_read_cb( struct bufferevent *buf_ev, void *arg );
    static void echo_event_cb( struct bufferevent *buf_ev, short events, void *arg );
};