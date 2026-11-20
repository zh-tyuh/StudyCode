#include<iostream>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>


int main()
{
    //1、创建套接字
    int rcvfd = socket(AF_INET,SOCK_DGRAM,0);
    if(rcvfd==-1)
    {
        perror("socket error");
        return -1;
    }

    //2、绑定IP地址和端口号
    sockaddr_in rcvin;
    rcvin.sin_family = inet_addr("192.168.237.137");
    rcvin.sin_addr.s_addr = INADDR_ANY;
    rcvin.sin_port = htons(8888);
    if(bind(rcvfd,(struct sockaddr*)&rcvin,sizeof(rcvin))==-1)
    {
        perror("bind error");
        return -1;
    }
    printf("bind success\n");

    //3、接受客户端发来的消息，并添加一个笑脸返回给客户端
    char rbuf[1024]="";
    sockaddr_in cin;  //接收客户端的IP和端口号
    socklen_t size = sizeof(cin);
    while(1)
    {   printf("nihao \n");
        //清空容器中的内容
        bzero(rbuf,sizeof(rbuf));
        //接收来自客户端的信息
        if(recvfrom(rcvfd,rbuf,sizeof(rbuf),0,(struct sockaddr*)&cin,&size)==-1)
        {
            perror("recvfrom error");
            return -1;
        }
        printf("hello\n");
        printf("[%s:%d]:%s\n",inet_ntoa(cin.sin_addr),ntohs(cin.sin_port),rbuf);
        
    }

    //4、关闭套接字
    close(rcvfd);


}