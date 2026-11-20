#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

void hander(int signum)
{
    if(signum == SIGUSR1)
    {
        printf("逆子，何至于此！！！\n");
        wait(NULL);
        raise(SIGKILL); //向自己发送一个杀死自己的信号
    }
}

int main()
{
    //使用kill函数发送信号
    
    //用户自定义信号SIGUSR1
    if(signal(SIGUSR1,hander) == SIG_ERR)
    {
        perror("signal error");
        return -1;
    }

    //创建子进程
    pid_t pid = fork();
    if(pid == -1)
    {
        perror("fork error");
        return -1;
    }

    if(pid>0)
    {//父进程
        while(1)
        {
            printf("我真的好想再活五百年！\n");
            sleep(1);
        }
    }
    else if(pid == 0)
    {//子进程
        //向父进程发送一个信号，让父进程自杀
        sleep(5);
        printf("红尘已经看破，叫上父亲一起赴黄泉吧\n");
        kill(getppid(),SIGUSR1);
        exit(EXIT_SUCCESS);
    }
    else{
        return -1;     
    }
}