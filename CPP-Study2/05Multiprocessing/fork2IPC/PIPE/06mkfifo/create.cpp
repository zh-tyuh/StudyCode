#include<iostream>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>


int main()
{
    //创建一个有名管道文件
    if(mkfifo("./myfifo",0064) == -1)
    {
        perror("mkfifo error");
        return -1;
    }

    printf("管道文件创建成功！！\n");
    return 0;
}