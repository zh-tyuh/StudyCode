#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#define SER_IP "192.168.237.131"
#define SER_PORT 8888
#define CLI_IP "192.168.237.131"
#define CLI_PORT 9977

int main()
{
    //1、创建通信套接字cfd
    int cfd=socket(AF_INET,SOCK_STREAM,0);  //第一个参数表示IPV4，第二个参数表示通信类型为TCP
    if(cfd==-1)
    {
        perror("socket error");
        return -1;
    }

    //2、为客户端绑定端口号，也可以不绑定，系统会为客户端随机分配端口号
    //2.1创建一个结构体存储客户端信息
    struct sockaddr_in cin;
    cin.sin_addr.s_addr=inet_addr(CLI_IP);
    cin.sin_family=AF_INET;
    cin.sin_port=htons(CLI_PORT);
    //为套接字绑定该信息
    if(bind(cfd,(struct sockaddr*)&cin,sizeof(cin))==-1)
    {
        perror("bind error");
        return -1;
    }
    printf("bind success\n");

    //3、将客户端与服务端建立连接
    //3.1创建信息
    struct sockaddr_in sin;
    sin.sin_addr.s_addr=inet_addr(SER_IP);
    sin.sin_family=AF_INET;
    sin.sin_port=htons(SER_PORT);
    //3.2建立连接
    if(connect(cfd,(sockaddr*)&sin,sizeof(sin))==-1)
    {
        perror("connect error");
        return -1;
    }
    printf("connect success\n");

    //4、收发消息
    char wbuf[128]="";
    while(1)
    {
        //清空容器中的数据
        bzero(wbuf,sizeof(wbuf));

        //从终端中读取数据并发送
        fgets(wbuf,sizeof(wbuf),stdin);
        wbuf[strlen(wbuf)-1]='\0';//将换行变成'\0'

        if(send(cfd,wbuf,sizeof(wbuf),0)==-1)  //参数0表示阻塞等待
        {
            perror("send error");
            return -1;
        }
        printf("发送成功\n");

        if(recv(cfd,wbuf,sizeof(wbuf),0)==0)
        {
            printf("对端已下线\n");
            break;
        }

        printf("收到服务端的消息为%s\n",wbuf);
    }

    //5、关闭套接字
    close(cfd);
}

