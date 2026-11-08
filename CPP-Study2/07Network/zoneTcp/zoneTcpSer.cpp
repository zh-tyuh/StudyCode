#include<iostream>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h> //close
#include<netinet/in.h>
#include<sys/un.h>
#include<string.h>
#include<arpa/inet.h>
#define SET_IP "192.168.237.131"
#define SET_PORT 8888

//流式域套接字的服务端实现

int main()
{
    

    //1、创建一个套接字，并返回对应的文件描述符
    int sfd = socket(AF_UNIX,SOCK_STREAM,0);
    if(sfd==-1)
    {
        perror("socket error");
        return -1;
    }
    printf("socket success sfd=%d\n",sfd); //3

    
    //注意：sun绑定的套接字文件必须是一个不存在的文件，如果存在，需要先将该套接字文件删除
    if(access("./unix",F_OK)==0)
    {
        //该文件存在，执行删除操作
        if(unlink("./unix")==-1)
        {
            perror("unlink error");
            return -1;
        }
    }


    //2、为套接字分配名称，给套接字绑定本地套接字路径
    //2.1 创建套接字信息结构体，方便绑定时传参数
    struct sockaddr_un sun;
    sun.sun_family=AF_UNIX;
    strcpy(sun.sun_path,"./unix"); //对于字符串，不能使用等号赋值
    

    //2.2 绑定工作
    //参数：1、要被绑定的套接字文件描述符
    //2、参数2表示要绑定信息结构体，需要进行强制类型转换
    if(bind(sfd,(sockaddr*)&sun,sizeof(sun))==-1)
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
    struct sockaddr_un cun;
    socklen_t cunlen=sizeof(cun);
    int newfd = accept(sfd,(sockaddr *)&cun,&cunlen);
    if(newfd==-1)
    {
        perror("accept error");
         return -1;
    }
    printf("[%s]:已连接成功\n",cun.sun_path);

    
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
        printf("[%s]:%s\n",cun.sun_path,rbuf);

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
