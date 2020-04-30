#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "conn/comm.h"
#include "conn/server.h"
#include "conn/channel.h"

#include <chrono>
#include "msg_pb3.pb.h"

void on_message(ChannelPtr ch)
{
    char buf[1024];
    int conn_fd = ch->get_fd();
    int n = recv(conn_fd, buf, 1024, 0);
    if(n <= 0)
        return;
        
    std::string data = buf;
    GameServerMsg::SimpleMsg msg;
    msg.ParseFromString(data);
    printf("Recv: %s\n", buf);
    printf("\t-- id is %ld\n", msg.id());
    printf("\t-- name is %s\n", msg.name().c_str());
    printf("\t-- request is %d\n", msg.request());

    GameServerMsg::SimpleMsg msg_sendback;
    switch (msg.request())
    {
        // 处理收到时间戳的请求
        case GameServerMsg::SimpleMsg_Task_Time:
        {
            auto tnow = std::chrono::system_clock::now();
            int64_t tstamp = std::chrono::duration_cast<std::chrono::milliseconds>(tnow.time_since_epoch()).count();
            auto ptcurr = msg_sendback.mutable_t_curr();
            ptcurr->set_t_stamp(tstamp);
            msg_sendback.SerializeToString(&data);
            strcpy(buf, data.c_str());
            break;
        }
        default:
            break;
    }

    n = send(conn_fd, buf, 1024, 0);
    if(n <= 0)
        return;
    printf("Send: %s\n", buf);
    printf("\t-- time stamp is %ld\n", msg_sendback.t_curr().t_stamp());
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