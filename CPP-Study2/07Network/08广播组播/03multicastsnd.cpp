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
    int sndfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sndfd == -1)
    {
        perror("socket error");
        return -1;
    }

    //2、绑定端口号和IP地址（可选）


    //3、消息交互（非连接式）
    char wbuf[1024]="";
    //3.1 定义结构体存储   要收到信息的组的IP和端口
    struct sockaddr_in sndin;
    sndin.sin_family=AF_INET;
    sndin.sin_addr.s_addr=inet_addr("224.1.2.3");
    sndin.sin_port=htons(8888);
    socklen_t size=sizeof(sndin);
    
    while(1)
    {
        bzero(wbuf,sizeof(wbuf));
        fgets(wbuf,sizeof(wbuf),stdin);
        wbuf[strlen(wbuf)-1]='\0';

        if(sendto(sndfd,wbuf,strlen(wbuf),0,(struct sockaddr*)&sndin,size)==-1)
        {
            perror("sendto error");
            return -1;
        }

    }

    //4、关闭套接字
    close(sndfd);


}