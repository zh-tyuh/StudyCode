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


    //因为select中的参数1表示集合中最大的文件描述符+1，又因为当有多个客户端进行连接时，最大的文件描述符不一定是newfd
    //所以引用一个变量maxfd用来将记录当前set中最大的文件描述符
    int maxfd = sfd;

    //因为cin中保存的永远是最后一个accept的newfd的信息，之前连接的内容就丢失了
    //因此需要一个数组，记录每次accept的客户端的信息，而文件描述符可以作为其下标
    sockaddr_in arr_cin[1024];//为什么是1024，因为readset容器的最大限度就是1024


    while(1){
        tempfds=readfds;

        //调用select函数，完成对文件描述符的统一管理
        int res = select(maxfd+1,&tempfds,NULL,NULL,NULL);
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
        {//阻塞等待客户端的连接
            int newfd = accept(sfd,(sockaddr *)&cin,&cinlen);
            if(newfd==-1)
            {
                perror("accept error");
                return -1;  
            }
            printf("[%s:%d]:已连接成功\n",inet_ntoa(cin.sin_addr),ntohs(cin.sin_port));
            //保存新连接的客户端的信息
            arr_cin[newfd].sin_addr=cin.sin_addr;
            arr_cin[newfd].sin_port=cin.sin_port;
            //将新连接的客户端文件描述符添加到select管理集合容器中
            FD_SET(newfd,&readfds);
            //更新maxfd 但是新连接的newfd不一定是最大的文件描述符 如原来的集合中有0 sfd 5 6 那么newfd就=4
            if(newfd > maxfd)
            {
                maxfd = newfd;
            }
        }
        
        if(FD_ISSET(0,&tempfds))
        {//阻塞等待用户从终端输入数据
            char wbuf[128]="";
            fgets(wbuf,sizeof(wbuf),stdin);
            printf("触发了键盘输入事件\n");
            //将键盘输入的消息发送到所有客户端
            for(int i=4;i<=maxfd;i++)
            {
                send(i,wbuf,sizeof(wbuf),0);
            }
        }

        for(int i=4;i<=maxfd;i++)   
        {
            /*为什么这里需要用一个for循环？
              因为在可能有多个客户端进行信息的收发，所以需要循环判断是那个客户端对应的文件描述符发来信息造成的阻塞
              如果不将进行循环判断，在FD_ISSET中填写newfd，则当除了newfd对应的文件描述符造成的阻塞会被处理以外，
              其余的文件描述符造成的阻塞不予处理
             */
            if(FD_ISSET(i,&tempfds))
            {//阻塞等待从客户端接收信息
                //5、接收信息
                char rbuf[128]="";
                bzero(rbuf,sizeof(rbuf));//每次接收信息将容器置空
                //从套接字中读取信息放在buf中
                if(recv(i,rbuf,sizeof(rbuf),0)==0)
                {
                    printf("对端已下线\n");
                    //当对端下线之后，需要对应的文件描述符
                    close(i);
                    //同时需要将对应的文件描述符在readfds中删除
                    FD_CLR(i,&readfds);
                    //同时更新maxfd
                    for(int k=maxfd;k>0;k--)
                    {//找出readfds中最大的文件描述符
                        if(FD_ISSET(k,&readfds))
                        {
                            maxfd=k;
                            break;
                        } 
                    }
                    continue;
                }
                printf("[%s:%d]:%s\n",inet_ntoa(arr_cin[i].sin_addr),ntohs(arr_cin[i].sin_port),rbuf);
                //在每一个消息后面加一个笑脸返回回去
                strcat(rbuf,"^_^");
                if(send(i,rbuf,sizeof(rbuf),0)==-1)
                {
                    perror("send error");
                    return -1;
                }
                printf("发送成功\n");
            }
        }
        
    }


    close(sfd);
    return 0;
}



