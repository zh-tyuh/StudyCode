#include<stdio.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<string.h>

#define PAGESZ 4096

int main()
{
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
        printf("请输入>>");
        fgets(addr,PAGESZ,stdin);
        addr[strlen(addr)-1]='\0';
        if(strcmp(addr,"quit")==0)
        {
            break;
        }
    }

    //删除映射关系
    if(shmdt(addr)==-1)
    {
        perror("shmdt error");
        return -1;
    }


}