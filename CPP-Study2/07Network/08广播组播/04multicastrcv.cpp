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
    int rcvfd = socket(AF_INET,SOCK_DGRAM,0);
    if(rcvfd==-1)
    {
        perror("socket error");
        return -1;
    }

    //1.5 将该套接字加入到组中
    int reuse = 1;
    struct ip_mreqn imr;
    imr.imr_address.s_addr = inet_addr("192.168.237.137");
    imr.imr_multiaddr.s_addr = inet_addr("224.1.2.3");
    imr.imr_ifindex = 2;
    if(setsockopt(rcvfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&imr,sizeof(imr))==-1)
    {
        perror("setsockopt error");
        return -1;
    }


    //2、绑定IP地址和端口号
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr("224.1.2.3");
    sin.sin_port = htons(8888);
    if(bind(rcvfd,(struct sockaddr*)&sin,sizeof(sin))==-1)
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
        if(recvfrom(rcvfd,rbuf,sizeof(rbuf),0,(struct sockaddr*)&cin,&size)==-1)
        {
            perror("recvfrom error");
            return -1;
        }
        printf("[%s:%d]:%s\n",inet_ntoa(cin.sin_addr),ntohs(cin.sin_port),rbuf);
    
    }

    //4、关闭套接字
    close(rcvfd);


}