#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>

int main()
{
    //wait资源回收

    pid_t pid=-1;
    pid = fork();

    if(pid>0)
    {//父线程
        printf("PID = %d , ChildPID = %d , PPID = %d\n",getpid(),pid,getppid());
        printf("I am mie jianguo\n");

        sleep(8);
        //wait(NULL);
        waitpid(-1,NULL,WNOHANG);
        printf("子进程已经被回收\n");

    }
    else if(pid == 0)
    {//子线程
        printf("PID = %d , PPID = %d\n",getpid(),getppid());


        printf("I am mieba gangtiexia is my son");// 不进行换行即不刷新缓存区
        //虽然退出进程但是进程并没有被释放掉，处于Z僵尸状态
        
        exit(EXIT_SUCCESS); //会刷新缓存区后再退出进程
        //_exit(EXIT_SUCCESS);  //不会刷新缓存区，因此后面灭霸的信息没有打印在控制台

    }
    else
    {
        perror("fork error");
    }
    while(1); //如果没有防止函数终止的操作，如果父进程运行完直接终止，子进程就会变成孤儿进程，此时PPID为1
    return 0;
}