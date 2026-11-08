#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void handler(int signum)
{
    if(signum == SIGINT)
    {
        printf("捕获到了用户输入的CTRL+C\n");
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
    if(signal(SIGINT,handler) == SIG_ERR)
    {
        perror("signal error");
        return -1;
    }


    while(1)
    {
        sleep(1);
        printf("我真的好像再活500年\n");
    }


    return 0;
}