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
    if(pipe(fildes)==-1)
    {
        perror("pipe error");
        return -1;
    }

    //自己也可以给自己传输数据
    char wbuf[100]="You Are So HandSome";
    char rbuf[100]="";
    //向无名管道写入数据
    write(fildes[1],wbuf,strlen(wbuf));
    //从无名管道中读出数据
    read(fildes[0],rbuf,sizeof(rbuf));

    printf("我自己给自己发的消息是：%s\n",rbuf);
    return 0;

}