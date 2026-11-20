#include<iostream>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<stdlib.h>

//使用有名管道实现，两个进程之间相互通信，提示：可以使用多进程或多线程
int main()
{
    //小浣熊程序，利用多线程，父线程向有名管道1中读取灭霸写的数据，子线程从有名管道2中写入数据
    
    pid_t pid = fork();
     
    if(pid>0)
    {//父进程，从有名管道1中读取数据
        //打开有名管道1
        int rfd=-1;
        if((rfd=open("./mtoh",O_RDONLY))==-1)
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
            printf("灭霸：%s\n",rbuf);
            if(strcmp(rbuf,"quit")==0)
            {
                break;
            }
        }
        //关闭文件描述符并回收资源
        close(rfd);
        wait(NULL);
    }
    
    else if(pid==0)
    {//子进程，向有名管道2中写入数据
        int wfd=-1;
        if((wfd=open("./htom",O_WRONLY))==-1)
        {
            perror("open error");
            return -1;
        }

        char wbuf[1024]="";
        while(1)
        {
            //bzero(wbuf,sizeof(wbuf));
            //从控制台中获取字符串并写入
            fgets(wbuf,sizeof(wbuf),stdin);
            wbuf[strlen(wbuf)-1]='\0';
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

        //关闭文件标识符并退出进程
        close(wfd);
        exit(EXIT_SUCCESS);
    }
    else
    {
        perror("fork error");
        return -1;
    }
        
}