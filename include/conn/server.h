#ifndef EVENT_H
#define EVENT_H

// #include <vector>
#include "conn/epoll_gs.h"
#include <conn/comm.h>

#define MAX_EVENTS 32       //epoll_wait一次性监听最大的事件数量

class Server
{
public:

    Server();
    ~Server();

    int initialize(int port);
    void run();
    //void shutdown();

    void set_channel_read_callback(ChannelEventCallback channel_rcb);
    void set_channel_write_callback(ChannelEventCallback channel_wcb);

private:
    void accept_callback();

    int listen_fd;
    Epoll epoll_gs;

    //ChannelPtr accept_channel;

    ChannelEventCallback channel_read_callback;
    ChannelEventCallback channel_write_callback;

    //std::vector<ChannelPtr> channel_ptrs;
};

#endif