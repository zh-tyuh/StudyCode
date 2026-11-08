#include<iostream>
#include<stdio.h>
using namespace std;
#include"http.h"

void* msg_request(void* arg)
{
    int sock = *(int *)arg;
    delete(int *)arg;
    //调用信息处理函数，该函数是所有请求的入口
    //自定义函数：将接收客户端发送的请求，将信息进行处理
    //参数：客户端与服务端的通信套接字
    //返回值：
    hander_msg(sock);
    close(sock);
    return NULL;
}


//=========================主程序============================
int main(int argc,const char* argv[])
{
    //判断是否手动传入端口号
    int port = 80; //端口号默认是80
    if(argc>1)
    {//管理员手动传入端口号
        port = atoi(argv[1]);
        //功能：将给定的字符串变成整型
        //参数：字符串（只限于整型字符串）
        //返回值：整型
    }


    //第一步需要先接收http请求
    //初始化服务器
    //自定义函数：功能完成tcp服务器的初始化操作，包括创建套接字，绑定端口号和监听
    //参数：端口号
    //返回值：服务器套接字
    int lis_socket = init_server(port);   


    //循环接收客户端的连接请求
    //并发服务器使用多线程实现
    while(1)
    {
        struct sockaddr_in peer;  //接收客户端的地址信息结构体
        socklen_t len=sizeof(peer);//接受长度
        //接收客户端的连接请求
        //返回的套接字就是服务端用于处理和客户端进行通信的套接字文件描述符
        int new_sock=accept(lis_socket,(struct sockaddr*)&peer,&len);
        if(new_sock == 0)
        {
            perror("accept error");
            return -1;
        }
        printf("您有新的客户端(%d)发来连接了\n",new_sock);


        //创建分支线程用于跟客户端进行通信
        pthread_t tid=-1;
        if(pthread_create(&tid,NULL,msg_request,new int(new_sock))>0)
        {
            printf("pthread_create error\n");
            return -1;
        }

        //将线程设置为分离态
        pthread_detach(tid);



    }

}