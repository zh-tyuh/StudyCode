#include<iostream>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h> //close
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/select.h>
#define SET_IP "192.168.237.131"
#define SET_PORT 8889


int main()
{
    //1、创建一个套接字，并返回对应的文件描述符
    int sfd = socket(AF_INET,SOCK_STREAM,0);
    if(sfd==-1)
    {
        perror("socket error");
        return -1;
    }
    printf("socket success sfd=%d\n",sfd); //3

    //2、为套接字分配名称，给套接字绑定ip地址和端口号
    //2.1 创建套接字信息结构体，方便绑定时传参数
    struct sockaddr_in sin;
    sin.sin_family=AF_INET;
    sin.sin_addr.s_addr=inet_addr(SET_IP);
    sin.sin_port=htons(SET_PORT);
    //2.2 绑定工作
    //参数：1、要被绑定的套接字文件描述符
    //2、参数2表示要绑定信息结构体，需要进行强制类型转换
    if(bind(sfd,(sockaddr*)&sin,sizeof(sin))==-1)
    {
        perror("bind error");
        return -1;
    }

    //3、监听，将套接字设置为监听状态
    //参数1：套接字文件描述符
    //参数2：挂起队列能够增长的最大长度，一般是128。也就是能够同时监听的客户端最大限度
    if(listen(sfd,128)==-1)
    {
        perror("listen error");
        return -1;
    }
    printf("listen success\n");

    //4、阻塞等待客户端的连接请求
    //如果已连接队列中有客户端，则从连接队列中拿取第一个，并创一个用于通信的套接字返回
    //参数1：服务器套接字的文件描述符
    //参数2：是一个sockaddr类型的指针，指向存储包含了客户端的信息结构体
    //参数3：是参数2的大小
    struct sockaddr_in cin;
    socklen_t cinlen=sizeof(cin);

    fd_set readfds,tempfds;

    FD_ZERO(&readfds);
    FD_SET(0,&readfds);
    FD_SET(sfd,&readfds);


    while(1){
        tempfds=readfds;

        //调用select函数，完成对文件描述符的统一管理
        int res = select(sfd+1,&tempfds,NULL,NULL,NULL);

        if(res<0)
        {
            perror("select error");
            return -1;
        }
        else if(res==0)
        {
            printf("time out!!!\n");
            return -1;
        }

        //如果执行至此，说明至少有一个文件描述符触发了事件，只需要判断那个文件描述符存在即可
        
        if(FD_ISSET(sfd,&tempfds))
        {
            //阻塞等待客户端的连接
            int newfd = accept(sfd,(sockaddr *)&cin,&cinlen);
            if(newfd==-1)
            {
                perror("accept error");
                return -1;  
            }
            printf("[%s:%d]:已连接成功\n",inet_ntoa(cin.sin_addr),ntohs(cin.sin_port));
        }
        
        if(FD_ISSET(0,&tempfds)){
            //阻塞等待用户从终端输入数据
            char wbuf[128]="";
            fgets(wbuf,sizeof(wbuf),stdin);
            printf("触发了键盘输入事件\n");
        }
    }
    close(sfd);

    
    return 0;
}