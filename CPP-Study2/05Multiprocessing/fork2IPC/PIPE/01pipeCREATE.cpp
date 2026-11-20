#include<unistd.h>
#include<iostream>
#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>
using namespace std;

int main()
{
    //创建无名管道
    int fildes[2];
    if(pipe(fildes) == -1)
    {
        perror("pipe error");
        return -1;
    }
    printf("fildes[0] = %d, fildes[1] = %d\n",fildes[0],fildes[1]);//3 4
    //为什么是3和4，因为这两个数是文件描述符，系统默认给stdout stdin stderr 分配给0 1 2 以此类推分配给3和4


    //创建子进程
    pid_t pid=fork();
    if(pid>0)
    {//父进程
        //父进程不用读端，就关闭
        close(fildes[0]);

        



        //父进程关闭写端
        close(fildes[1]);
        wait(NULL);          //父进程收尸子进程

    }
    else if(pid==0)
    {//子进程
        //子进程不用写端，就关闭
        close(fildes[1]);




        //子进程关闭读端
        close(fildes[0]);
        //子进程退出
        exit(EXIT_SUCCESS);
    }
    else
    {
        perror("fork error");
        return -1;
    }
    return 0;
}