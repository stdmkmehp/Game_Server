#ifndef EPOLL_GS_H
#define EPOLL_GS_H

#define MAX_EVENTS 32       //epoll_wait一次性监听最大的事件数量

#include <conn/comm.h>

struct epoll_event create_epoll_event(uint32_t events, ChannelPtr ptr);

struct Epoll
{
public:
    Epoll();
    ~Epoll();

    int create();

    void add(int fd, struct epoll_event ev);
    void del(int fd, struct epoll_event ev);
    void modify(int fd, struct epoll_event ev);

    void loop_dispatch();

private:
    int epoll_fd;
};

#endif