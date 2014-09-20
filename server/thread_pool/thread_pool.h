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
    void stop() {};
    event_factory *get_factory();
    void shift_queue();

    static void thread_function(int thread_id, thread_pool *_thread_pool);

    bool is_threads_run;
    std::queue<event_factory*> factories;
    bool *active_threads;
    std::mutex factories_locker;
    std::mutex active_threads_locker;
    std::mutex wait_locker;
    std::condition_variable cv;

private:
    long number_of_workers;
};