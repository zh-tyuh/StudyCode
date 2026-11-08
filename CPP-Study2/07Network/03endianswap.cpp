#include<iostream>
#include<stdio.h>
#include<arpa/inet.h>

int main()
{
    //网络字节序和主机字节序之间的转换
    int num=0x12345678;
    printf("hostnum = %#x\n",num);  //小端
    int netnum = htonl(num);
    printf("netnum = %#x\n",netnum); //大端
}
