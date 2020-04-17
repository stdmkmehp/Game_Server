#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include <conn/comm.h>

#define MAX_EVENTS 32       //epoll_wait一次性监听最大的事件数量

/*
typedef union epoll_data {
    void    *ptr;
    int      fd;
    uint32_t u32;
    uint64_t u64;
} epoll_data_t;

struct epoll_event {
    uint32_t     events;    // Epoll events
    epoll_data_t data;      //User data variable
};
*/

class Event_Loop
{
public:
    Event_Loop();
    ~Event_Loop();

    void loop();    // loop& dispatch
    void update_channel(Channel* cptr);
    void add_channel(Channel* cptr);
    void del_channel(Channel* cptr);

private:
    int epoll_fd;
};

#endif