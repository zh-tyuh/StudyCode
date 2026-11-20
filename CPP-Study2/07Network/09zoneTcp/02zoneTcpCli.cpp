#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/un.h>
#include<string.h>
#define SER_IP "192.168.237.131"
#define SER_PORT 8888
#define CLI_IP "192.168.237.131"
#define CLI_PORT 9977

int main()
{
    //1、创建通信套接字cfd
    int cfd=socket(AF_UNIX,SOCK_STREAM,0);  //第一个参数表示IPV4，第二个参数表示通信类型为TCP
    if(cfd==-1)
    {
        perror("socket error");
        return -1;
    }


    //判断绑定的套接字文件是否存在
    if(access("./Linux",F_OK)==0)
    {
        if(unlink("./Linux")==-1)
        {
            perror("unlink error");
            return -1;
        }
    }


    //2、为客户端绑定套接字文件，也可以不绑定，如果不进行绑定，系统不会帮其自动绑定一个随机文件，文件名是一个乱码
    //2.1创建一个结构体存储客户端信息
    struct sockaddr_un cun;
    cun.sun_family=AF_UNIX;
    strcpy(cun.sun_path,"./Linux");

    //为套接字绑定该信息
    if(bind(cfd,(struct sockaddr*)&cun,sizeof(cun))==-1)
    {
        perror("bind error");
        return -1;
    }
    printf("bind success\n");

    //3、将客户端与服务端建立连接
    //3.1创建服务端相关信息
    struct sockaddr_un sun;
    sun.sun_family=AF_UNIX;
    strcpy(sun.sun_path,"./unix");

    //3.2建立连接
    if(connect(cfd,(sockaddr*)&sun,sizeof(sun))==-1)
    {
        perror("connect error");
        return -1;
    }
    printf("connect success\n");

    //4、收发消息
    char wbuf[128]="";
    while(1)
    {
        //清空容器中的数据
        bzero(wbuf,sizeof(wbuf));

        //从终端中读取数据并发送
        fgets(wbuf,sizeof(wbuf),stdin);
        wbuf[strlen(wbuf)-1]='\0';//将换行变成'\0'

        if(send(cfd,wbuf,sizeof(wbuf),0)==-1)  //参数0表示阻塞等待
        {
            perror("send error");
            return -1;
        }
        printf("发送成功\n");

        if(recv(cfd,wbuf,sizeof(wbuf),0)==0)
        {
            printf("对端已下线\n");
            break;
        }

        printf("收到服务端的消息为%s\n",wbuf);
    }

    //5、关闭套接字
    close(cfd);
}

