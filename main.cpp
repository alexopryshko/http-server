#include "server/server.h"

int main( int argc, char **argv )
{
    server *_server = new server();
    _server->run();

    return 0;
}