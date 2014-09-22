#include "http_handler.h"

http_handler::http_handler() {
    number_of_threads = sysconf( _SC_NPROCESSORS_ONLN ) + 1;
}

void http_handler::add_request(request_header *_request_header) {
    factories_locker.lock();
    factories.push(_request_header);
    factories_locker.unlock();
    cv.notify_one();
}

void http_handler::request_handler(http_handler* _http_handler) {
    while (_http_handler->get_is_threads_run()) {
        std::unique_lock<std::mutex> _locker(_http_handler->wait_locker);
        _http_handler->cv.wait(_locker, [&](){ return _http_handler->get_is_threads_run(); });
        request_header* _request_header = _http_handler->get_request_header_from_queue();
        //to-do
    }
}

request_header* http_handler::get_request_header_from_queue() {
    request_header* _request_header = NULL;
    factories_locker.lock();
    _request_header = factories.front();
    factories.pop();
    factories_locker.unlock();
    return _request_header;
}

void http_handler::run() {
    is_threads_run = true;
    for (int i = 0; i < number_of_threads; i++) {
        std::thread thread(request_handler, this);
        thread.detach();
    }
}