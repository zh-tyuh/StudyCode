#include<stdio.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<string.h>
#include<unistd.h>
#include"sem.h"
#define PAGESZ 4096

int main()
{
    //11、创建信号量集  
    int semid = create_sem(2);

    //1、创建key值
    key_t key=-1;
    if((key=ftok("/",'k'))==-1)
    {
        perror("ftok error");
        return -1;
    }

    //2、通过key值创建共享内存段
    int shmid=-1;
    if((shmid=shmget(key,PAGESZ,IPC_CREAT|0664))==-1)
    {
        perror("shmget error");
        return -1;
    }

    //3、将共享内存段的地址映射到用户空间
    char* addr =(char *)(shmat(shmid,NULL,0));
    if(addr==(void*)-1)
    {
        perror("shmat error");
        return -1;
    }

    //4、对共享内存进行操作
    //从终端中输入字符串放在共享内存中
    while(1)
    {   
        //22、申请1号的信号灯的资源
        P(semid,1);

        printf("收到的信息为：%s\n",addr);

        if(strcmp(addr,"quit")==0)
        {
            break;
        }
        //33、释放0号信号灯的信号量资源
        V(semid,0);
    }

    //删除映射关系
    if(shmdt(addr)==-1)
    {
        perror("shmdt error");
        return -1;
    }

    //删除共享内存段
    if(shmctl(shmid,IPC_RMID,NULL)==-1)
    {
        perror("shmctl error");
        return -1;
    }

    //删除信号集
    delete_sem(semid);

}