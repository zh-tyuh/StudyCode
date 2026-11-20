#include<iostream>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>

int main()
{
    //1、创建套接字
    int cfd = socket(AF_UNIX,SOCK_DGRAM,0);
    if(cfd == -1)
    {
        perror("socket error");
        return -1;
    }

    //2、绑定ip地址和端口号(可选)    如果没有绑定，系统也不会自动绑定，会给的一个随机的文件
    //判断套接字文件是否存在
    if (access("./linux", F_OK) == 0)
    {
        //说明文件已经存在，需要将其进行删除操作
        if (unlink("./linux") == -1)
        {
            perror("unlink error");
            return -1;
        }
    }

    //2、绑定套接字文件
    sockaddr_un cun;
    cun.sun_family = AF_UNIX;
    strcpy(cun.sun_path,"./linux");
    if(bind(cfd,(sockaddr*)&cun,sizeof(cun))==-1)
    {
        perror("bind error");
        return -1;
    }


    
    //3、通信
    //服务端信息
    sockaddr_un sun;
    sun.sun_family = AF_UNIX;
    strcpy(sun.sun_path,"./unix");
    socklen_t size = sizeof(sun);


    char wbuf[128] ="";
    while(1)
    {
        bzero(wbuf,sizeof(wbuf));
        fgets(wbuf,sizeof(wbuf),stdin);
        wbuf[strlen(wbuf)-1]='\0';

        if(sendto(cfd,wbuf,strlen(wbuf),0,(struct sockaddr*)&sun,size)==-1)
        {
            perror("sendto error");
            return -1;
        }

        if(recvfrom(cfd,wbuf,sizeof(wbuf),0,(struct sockaddr*)&sun,&size)==-1)
        {
            perror("recvfrom error");
            return -1;
        }
        printf("服务端返回的消息为：%s\n",wbuf);

    }




}