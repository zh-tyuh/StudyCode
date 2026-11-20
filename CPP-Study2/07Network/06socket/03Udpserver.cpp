#include<iostream>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#define SER_PORT 8888
#define SER_IP "192.168.237.137"

int main()
{
    //1、创建套接字
    int sfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sfd==-1)
    {
        perror("socket error");
        return -1;
    }

    //2、绑定IP地址和端口号
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(SER_IP);
    sin.sin_port = htons(SER_PORT);
    if(bind(sfd,(struct sockaddr*)&sin,sizeof(sin))==-1)
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
    {   
        //清空容器中的内容
        bzero(rbuf,sizeof(rbuf));
        //接收来自客户端的信息
        if(recvfrom(sfd,rbuf,sizeof(rbuf),0,(struct sockaddr*)&cin,&size)==-1)
        {
            perror("recvfrom error");
            return -1;
        }
        printf("[%s:%d]:%s\n",inet_ntoa(cin.sin_addr),ntohs(cin.sin_port),rbuf);
        //在后面添加一个笑脸然后返回
        strcat(rbuf,":>");
        if(sendto(sfd,rbuf,strlen(rbuf),0,(struct sockaddr*)&cin,size)==-1)
        {
            perror("send error");
            return -1;
        }
        printf("回复成功\n");
    }

    //4、关闭套接字
    close(sfd);


}