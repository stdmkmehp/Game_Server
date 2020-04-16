#include <stdlib.h>
#include <stdio.h>
#include "conn/comm.h"
#include "conn/server.h"
#include "conn/channel.h"

void on_connection()
{
    
}

void on_message(ChannelPtr ch)
{
    printf("on message\n");
}

int main(int argc, char *argv[])
{
    
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