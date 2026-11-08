#include<stdio.h>
#include<unistd.h>

int main()
{
    //关注fork的返回值
    pid_t pid = -1;

    pid = fork();  //返回值对于父进程而言，是子进程的pid，即pid = 子进程的pid; 对于子进程而言pid = 0

    //因此可以根据pid让子进程和父进程执行不同的任务
    if(pid>0)
    {//父进程要执行的任务
        printf("child pid is %d\n",pid);
        printf("iam Dad\n");
    }
    else if(pid==0)
    {//子进程要执行的任务
        printf("pid = %d\n",pid);
        printf("iam CHILD\n");
    }
    else
    {
        perror("fork error");
    }

    while(1); 
}