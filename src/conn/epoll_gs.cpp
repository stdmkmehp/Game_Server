#include <sys/epoll.h>
#include <string.h>
#include <unistd.h>
#include "conn/epoll_gs.h"
#include "conn/channel.h"

struct epoll_event create_epoll_event(uint32_t events, ChannelPtr ptr)
{
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = events;
    // FIXME: can not assign shared_ptr to void*
    // ev.data.ptr为智能指针的地址
    ev.data.ptr = &ptr;    
    return ev;
}

Epoll::Epoll() : epoll_fd(-1)
{

}

Epoll::~Epoll()
{
    if(epoll_fd >= 0)
        close(epoll_fd);
}

int Epoll::create()
{
    epoll_fd = epoll_create(1024);
    if(epoll_fd < 0)
        printf("[ERROR] Failed to create epoll.\n");
    return epoll_fd;
}

void Epoll::loop_dispatch()
{
    struct epoll_event events[MAX_EVENTS];

    for(;;)
    {
        int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        for(int i=0; i<nfds; ++i)
        {
            // FIXME: 非常勉强的实现 智能指针的指针解引用 获得智能指针，再传递给channel_ptr
            // https://stackoverflow.com/questions/23204255/how-to-cast-void-to-shared-ptrmytype
            ChannelPtr channel_ptr = *(static_cast<ChannelPtr*>(events[i].data.ptr));
            channel_ptr->handle_event(events[i].events);
        }
    }
}

void Epoll::add(int fd, struct epoll_event ev)
{
    int ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev);
    if(ret < 0)
    {
        printf("[ERROR] Failed to add epoll event.\n");
    }
}

void Epoll::del(int fd, struct epoll_event ev)
{
    int ret = epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, &ev);
    if(ret < 0)
    {
        printf("[ERROR] Failed to delete epoll event.\n");
    }
}

void Epoll::modify(int fd, struct epoll_event ev)
{
    int ret = epoll_ctl(epoll_fd, EPOLL_CTL_MOD, fd, &ev);
    if(ret < 0)
    {
        printf("[ERROR] Failed to modify epoll event.\n");
    }
}