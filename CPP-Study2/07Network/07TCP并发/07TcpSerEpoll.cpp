#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> //close
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#define SET_IP "192.168.237.131"
#define SET_PORT 8888

int main()
{
    // 1、创建一个套接字，并返回对应的文件描述符
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1)
    {
        perror("socket error");
        return -1;
    }
    printf("socket success sfd=%d\n", sfd); // 3

    // 2、为套接字分配名称，给套接字绑定ip地址和端口号
    // 2.1 创建套接字信息结构体，方便绑定时传参数
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(SET_IP);
    sin.sin_port = htons(SET_PORT);
    // 2.2 绑定工作
    // 参数：1、要被绑定的套接字文件描述符
    // 2、参数2表示要绑定信息结构体，需要进行强制类型转换
    if (bind(sfd, (sockaddr *)&sin, sizeof(sin)) == -1)
    {
        perror("bind error");
        return -1;
    }

    // 3、监听，将套接字设置为监听状态
    // 参数1：套接字文件描述符
    // 参数2：挂起队列能够增长的最大长度，一般是128。也就是能够同时监听的客户端最大限度
    if (listen(sfd, 128) == -1)
    {
        perror("listen error");
        return -1;
    }
    printf("listen success\n");

    // 4、阻塞等待客户端的连接请求
    // 定义变量，用于接受客户端地址信息结构体
    struct sockaddr_in cin;
    socklen_t cinlen = sizeof(cin);

    // 创建一个epoll实例，返回值是一个文件描述符，并将sfd加入到epoll树中
    int epfd = epoll_create(1);
    if (epfd == -1)
    {
        perror("epoll_create error");
        return -1;
    }
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = sfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, sfd, &ev);
    // 参数1 epoll的文件描述符
    // 参数2 epoll操作，这个表示添加文件描述符
    // 参数3 要检测的文件描述符的值
    // 参数4 要检测的事件

    struct epoll_event evs[1024];
    int size = sizeof(evs) / sizeof(epoll_event);

    while (1)
    {
        // 阻塞检测epoll示例中是否有文件描述符就绪，如果有准备就绪，解除阻塞
        int num = epoll_wait(epfd, evs, size, -1);
        printf("num = %d\n", num);
        // 参数1 epoll示例的文件描述符
        // 参数2 自定义的文件描述符容器，如果epoll_wait中检测到有文件描述符产生事件了，就将该文件描述符放入该容器中
        // 参数3 文件描述符容器的大小
        // 参数4 表示阻塞事件 -1表示永久阻塞
        // 返回值 表示触发的文件描述符的个数，也就是容器中的文件描述符的个数

        for (int i = 0; i < num; i++)
        { // 遍历所有容器中的文件描述符，也就是触发的事件
            int tempfd = evs[i].data.fd;
            if (tempfd == sfd)
            { // 触发了sfd文件描述符，也就是接收到了新的请求
                int newfd = accept(sfd, (sockaddr *)&cin, &cinlen);
                if (newfd == -1)
                {
                    perror("accept error");
                    return -1;
                }
                printf("[%s:%d]:已连接成功\n", inet_ntoa(cin.sin_addr), ntohs(cin.sin_port));
                // 将该客户端连接的文件描述符加入到epoll阻塞检测树中
                struct epoll_event newev;
                newev.events = EPOLLIN;
                newev.data.fd = newfd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, newfd, &newev);
            }
            else
            { // 触发了其他文件描述符，也就是接收到了客户端发来的消息
                // 接收信息
                char rbuf[128] = "";
                bzero(rbuf, sizeof(rbuf)); // 每次接收信息将容器置空
                // 从套接字中读取信息放在buf中
                if (recv(tempfd, rbuf, sizeof(rbuf), 0) == 0)
                {
                    printf("对端已下线\n");
                    close(tempfd);
                    //将i从epoll树中删除
                    epoll_ctl(epfd,EPOLL_CTL_DEL,tempfd,&evs[i]);
                }
                printf("[%s:%d]:%s\n", inet_ntoa(cin.sin_addr), ntohs(cin.sin_port), rbuf);

                // 在每一个消息后面加一个笑脸返回回去
                strcat(rbuf, "^_^");
                if (send(tempfd, rbuf, sizeof(rbuf), 0) == -1)
                {
                    perror("send error");
                    return -1;
                }

                printf("发送成功\n");
            }
        }
        
    }

   
    close(sfd);
    close(epfd);

    return 0;
}