#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <conn/channel.h>
#include <conn/buffer.h>
#include <conn/event_loop.h>


Channel::Channel(int fd_, Event_Loop* elptr) : fd(fd_), event_loop_ptr(elptr), read_callback(nullptr), write_callback(nullptr),
                            read_buf(new Buffer()), write_buf(new Buffer())
{
    memset(&ev, 0, sizeof(ev));
    ev.data.ptr = this; // 有风险！ ev.data.ptr为资源的实际地址
    event_loop_ptr->add_channel(this);
    printf("[Debug] New Channel Created, fd is %d.\n", fd);
}

Channel::~Channel()
{
    printf("[Debug] Destruct Channel. fd is %d.\n", fd);
    close(fd);
    //event_loop_ptr->del_channel(this);
}

void Channel::handle_event(uint32_t events)
{
    if((events & EPOLLHUP) && !(events & EPOLLIN))
    {
        // close callback
    }

    if (events & EPOLLERR)
    {
        // error callback
    }

    // 读数据 紧急数据 读关闭
    if(events & (EPOLLIN | EPOLLPRI | EPOLLRDHUP))
    {
        if(read_callback)
        {
            read_callback();
        }
    }
    
    if(events & EPOLLOUT)
    {
        if (write_callback)
        {
            write_callback();
        }
    }

}

void Channel::enable_write()
{
    ev.events |= EPOLLOUT;
    event_loop_ptr->update_channel(this);
}

void Channel::disable_write()
{
    ev.events &= ~EPOLLOUT;
    event_loop_ptr->update_channel(this);
}
void Channel::enable_read()
{
    ev.events |= (EPOLLIN | EPOLLPRI);
    event_loop_ptr->update_channel(this);
}

void Channel::disable_read()
{
    ev.events &= ~(EPOLLIN | EPOLLPRI);
    event_loop_ptr->update_channel(this);
}


void Channel::set_read_callback(EventCallback cb)
{
    read_callback = cb;
}

void Channel::set_write_callback(EventCallback cb)
{
    write_callback = cb;
}