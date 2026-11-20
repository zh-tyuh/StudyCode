#include<iostream>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
using namespace std;


int main()
{
    //1、创建用于发送的套接字
    int sndfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sndfd == -1)
    {
        perror("socket error");
        return -1;
    }

    //设置套接字属性：允许进行广播
    int reuse = 1;
    if(setsockopt(sndfd,SOL_SOCKET,SO_BROADCAST,&reuse,sizeof(reuse))==-1)
    {
        perror("setsockopt error");
        return -1;
    }

    //2、绑定端口号和IP（可选）


    //3、消息交互（非连接式）
    char wbuf[1024]="";

    //3.1 定义结构体存储接收端信息，对应IP地址表示广播IP
    struct sockaddr_in rcvin;
    rcvin.sin_family=AF_INET;
    rcvin.sin_addr.s_addr=inet_addr("192.168.237.255");
    rcvin.sin_port=htons(8888);
    socklen_t size=sizeof(rcvin);
    
    while(1)
    {
        bzero(wbuf,sizeof(wbuf));
        fgets(wbuf,sizeof(wbuf),stdin);
        wbuf[strlen(wbuf)-1]='\0';

        if(sendto(sndfd,wbuf,strlen(wbuf),0,(struct sockaddr*)&rcvin,size)==-1)
        {
            perror("sendto error");
            return -1;
        }
        printf("发送成功\n");
    }

    //4、关闭套接字
    close(sndfd);


}