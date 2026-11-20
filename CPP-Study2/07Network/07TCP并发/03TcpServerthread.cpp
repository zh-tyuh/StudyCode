#include<iostream>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#define SER_IP "192.168.237.137"
#define SER_PORT 8888
struct arg
{
    int fd;
    sockaddr_in cin;
};

void* msg_hander(void* arg)
{//利用newfd和客户端进行交互
    //将传入的参数进行转化 newfd cin
    sockaddr_in cin = (*(struct arg*)arg).cin;
    int newfd = (*(struct arg*)arg).fd;

    //信息传递
    char rbuf[128]="";
    while(1)
    {
        bzero(rbuf,sizeof(rbuf));
        recv(newfd,rbuf,sizeof(rbuf),0);
        
        printf("[%s:%d]:%s\n",inet_ntoa(cin.sin_addr),ntohs(cin.sin_port),rbuf);

        //添加一个笑脸发回去
        strcat(rbuf,":>");
        send(newfd,rbuf,strlen(rbuf),0);
        
        printf("发送成功\n");
        if(strcmp(rbuf,"quit")==0)
        {                    
            break;
        }
    }
    close(newfd);
    pthread_exit(NULL);
}


int main()
{  
    //1、创建用于通信的套接字
    int sfd = socket(AF_INET,SOCK_STREAM,0);
    if(sfd == -1)
    {
        perror("socket error");
        return -1;
    }
    //设置端口号允许快速复用
    int reu = 1;
    if(setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&reu,sizeof(reu))==-1)
    {
        perror("setsockopt error");
        return -1;
    }

    //2、绑定端口号的IP地址
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(SER_IP);
    sin.sin_port = htons(SER_PORT);

    if(bind(sfd,(struct sockaddr*)&sin,sizeof(sin))==-1)
    {
        perror("bind error");
        return -1;
    }

    //3、将套接字设置为监听状态
    if(listen(sfd,128)==-1)
    {
        perror("listen error");
        return -1;
    }
    printf("listening.....\n");

    //4、阻塞等待客户端进行连接请求
    sockaddr_in cin;
    socklen_t cinsize = sizeof(cin);
    while(1)
    {
        //创建新的用于通信的套接字
        int newfd = accept(sfd,(struct sockaddr*)&cin,&cinsize);
        if(newfd == -1)
        {
            perror("accept error");
            return -1;
        }
        printf("%s:%d]:已连接成功，newfd = %d!!!!\n", inet_ntoa(cin.sin_addr), ntohs(cin.sin_port), newfd);

        //利用多线程实现并发操作
        //待传入的参数
        struct arg need;
        need.fd=newfd;
        need.cin=cin;
        //创建子线程用于和客户端进行交互
        pthread_t pid = -1;
        if(pthread_create(&pid,NULL,msg_hander,&need)==-1)
        {
            printf("phread_create error\n");
            return -1;
        }
        pthread_detach(pid);


    }

}