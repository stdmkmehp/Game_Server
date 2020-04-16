#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include "conn/server.h"
#include "conn/channel.h"
#include "conn/epoll_gs.h"


Server::Server() : listen_fd(-1), epoll_gs(), channel_read_callback(nullptr), channel_write_callback(nullptr)
{

}

Server::~Server()
{
    if(listen_fd >= 0)
        close(listen_fd);
}

int Server::initialize(int port)
{
    struct sockaddr_in svraddr;
    memset(&svraddr, 0, sizeof(svraddr));
    svraddr.sin_family = AF_INET;
    svraddr.sin_port = htons(port);
    svraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // TCP non-block close-on-exec
    int listen_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
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

    return listen_fd;
}

void Server::run()
{
    epoll_gs.create();

    ChannelPtr accept_channel(new Channel(listen_fd));
    accept_channel->set_read_callback(std::bind(&Server::accept_callback, this));
    epoll_event ev = create_epoll_event(EPOLLIN | EPOLLPRI, accept_channel);
    epoll_gs.add(listen_fd, ev);

    epoll_gs.loop_dispatch();
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
    int connfd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_addr_len);

    if(connfd < 0)
    {
        printf("[ERROR] Failed to connect client.\n");
        return;
    }

    // set connfd non-blocking
    fcntl(connfd, F_SETFL, fcntl(connfd, F_GETFL, 0) | O_NONBLOCK);

    // create channel and add connfd into epoll
    ChannelPtr new_channel(new Channel(connfd));
    // channel_read_callback为Server的成员变量 而非成员函数 bind时不能加this
    new_channel->set_read_callback(std::bind(Server::channel_read_callback, new_channel));
    new_channel->set_write_callback(std::bind(Server::channel_write_callback, new_channel));
    epoll_event ev = create_epoll_event(EPOLLIN | EPOLLPRI, new_channel);
    epoll_gs.add(connfd, ev);
}