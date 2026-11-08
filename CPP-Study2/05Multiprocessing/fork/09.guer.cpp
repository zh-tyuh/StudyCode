#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

int main()
{   
    pid_t pid = fork();
    if(pid>0)
    {//父进程
        sleep(3);
        cout<<"我是灭建国"<<endl;
        exit(EXIT_SUCCESS);
    }
    else if(pid == 0)
    {//子进程
        sleep(8);
        cout<<"我是灭霸"<<endl;
        exit(EXIT_SUCCESS);
    }
    else
    {
        perror("fork error\n");
        return -1;
    }
    while(1);
    return 0;
}
