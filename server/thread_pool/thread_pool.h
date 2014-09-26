#pragma once
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "event_factory.h"
#include <unistd.h>

class thread_pool {
public:
    thread_pool();
    thread_pool(int count);

    void run();
    event_factory *get_factory();
    void shift_queue();

    static void thread_function(int thread_id, thread_pool *_thread_pool);

    bool is_threads_run;
    std::queue<event_factory*> factories;
    std::mutex factories_locker;
private:
    long number_of_workers;
};