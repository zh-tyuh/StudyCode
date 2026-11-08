#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

void handler(int signum)
{
    if(signum == SIGINT)
    {
        printf("捕获到了用户输入的CTRL+C\n");
    }
    else if(signum == SIGCHLD)
    {
        waitpid(-1,NULL,WNOHANG);
    }
}

int main()
{
    //SIGINT是中断信号，当用户输入ctrl+c时候发射来

    // //利用signam函数，将系统对该信号的处理方式改为忽略
    // if(signal(SIGINT,SIG_IGN) == SIG_ERR)
    // {
    //     perror("signal error");
    //     return -1;
    // }

    //利用signal函数，将系统对该信号的处理方式改为捕获(自定义函数)
    // if(signal(SIGINT,handler) == SIG_ERR)
    // {
    //     perror("signal error");
    //     return -1;
    // }


    //已知当子进程退出的时候，会向父进程发送一个SIGCHLD的信号
    //那么就可以利用这个特点利用signal函数修改内核对该信号的处理方式实现回收资源
    // if(signal(SIGCHLD,handler) == SIG_ERR)
    // {
    //     perror("signal error");
    //     return -1;
    // }


    //测试
    //创建十个僵尸进程
    for(int i=0;i<10;i++)
    {
        if(fork()== 0)
        {//表示该子进程
            exit(EXIT_SUCCESS);
        }
    }


    while(1);


    return 0;
}