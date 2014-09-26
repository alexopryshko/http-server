#include "event_factory.h"
#include "../../http/request_header.h"
#include "../../http/response_header.h"
//#include "../../http/utility.h"
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
    struct bufferevent *buf_ev = bufferevent_socket_new( this->base, fd, BEV_OPT_CLOSE_ON_FREE);
    int *file_d = new int();
    bufferevent_setcb(buf_ev, echo_read_cb, echo_write_cb, echo_event_cb, file_d);
    bufferevent_enable( buf_ev, (EV_READ) );
}

void event_factory::job() {
    event_base_loop(base, 0);
}

void event_factory::echo_event_cb(struct bufferevent *buf_ev, short events, void *arg) {
    if( events & BEV_EVENT_ERROR )
        perror( "Ошибка объекта bufferevent" );
    if( events & (BEV_EVENT_EOF | BEV_EVENT_ERROR) )
        bufferevent_free( buf_ev );
    //free(arg);
}

void event_factory::echo_read_cb(struct bufferevent *buf_ev, void *arg) {
    struct evbuffer *buf_input = bufferevent_get_input(buf_ev);
    struct evbuffer *buf_output = bufferevent_get_output(buf_ev);
    bool send_file = false;
    bool index_directory = false;
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
        if (!check_path(_request_header->get_path())) {
            throw forbidden();
        }
        file_path += _request_header->get_path();
        if (file_path.back() == '/') {
            file_path += "index.html";
            index_directory = true;
        }
        file_descriptor = open(file_path.c_str(), O_RDONLY | O_NONBLOCK);
        int *file_d = (int*)arg;
        *file_d = file_descriptor;
        if (file_descriptor < 0) {
            if (index_directory)
                throw forbidden();
            else
                throw not_found();
        }
        fstat(file_descriptor, &file_stat);
        _response_header->set_content_type(get_file_type(_request_header->get_path()));
        _response_header->set_content_length(file_stat.st_size);
        _response_header->set_status_code(200);
        if (_request_header->get_method() != "HEAD")
            send_file = true;
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
    catch (forbidden) {
        _response_header->set_content_type("html");
        _response_header->set_content_length(0);
        _response_header->set_status_code(403);
    }
    evbuffer_add_printf(buf_output, _response_header->getHeader().c_str());
    if (send_file) {
        evbuffer_add_file(buf_output, file_descriptor, 0, file_stat.st_size);
    }
    bufferevent_enable(buf_ev, (EV_WRITE));
    //delete(_request_header);
    //delete(_response_header);
}

void event_factory::echo_write_cb(struct bufferevent *buf_ev, void *arg) {
    //free(arg);
    bufferevent_free(buf_ev);
}
