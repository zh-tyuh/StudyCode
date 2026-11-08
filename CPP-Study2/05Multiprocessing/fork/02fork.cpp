#include<stdio.h>
#include<unistd.h>
 int main()
 { 
    //不关注fork的返回值
 
    printf("Before i have a child\n");

    
    fork();//创建子进程之后子进程会直接拷贝父进程的后续资源
    printf("Hello,World\n"); //子进程


    while(1);
    return 0;
 }