#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include "client.h"

class thread_pool {
public:
    thread_pool();
    thread_pool(int count);

    void run();
    void add_client(client *clt);
    void remove_client(client clt);

private:
    int number_of_workers;
    //std::queue threads;
    std::queue<client*> clients;
    std::mutex g_lock;

    void worker_function();
};