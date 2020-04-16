#include <netinet/in.h>
#include <sys/epoll.h>
#include <conn/channel.h>
#include <conn/buffer.h>


Channel::Channel(int fd_) : fd(fd_), read_callback(nullptr), write_callback(nullptr),
                            read_buf(new Buffer()), write_buf(new Buffer())
{
    
}

Channel::~Channel()
{
    
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

void Channel::set_read_callback(EventCallback cb)
{
    read_callback = cb;
}

void Channel::set_write_callback(EventCallback cb)
{
    write_callback = cb;
}