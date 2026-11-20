#include<unistd.h>
#include<iostream>
#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<string.h>
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
        //父进程关闭读端
        close(fildes[0]);

        char wbuf[128]="hello MySon";
        write(fildes[1],wbuf,strlen(wbuf));

        /*读端不存在再向写端写入数据：
        初始时，父进程读端关闭，子进程写端关闭，也就是说无名管道只有父进程的写端和子进程的读端
        /此时父进程休眠3秒，子进程已经关闭了读端。  再向无名管道中写入数据，就会错误
        sleep(3);
        write(fildes[1],wbuf,strlen(wbuf));
        */

        //while(1); 防止写端关闭，用来验证read阻塞

        //父进程关闭写端
        close(fildes[1]);
        wait(NULL);          //父进程收尸子进程

    }
    else if(pid==0)
    {//子进程
        //子进程关闭写端
        close(fildes[1]);

        char rbuf[128]="";

        while(1)
        {//写端不存在，再读东西，read不会进行阻塞
        read(fildes[0],rbuf,sizeof(rbuf));
        printf("我是灭霸，灭建国给我发的消息是：%s\n",rbuf);
        }

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