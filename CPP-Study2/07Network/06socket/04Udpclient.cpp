#include<iostream>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
using namespace std;
#define SER_IP "192.168.237.137"
#define SER_PORT 8888

int main()
{
    //1、创建套接字
    int cfd = socket(AF_INET,SOCK_DGRAM,0);
    if(cfd == -1)
    {
        perror("socket error");
        return -1;
    }

    //2、绑定端口号和IP地址（可选）

    //3、消息交互（非连接式）
    char wbuf[1024]="";
    //3.1 定义结构体存储服务端信息
    struct sockaddr_in sin;
    sin.sin_family=AF_INET;
    sin.sin_addr.s_addr=inet_addr(SER_IP);
    sin.sin_port=htons(SER_PORT);
    socklen_t size=sizeof(sin);
    
    while(1)
    {
        bzero(wbuf,sizeof(wbuf));
        fgets(wbuf,sizeof(wbuf),stdin);
        wbuf[strlen(wbuf)-1]='\0';

        if(sendto(cfd,wbuf,strlen(wbuf),0,(struct sockaddr*)&sin,size)==-1)
        {
            perror("sendto error");
            return -1;
        }

        if(recvfrom(cfd,wbuf,sizeof(wbuf),0,(struct sockaddr*)&sin,&size)==-1)
        {
            perror("recvfrom error");
            return -1;
        }
        printf("客户端返回的消息为：%s\n",wbuf);

    }

    //4、关闭套接字
    close(cfd);


}