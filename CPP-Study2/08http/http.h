#include<sys/types.h>
#include<netinet/in.h>
#include<pthread.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/sendfile.h>

#define SIZE 4096


#ifndef HTTP_H
#define HTTP_H

//声明初始化服务器函数
int init_server(int _port);
//声明信息处理函数
int hander_msg(int _sock);



#endif