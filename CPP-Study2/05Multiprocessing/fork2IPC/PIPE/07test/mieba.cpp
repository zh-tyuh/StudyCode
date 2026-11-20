#include<iostream>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>

//使用有名管道实现，两个进程之间相互通信，提示：可以使用多进程或多线程
int main()
{
    //灭霸程序，利用多线程，父线程向有名管道1中写入数据，子线程从有名管道2中读取小浣熊写的数据
    pid_t pid = fork();
    if(pid>0)
    {//父进程，向有名管道1中写入数据
        //打开管道文件
        int wfd=-1;
        if((wfd=open("./mtoh",O_WRONLY))==-1)
        {
            perror("open error");
            return -1;
        }
        char wbuf[1024]="";
        while(1)
        {
            bzero(wbuf,sizeof(wbuf));
            //从终端中读取数据
            fgets(wbuf,sizeof(wbuf),stdin);
            wbuf[strlen(wbuf)-1]='\0';//将输入的\n变成\0

           
            if(write(wfd,wbuf,strlen(wbuf))==-1)
            {
                perror("write error");
                return -1;
            }
            if(strcmp(wbuf,"quit")==0)
            {
                break;
            }
        }
    
    //退出文件描述符并回收子进程资源
    close(wfd);
    wait(NULL);
    }
    else if(pid==0)
    {//子进程，从有名管道2中读取数据
        int rfd=-1;
        if((rfd=open("./htom",O_RDONLY))==-1)
        {
            perror("open error");
            return -1;
        }
        char rbuf[1024]="";
        while(1)
        {
            bzero(rbuf,sizeof(rbuf));
            
            if(read(rfd,rbuf,sizeof(rbuf))==-1)
            {
                perror("read error");
                return -1;
            }
            printf("小浣熊：%s\n",rbuf);
            if(strcmp(rbuf,"quit")==0)
            {
                break;
            }
        }    
    //关闭文件描述符并推出进程
    close(rfd);
    exit(EXIT_SUCCESS);
    }
    else
    {
        perror("fork error");
        return -1;
    }


}