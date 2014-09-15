class client {
public:
    void (*job)(client *client);
    struct event_base *base;
};