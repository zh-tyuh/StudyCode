#include<iostream>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

int main()
{
    //作为接收端接收管道信息
    int rfd = -1;
    if((rfd=open("./myfifo",O_RDONLY))==-1)
    {
        perror("open error");
        return -1;
    }

    //读取有名管道中的信息，并将读取到的信息输出到控制台上
    char rbuf[1024]="";
    while(1)
    {   
        bzero(rbuf,strlen(rbuf));

        if(read(rfd,rbuf,sizeof(rbuf))==-1)   
        {
            perror("read error");
            return -1;
        }
        printf("读取到的信息是：%s\n",rbuf);
        if(strcasecmp(rbuf,"quit")==0)
        {
            break;
        }
    }

    //关闭文件
    close(rfd);
}