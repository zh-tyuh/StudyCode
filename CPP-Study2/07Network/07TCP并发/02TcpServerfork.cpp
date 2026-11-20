#include<iostream>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/signal.h>
#include<sys/wait.h>
#define SER_IP "192.168.237.137"
#define SER_PORT 8888

void hander(int signum)
{//信号处理
    if(signum == SIGCHLD)
    {
        while(waitpid(0,NULL,WNOHANG)>0);//只要存在未成功回收的进程就进行非阻塞回收直道waitpid=0
    }

}

int main()
{   
    //更改退出进程信号处理方式
    if(signal(SIGCHLD,hander)==SIG_ERR)
    {
        perror("signal error");
        return -1;
    }
  
    


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

        //利用多进程实现并发操作
        //创建一个新的进程用于与新客户端newfd进行通信，主线程只用于阻塞等待客户端的连接
        pid_t pid = fork();
        if(pid>0)
        {//父进程
            //主进程中的资源同时存在与父进程和子进程中
            //主进程只负责阻塞等待客户端连接，不进行通信，所以需要关闭newfd文件描述符
            close(newfd);

            //回收资源采用信号方式回收
            //wait()阻塞回收，当进行阻塞回收的时候，

        }
        else if(pid == 0)
        {//子进程，用于与客户端进行通信
            //子进程中会复制所有fork之前的主进程的资源，包含newfd和sfd
            //子进程只需要用到专门用于通信的newfd文件描述符，不需要使用创建新连接的sfd，所以需要关闭
            close(sfd);

            //进行通信
            char rbuf[128]="";
            while(1)
            {
                bzero(rbuf,sizeof(rbuf));
                if(recv(newfd,rbuf,sizeof(rbuf),0)==-1)
                {
                    perror("recv error");
                    return -1;
                }
                printf("[%s:%d]:%s\n",inet_ntoa(cin.sin_addr),ntohs(cin.sin_port),rbuf);

                //添加一个笑脸发回去
                strcat(rbuf,":>");
                if(send(newfd,rbuf,strlen(rbuf),0) ==-1)
                {
                    perror("send error");
                }
                printf("发送成功\n");
                if(strcmp(rbuf,"quit")==0)
                {
                    break;
                }
            }

            exit(EXIT_SUCCESS);
        }
        else
        {
            perror("fork errorr");
            return -1;
        }
    }

}