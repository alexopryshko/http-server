#include "event_factory.h"
#include "../../http/request_header.h"
#include "../../http/response_header.h"
#include "exception.h"



std::string document_root = "/Users/alexander/Development/http-server/data/http-test-suite";

event_factory::event_factory() {
    base = event_base_new();
    parent_id_thread = -1;
}

void event_factory::set_parent_id_thread(int parent_id_thread) {
    this->parent_id_thread = parent_id_thread;
}

void event_factory::add(evutil_socket_t fd) {
    struct bufferevent *buf_ev = bufferevent_socket_new( this->base, fd, BEV_OPT_CLOSE_ON_FREE );
    //FILE * file = NULL;
    bufferevent_setcb(buf_ev, echo_read_cb, echo_write_cb/*set drop call back */, echo_event_cb, NULL);
    //bufferevent_enable( buf_ev, (EV_READ | EV_WRITE) );
    bufferevent_enable( buf_ev, (EV_READ) );
}

void event_factory::job() {
    event_base_loop(base, 0);
    //event_base_loop(base, EVLOOP_NONBLOCK);
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
    bool send_file = false;
    size_t buffer_input_size = evbuffer_get_length(buf_input);
    request_header *_request_header = new request_header();
    response_header* _response_header = new response_header();
    std::string file_path = document_root;
    struct stat file_stat;
    int file_descriptor = -1;
    try {
        if (!_request_header->parse(evbuffer_pullup(buf_input, buffer_input_size), buffer_input_size)) {
            throw bad_request();
        }
        if (!(_request_header->get_method() == "GET" || _request_header->get_method() == "HEAD")) {
            throw bad_request();
        }
        file_path += _request_header->get_path();
        file_descriptor = open(file_path.c_str(), O_RDONLY | O_NONBLOCK);
        if (file_descriptor < 0) {
            throw not_found();
        }
        fstat(file_descriptor, &file_stat);
        _response_header->set_content_type_from_path(_request_header->get_path());
        _response_header->set_content_length(file_stat.st_size);
        _response_header->set_status_code(200);
        send_file = true;
        //FILE * pFile;
        //pFile = fopen ("/Users/alexander/Development/http-server/data/Ref6_bufferevent.html","r");
        //int fd = fileno(pFile);
        //fseek(pFile, 0L, SEEK_END);
        //long size = ftell(pFile);
        //fseek(pFile, 0L, SEEK_SET);
        //FILE * pFile;
        //pFile = fopen ("/Users/alexander/Development/http-server/data/Ref6_bufferevent.html","r");
        //int fd = fileno(pFile);
        //fseek(pFile, 0L, SEEK_END);
        //long size = ftell(pFile);
        //fseek(pFile, 0L, SEEK_SET);
        //const char *str = "HTTP/1.1 200 OK\r\nServer: nginx/1.2.4\r\nDate: Sun, 14 Sep 2014 18:35:55 GMT\r\nContent-Type: text/html; charset=windows-1251\r\nContent-Length: 44\r\nConnection: close\r\n\r\n ";
        //if (_response->create_response(_request_header)) {
        //    evbuffer_add_printf(buf_output, _response->serialize().c_str());
        //    evbuffer_add_file(buf_output, _response->get_file_description(), 0, _response->get_file_size());
        //}
    }
    catch (bad_request) {
        _response_header->set_content_type("html");
        _response_header->set_content_length(0);
        _response_header->set_status_code(405);
    }
    catch (not_found) {
        _response_header->set_content_type("html");
        _response_header->set_content_length(0);
        _response_header->set_status_code(404);
    }
    evbuffer_add_printf(buf_output, _response_header->getHeader().c_str());
    if (send_file) {
        evbuffer_add_file(buf_output, file_descriptor, 0, file_stat.st_size);
    }
    bufferevent_enable(buf_ev, (EV_WRITE));
}

void event_factory::echo_write_cb(struct bufferevent *buf_ev, void *arg) {
    free(arg);
    bufferevent_free(buf_ev);
}
