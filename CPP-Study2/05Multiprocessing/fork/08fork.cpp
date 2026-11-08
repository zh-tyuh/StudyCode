#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

int main()
{
    //父进程创建两个进程并为其收尸(回收资源)

    pid_t pid = fork();

    if(pid>0)
    {//父进程
        pid_t pid2 =fork();//创建第二个儿子
        if(pid2 > 0)
        {//父进程
            cout << "我是灭建国" << endl;
            wait(NULL);
            wait(NULL);
        }
        else if(pid2 == 0)
        {//第二个子进程
            sleep(3);
            cout << "我是灭道" << endl;
            exit(EXIT_SUCCESS);
        }
        else
        {
            perror("fork error");
            return -1;
        }

    }
    else if(pid == 0)
    {//第一个子进程
        sleep(3);
        cout << "我是灭霸" << endl;
        exit(EXIT_SUCCESS);
    }
    else
    {
        perror("fork error");
         return -1;
    }



}