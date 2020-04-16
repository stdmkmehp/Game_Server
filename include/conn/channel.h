#ifndef CHANNEL_H
#define CHANNEL_H

#include <conn/comm.h>


class Channel
{
public:
    Channel(int fd_);
    ~Channel();

    void handle_event(uint32_t events);

    void set_read_callback(EventCallback cb);
    void set_write_callback(EventCallback cb);

private:
    int fd;

    EventCallback read_callback;
    EventCallback write_callback;

    BufferPtr read_buf;
    BufferPtr write_buf;
};

#endif