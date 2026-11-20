#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include"sem.h"
#include<unistd.h>
#define PAGESZ 4096

int main()
{
    //进程1输出字符A，进程2输出字符B，进程3输出啊字符C，使用信号量集完成，最终输出的结果为ABCABCABCABC...
    
    int semid = create_sem(3);
    while(1)
    {   
        //申请1号信号灯的信号量资源
        P(semid,1);
        sleep(1);
        printf("B");
        fflush(stdout);
        //释放2信号灯的信号量资源
        V(semid,2);
    }

}