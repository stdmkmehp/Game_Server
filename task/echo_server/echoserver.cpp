#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "conn/comm.h"
#include "conn/server.h"
#include "conn/channel.h"

void on_message(ChannelPtr ch)
{
    char buf[1024];
    int conn_fd = ch->get_fd();
    int n = recv(conn_fd, buf, 1024, 0);
    if(n <= 0)
        return;
    printf("Recv: %s\n", buf);

    n = send(conn_fd, buf, 1024, 0);
    if(n <= 0)
        return;
    printf("Send: %s\n", buf);
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Usage: ./echoserver port\n");
        return 0;
    }
    
    Server game_server;
    game_server.set_channel_read_callback(on_message);

    int port = atoi(argv[1]);
    int listenfd = game_server.initialize(port);
    if(listenfd < 0)
    {
        printf("[ERROR] Failed to create listen fd.\n");
        return -1;
    }

    game_server.run();

    //game_server.shutdown();

    return 0;
}