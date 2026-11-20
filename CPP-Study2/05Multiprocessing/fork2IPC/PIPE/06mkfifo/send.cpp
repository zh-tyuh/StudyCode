#include<iostream>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main()
{
    //通过管道文件向接收端发送消息
    int sfd = -1;
    if((sfd = open("./myfifo",O_WRONLY))==-1)
    {
        perror("open error");
        return -1;
    }
    
    char wbuf[1024]="";
    while(1)
    {
        //将wbuf中的内容清楚
        bzero(wbuf,sizeof(wbuf));

        //利用stdin向wbuf中写入数据
        printf("请输入>>");
        fgets(wbuf,sizeof(wbuf),stdin);
        wbuf[strlen(wbuf)-1]='\0';

         //向管道文件中写入数据
        if(write(sfd,wbuf,strlen(wbuf))==-1)
        {
            perror("write error");
            return -1;
        }
        if(strcmp(wbuf,"quit")==0)
        {
            break;
        } 

        
    }

    //关闭文件
    close(sfd);
    return 0;

}


