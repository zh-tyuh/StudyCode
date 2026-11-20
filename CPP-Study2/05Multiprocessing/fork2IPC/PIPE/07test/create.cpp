#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>



int main()
{   
    //创建有名管道1，即灭霸向小浣熊发送数据的管道
    if(mkfifo("./mtoh",0064)==-1)
    {
        perror("mkfifo error");
        return -1;
    }
    printf("mtoh创建成功\n");

    //创建有名管道2，即小浣熊向灭霸发送数据的管道
    if(mkfifo("./htom",0064)==-1)
    {
        perror("mkfifo error");
        return -1;
    }
    printf("htom创建成功\n");
}