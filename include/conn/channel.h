#ifndef CHANNEL_H
#define CHANNEL_H

#include <conn/comm.h>
#include <sys/epoll.h>

class Event_Loop;

class Channel
{
public:
    Channel(int fd_, Event_Loop* elptr);           // 构造时即向event_loop注册该channel的event
    ~Channel();

    void handle_event(uint32_t events);

    int get_fd() { return fd; }
    struct epoll_event get_epoll_event() { return ev; }

    void set_read_callback(EventCallback cb);
    void set_write_callback(EventCallback cb);

    void enable_read();
    void disable_read();
    void enable_write();
    void disable_write();

private:
    int fd;

    struct epoll_event ev;
    Event_Loop* event_loop_ptr; // 由Server负责event_loop_ptr的生命周期

    EventCallback read_callback;
    EventCallback write_callback;

    BufferPtr read_buf;
    BufferPtr write_buf;
};

#endif