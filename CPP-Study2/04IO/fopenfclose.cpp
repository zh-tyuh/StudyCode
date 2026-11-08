#include<stdio.h>
#include<errno.h> //中包含着一个全局变量errno 存储着错误码
#include<string.h>

int main(int argc,const char* argv[])
{
    //定义一个FILE类型的变量
    FILE *fp = NULL;
    
    //打开一个文件，如果通过只读的方式打开一个不存在的文件会出现错误，使用只写的方式打开会自动创建一个文件
    fp = fopen("./test.txt","r");
    if(fp == NULL)
    {
        //printf("fopen error:%d,errmsg:%s\n",errno,strerror(errno));
        perror("fopen error");//输出引号中的信息后打印错误信息
        return -1;
    }
    printf("fopen success\n");

    fclose(fp);
    return 0;
}