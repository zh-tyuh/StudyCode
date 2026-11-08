#include<stdio.h>
#include<unistd.h>

int main()
{
    //父子进程并发执行,没有先后顺序
    
    pid_t pid = -1;

    pid = fork();  //返回值对于父进程而言，是子进程的pid，即pid = 子进程的pid; 对于子进程而言pid = 0

    //因此可以根据pid让子进程和父进程执行不同的任务
    if(pid>0)
    {//父进程要执行的任务
        while(1)
        {
        printf("iam Dad1111\n");
        sleep(1);
        }
    }
    else if(pid==0)
    {//子进程要执行的任务
        while(1)
        {
        printf("iam CHILD\n");
        sleep(1);
        }
    }
    else
    {
        perror("fork error");
    }

    while(1);
}