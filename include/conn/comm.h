#ifndef CONN_COMM_H
#define CONN_COMM_H

#include <functional>
#include <memory>

class Channel;
class Buffer;

typedef std::shared_ptr<Channel> ChannelPtr;
typedef std::shared_ptr<Buffer> BufferPtr;

typedef std::function<void(ChannelPtr)> ChannelEventCallback;
typedef std::function<void()> EventCallback;



#endif