#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
    //gitpid 和 gitppid 函数

    pid_t pid=-1;
    pid = fork();

    if(pid>0)
    {//父线程
        printf("I am mie jianguo\n");
        printf("PID = %d , ChildPID = %d , PPID = %d\n",getpid(),pid,getppid());
    }
    else if(pid == 0)
    {//子线程
        printf("I am mieba\n");
        printf("PID = %d , PPID = %d\n",getpid(),getppid());
    }
    else
    {
        perror("fork error");
    }

    while(1); //如果没有防止函数终止的操作，如果父进程运行完直接终止，子进程就会变成孤儿进程，此时PPID为1

    return 0;




}