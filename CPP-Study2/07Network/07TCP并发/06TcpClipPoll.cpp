#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <poll.h>
#define SER_IP "192.168.237.131"
#define SER_PORT 8888
#define CLI_IP "192.168.237.131"
#define CLI_PORT 9977

int main()
{
    // 1、创建通信套接字cfd
    int cfd = socket(AF_INET, SOCK_STREAM, 0); // 第一个参数表示IPV4，第二个参数表示通信类型为TCP
    if (cfd == -1)
    {
        perror("socket error");
        return -1;
    }

    // 2、为客户端绑定端口号，也可以不绑定，系统会为客户端随机分配端口号
    // 2.1创建一个结构体存储客户端信息
    struct sockaddr_in cin;
    cin.sin_addr.s_addr = inet_addr(CLI_IP);
    cin.sin_family = AF_INET;
    cin.sin_port = htons(CLI_PORT);
    // 为套接字绑定该信息
    if (bind(cfd, (struct sockaddr *)&cin, sizeof(cin)) == -1)
    {
        perror("bind error");
        return -1;
    }
    printf("bind success\n");

    // 3、将客户端与服务端建立连接
    // 3.1创建信息
    struct sockaddr_in sin;
    sin.sin_addr.s_addr = inet_addr(SER_IP);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(SER_PORT);
    // 3.2建立连接
    if (connect(cfd, (sockaddr *)&sin, sizeof(sin)) == -1)
    {
        perror("connect error");
        return -1;
    }
    printf("connect success\n");

    // 利用poll函数实现IO多路复用
    // 在收发消息的过程中，fgets和recv都造成阻塞
    // 如果在fgets阻塞过程中，服务端向客户端发来消息，因为阻塞客户端不会收到该消息
    // 只有当fgets输入信息之后解除阻塞，才会收到客户端发来的消息
    // 因此可以通过poll函数实现收发消息的分离

    // 定义一个poll类型的结构体数组，分别表示0和cfd，即表示从终端读取消息和接受消息
    struct pollfd p[2];
    p[0].fd = 0;
    p[0].events = POLLIN;
    p[1].fd = cfd;
    p[1].events = POLLIN;

    // 4、收发消息
    char wbuf[128] = "";
    while (1)
    {
        // 清空容器中的数据
        bzero(wbuf, sizeof(wbuf));

        // 利用poll函数进行阻塞管理
        int res = poll(p, 2, -1);
        if (res < 0)
        {
            perror("poll error");
            return -1;
        }
        else if (res == 0)
        {
            printf("TIME OUT\n");
            return -1;
        }
        // 当执行至此，表示有事件发生。发生事件的revent会发生变化

        if (p[0].revents == POLLIN)
        { // 在stdin处发生了阻塞，即发生了输入事件
          // 从终端中读取数据并发送
            fgets(wbuf, sizeof(wbuf), stdin);
            wbuf[strlen(wbuf) - 1] = '\0'; // 将换行变成'\0'

            if (send(cfd, wbuf, sizeof(wbuf), 0) == -1) // 参数0表示阻塞等待
            {
                perror("send error");
                return -1;
            }
            printf("发送成功\n");
        }
        if (p[1].revents == POLLIN)
        { // 阻塞等待收到服务端的信息
            if (recv(cfd, wbuf, sizeof(wbuf), 0) == 0)
            {
                printf("对端已下线\n");
                break;
            }
            printf("收到服务端的消息为%s\n", wbuf);
        } 
    }

    // 5、关闭套接字
    close(cfd);
}
