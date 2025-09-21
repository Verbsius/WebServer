/*
 * @Author       : mark
 * @Date         : 2020-06-15
 * @copyleft Apache 2.0
 */ 
#ifndef EPOLLER_H
#define EPOLLER_H

#include <sys/epoll.h> //epoll_ctl()
#include <fcntl.h>  // fcntl()
#include <unistd.h> // close()
#include <assert.h> // close()
#include <vector>
#include <errno.h>

class Epoller {
public:
    // 
    explicit Epoller(int maxEvent = 1024);

    ~Epoller();

    bool AddFd(int fd, uint32_t events);

    bool ModFd(int fd, uint32_t events);

    bool DelFd(int fd);

    int Wait(int timeoutMs = -1);

    int GetEventFd(size_t i) const;

    uint32_t GetEvents(size_t i) const;
        
private:
    // 通过epoll_create创建的epoll句柄, 用来表示一个epoll实例，
    // 储存着所有被监听的文件描述符信息
    int epollFd_;

    // 用于存储epoll_wait返回的就绪事件的数组
    // epoll_wait检测到的就绪事件会被存储在这个数组中
    // maxEvent指定了这个数组的最大容量
    std::vector<struct epoll_event> events_;    
};

#endif //EPOLLER_H