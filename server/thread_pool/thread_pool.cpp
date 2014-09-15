#include "thread_pool.h"

thread_pool::thread_pool() {
    number_of_workers = sysconf( _SC_NPROCESSORS_ONLN ) + 1;
}

thread_pool::thread_pool(int number_of_workers) {
    this->number_of_workers = number_of_workers;
}

void thread_pool::run() {
    for (i = 0; i < number_of_workers; i++) {
        std::thread thread(worker_function);
        threads.push(thread);
        thread.detach();
    }
}

void thread_pool::add_client(client *clt) {
    g_lock.lock();
    clients.push(clt);
    g_lock.unlock();
}

void thread_pool::worker_function() {
    while (true) {
        if (clients.size() != 0) {
            client *clt = NULL;
            g_lock.lock();
            clt = clients.back();
            clients.pop();
            g_lock.unlock();
            clt->job(clt);
        }
    }
}


