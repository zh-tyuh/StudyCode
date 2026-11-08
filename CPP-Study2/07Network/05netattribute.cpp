#include<iostream>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h> //close
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#define SET_IP "192.168.237.131"
#define SET_PORT 8888


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




    //网络属性的设置
    //查看当前套接字文件描述符的属性
    int reuse = -1;
    socklen_t reuselen;
    if(getsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&reuse,&reuselen)==-1)
    {
        perror("getsockaddr error");
        return -1;
    }
    printf("reuse = %d \n",reuse);   //reuse = 0 表示地址快速重用的属性处于关闭状态

    //设置端口快速重用
    reuse = 1;    //reuse = 1 表示地址快速重用的属性处于关闭状态
    if(setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse))==-1)
    {
        perror("setsockopt error");
        return -1;
    }
    
    if(getsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&reuse,&reuselen)==-1)
    {
        perror("getsockaddr error");
        return -1;
    }
    printf("reuse = %d \n",reuse);   //reuse = 0 表示地址快速重用的属性处于关闭状态








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
    int newfd = accept(sfd,(sockaddr *)&cin,&cinlen);
    if(newfd==-1)
    {
        perror("accept error");
         return -1;
    }
    printf("[%s:%d]:已连接成功\n",inet_ntoa(cin.sin_addr),ntohs(cin.sin_port));

    
    //5、接收信息
    char rbuf[128]="";
    while(1)
    {
        bzero(rbuf,sizeof(rbuf));//每次接收信息将容器置空
        
        //从套接字中读取信息放在buf中
        if(recv(newfd,rbuf,sizeof(rbuf),0)==0)
        {
            printf("对端已下线\n");
            break;
        }
        printf("[%s:%d]:%s\n",inet_ntoa(cin.sin_addr),ntohs(cin.sin_port),rbuf);

        //在每一个消息后面加一个笑脸返回回去
        strcat(rbuf,"^_^");
        if(send(newfd,rbuf,sizeof(rbuf),0)==-1)
        {
            perror("send error");
            return -1;
        }

        printf("发送成功\n");
    }
    
    //关闭套接字
    close(newfd);
    close(sfd);

    
    return 0;
}