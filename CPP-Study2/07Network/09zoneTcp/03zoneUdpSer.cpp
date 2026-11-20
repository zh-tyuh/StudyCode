#include<iostream>
#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<sys/un.h>

int main()
{
    //1、创建用于通信的套接字，协议族是本地通信，通信类型是Udp
    int sfd = socket(AF_UNIX,SOCK_DGRAM,0);
    if(sfd == -1)
    {
        perror("socket error");
        return -1;
    }

    //2、判断用于通信的套接字文件是否存在于系统中
    if(access("./unix",F_OK)==0)
    {//删除文件
        if(unlink("./unix")==-1)
        {
            perror("unlink error");
            return -1;
        }
    }

    //3、将该套接字绑定套接字文件
    sockaddr_un sun;
    strcpy(sun.sun_path,"./unix");
    sun.sun_family = AF_UNIX;
    if(bind(sfd,(struct sockaddr*)&sun,sizeof(sun))==-1)
    {
        perror("bind error");
        return -1;
    }
    printf("bind sucess\n");

    //5、收发消息
    char rbuf[128]="";
    //创建一个结构体用于接收客户端的信息
    sockaddr_un cun;
    socklen_t size = sizeof(cun);

    while(1)
    {   
        //清空容器中的内容
        bzero(rbuf,sizeof(rbuf));
        //接收来自客户端的信息
        if(recvfrom(sfd,rbuf,sizeof(rbuf),0,(struct sockaddr*)&cun,&size)==-1)
        {
            perror("recvfrom error");
            return -1;
        }
        printf("[%s]:%s\n",cun.sun_path,rbuf);
        //在后面添加一个笑脸然后返回
        strcat(rbuf,":>");
        if(sendto(sfd,rbuf,strlen(rbuf),0,(struct sockaddr*)&cun,size)==-1)
        {
            perror("send error");
            return -1;
        }
        printf("回复成功\n");
    }

    close(sfd);
}