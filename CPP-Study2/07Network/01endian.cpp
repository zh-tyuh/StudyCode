#include<iostream>
#include<stdio.h>
using namespace std;

int main()
{
    //利用指针查看自己的主机是大端存储还是小端存储
 
    int num = 0x12345678; //定义一个4字节int型
    char* ptr = (char*)&num;  //获取num的第一个字节的数据

    if(*ptr==0x12)
    {//内存地址的低位存储num数据的高位
        printf("big endian\n");
    }
    else if(*ptr==0x78)
    {//内存地址的低位存储数据的低位
        printf("little endian\n");
    }
    else
    {
        printf("error");
        return 0;
    }

    printf("hello world\n");
    return 0;
}