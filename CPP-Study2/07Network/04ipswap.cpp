#include<iostream>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string>
 
int main()
{
    //利用内置函数将点分十进制IP字符串转化为4字节的无符号整型
    const char* ip1="192.168.237.1";   //相当于0xC0 A8 ED 1
    unsigned int ip = inet_addr(ip1);

    //按照小端存储输出结果应该是0x1EDA8C0
    printf("%#x\n",ip);
}