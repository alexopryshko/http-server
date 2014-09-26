#include "thread_pool.h"
#include <unistd.h>

thread_pool::thread_pool() {
    number_of_workers = sysconf( _SC_NPROCESSORS_ONLN ) + 1;
    std::cerr << "Number of threads: " + std::to_string(number_of_workers) << std::endl;
}

thread_pool::thread_pool(int number_of_workers) {
    this->number_of_workers = number_of_workers;
}

void thread_pool::thread_function(int thread_id, thread_pool *_thread_pool) {
    event_factory *_factory = new event_factory();
    _factory->set_parent_id_thread(thread_id);

    _thread_pool->factories_locker.lock();
    _thread_pool->factories.push(_factory);
    _thread_pool->factories_locker.unlock();
    while (_thread_pool->is_threads_run) {
        _factory->job();
        usleep(50);
    }
}

void thread_pool::run() {
    is_threads_run = true;
    for (int i = 0; i < number_of_workers; i++) {
        std::thread thread(thread_function, i, this);
        thread.detach();
    }
}

event_factory *thread_pool::get_factory() {
    factories_locker.lock();
    event_factory *_factory = factories.back();
    factories_locker.unlock();
    return _factory;
}

void thread_pool::shift_queue() {
    factories_locker.lock();
    event_factory *_factory = factories.front();
    factories.pop();
    factories.push(_factory);
    factories_locker.unlock();
}




