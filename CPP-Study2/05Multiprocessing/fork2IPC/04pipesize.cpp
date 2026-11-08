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

    //测试无名管道中的最大容量
    char buf='A';
    int count=0;
    while(1)
    {
    write(fildes[1],&buf,1);//向无名管道中每次写入1字节数据
    count++;
    printf("count = %d\n",count);  
    }
    //会发现循环在count=65536处终止，也就是在64K处无名管道满了

    close(fildes[0]);
    close(fildes[1]);
    return 0;

}