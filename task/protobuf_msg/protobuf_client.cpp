#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctime>
#include <chrono>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#include "msg_pb3.pb.h"

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("Usage: ./echoclient IP port\n");
        return 0;
    }

    struct sockaddr_in cltaddr;
    memset(&cltaddr, 0, sizeof(cltaddr));
    cltaddr.sin_family = AF_INET;
    cltaddr.sin_port = htons(atoi(argv[2]));
    cltaddr.sin_addr.s_addr = inet_addr(argv[1]);

    int conn_fd = socket(AF_INET, SOCK_STREAM, 0);  
    if (conn_fd < 0)  {
        printf("[ERROR] Failed to create conn fd.\n");
        return 0;
    }

    int ret = connect(conn_fd, (struct sockaddr*)&cltaddr, sizeof(cltaddr));
    if (ret < 0)  {
        printf("[ERROR] Failed to connect server.\n");
        close(conn_fd);
        return 0;
    }

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    for(;;)
    {
        GameServerMsg::SimpleMsg msg;
        msg.set_id(3004);
        msg.set_name("Steve W Zhao");
        msg.set_request(GameServerMsg::SimpleMsg_Task::SimpleMsg_Task_Time);
        
        std::string data;
        msg.SerializeToString(&data);

        strcpy(buffer, data.c_str());

        int n = send(conn_fd, buffer, 1024, 0);
        if(n <= 0)
            break;
        printf("Send: %s\n", buffer);
        printf("\t-- id is %ld\n", msg.id());
        printf("\t-- name is %s\n", msg.name().c_str());
        printf("\t-- request is %d\n", msg.request());

	    n = recv(conn_fd, buffer, 1024, 0);
        if(n <= 0)
            break;
        data = buffer;
        msg.ParseFromString(data);
        printf("Recv: %s\n", buffer);
        printf("\t-- time stamp in server is %ld\n", msg.t_curr().t_stamp());

        sleep(1);
    }

    close(conn_fd);
    return 0;
}