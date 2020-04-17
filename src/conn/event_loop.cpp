#include <unistd.h>
#include <sys/epoll.h>
#include <conn/event_loop.h>
#include <conn/channel.h>

Event_Loop::Event_Loop() : epoll_fd(-1)
{
    epoll_fd = epoll_create(1024);
    if(epoll_fd < 0)
        printf("[ERROR] Failed to create epoll.\n");
}

void Event_Loop::loop()
{
    struct epoll_event events[MAX_EVENTS];
    int timeout = -1;

    for(;;)
    {
        int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, timeout);
        for(int i=0; i<nfds; ++i)
        {
            // FIXME: 裸指针 有风险 但不出错
            Channel* channel_ptr = (Channel*)events[i].data.ptr;

            channel_ptr->handle_event(events[i].events);
        }
    }
}

Event_Loop::~Event_Loop()
{
    if(epoll_fd >= 0)
        close(epoll_fd);
}

void Event_Loop::update_channel(Channel* cptr)
{
    int fd = cptr->get_fd();
    epoll_event ev = cptr->get_epoll_event();
    int ret = epoll_ctl(epoll_fd, EPOLL_CTL_MOD, fd, &ev);
    if(ret < 0)
    {
        printf("[ERROR] Failed to modify epoll event.\n");
    }
}

void Event_Loop::add_channel(Channel* cptr)
{
    int fd = cptr->get_fd();
    epoll_event ev = cptr->get_epoll_event();
    int ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev);
    if(ret < 0)
    {
        printf("[ERROR] Failed to add epoll event.\n");
    }
}

void Event_Loop::del_channel(Channel* cptr)
{
    int fd = cptr->get_fd();
    epoll_event ev = cptr->get_epoll_event();
    int ret = epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, &ev);
    if(ret < 0)
    {
        printf("[ERROR] Failed to delete epoll event.\n");
    }
}