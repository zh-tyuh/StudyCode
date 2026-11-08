//和终端文件相关的缓冲区叫做行缓存，行缓冲区的大小为1024字节，对应的文件指针：stdin、stdout
#include<iostream>
#include<stdio.h>
using namespace std;

int main(int argc,const char* argv[])
{
    //如果缓存区没有被使用，求出大小为0，只有被至少使用一次之后，缓存区的大小才会被分配
    printf("行缓存的大小为：%d", stdout->_IO_buf_end - stdout-> _IO_buf_base);  //0
    printf("行缓存的大小为：%d", stdout->_IO_buf_end - stdout-> _IO_buf_base);  //1024




}
 