#pragma once
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>
#include "request_header.h"

class http_handler {
public:
    http_handler();

    void run();
    void add_request(request_header* _request_header);

    bool get_is_threads_run() {return is_threads_run;}
    request_header* get_request_header_from_queue();
    static void request_handler(http_handler* _http_handler);

    std::mutex wait_locker;
    std::condition_variable cv;
private:
    long number_of_threads;
    bool is_threads_run;
    std::queue<request_header*> factories;
    std::mutex factories_locker;
};