#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <conn/server.h>
#include <conn/channel.h>
#include <conn/event_loop.h>


Server::Server() : listen_fd(-1), event_loop_ptr(new Event_Loop()),
                    channel_read_callback(nullptr), channel_write_callback(nullptr)
{

}

Server::~Server()
{
    if(listen_fd >= 0)
        close(listen_fd);

    delete event_loop_ptr;
}

int Server::initialize(int port)
{
    struct sockaddr_in svraddr;
    memset(&svraddr, 0, sizeof(svraddr));
    svraddr.sin_family = AF_INET;
    svraddr.sin_port = htons(port);
    svraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // TCP non-block close-on-exec
    listen_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
    if(listen_fd < 0)
    {
        return -1;
    }
    
    int opt = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));  // address reuse
    int ret = bind(listen_fd, (struct sockaddr *)&svraddr, sizeof(svraddr));
    if(ret < 0)
    {
        close(listen_fd);
        return -1;
    }

    ret = listen(listen_fd, SOMAXCONN);
    if (ret < 0)
    {
        close(listen_fd);
        return -1;
    }

    printf("Server start listening on port %d...\n", port);
    return listen_fd;
}

void Server::run()
{
    ChannelPtr accept_channel(new Channel(listen_fd, event_loop_ptr));
    accept_channel->set_read_callback(std::bind(&Server::accept_callback, this));
    accept_channel->enable_read();

    event_loop_ptr->loop();
}

void Server::set_channel_read_callback(ChannelEventCallback channel_rcb)
{
    channel_read_callback = channel_rcb;
}

void Server::set_channel_write_callback(ChannelEventCallback channel_wcb)
{
    channel_write_callback = channel_wcb;
}

void Server::accept_callback()
{
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);;
    int conn_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_addr_len);

    if(conn_fd < 0)
    {
        printf("[ERROR] Failed to connect client.\n");
        return;
    }

    // set conn_fd non-blocking
    fcntl(conn_fd, F_SETFL, fcntl(conn_fd, F_GETFL, 0) | O_NONBLOCK);

    // FIXME 如果这里的channel是shared_ptr的话 这个shared_ptr是不是根本发挥不了作用
    // create channel and add conn_fd into epoll
    ChannelPtr new_conn_channel(new Channel(conn_fd, event_loop_ptr));
    // channel_read_callback为Server的成员变量 而非成员函数 bind时不能加this
    new_conn_channel->set_read_callback(std::bind(Server::channel_read_callback, new_conn_channel));
    new_conn_channel->set_write_callback(std::bind(Server::channel_write_callback, new_conn_channel));
    new_conn_channel->enable_read();
}