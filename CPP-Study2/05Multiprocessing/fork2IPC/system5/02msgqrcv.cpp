#include<stdio.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<string.h>
#include<unistd.h>
struct msgBuf
{
    long mtype;
    char mtext[128];
};
#define MSGSZ (sizeof(struct msgBuf)-sizeof(long))  //工程习惯

int main()
{
    //1、创建key值
    key_t key=-1;
    if((key=ftok("/",'k'))==-1)
    {
        perror("ftok error");
        return -1;
    }

    //2、根据key值创建消息队列
    int msgid=-1;
    if((msgid = msgget(key,IPC_CREAT|0664))==-1)
    {
        perror("msgget error");
        return -1;
    }

    //3、从消息队列中接收消息
    while(1)
    {
        struct msgBuf tmsg;
        if(msgrcv(msgid,&tmsg,MSGSZ,0,0)==-1)
        {
            perror("msgrcv error");
            return -1;
        }
        printf("收到的信息为%s\n",tmsg.mtext);
        if(strcmp(tmsg.mtext,"quit")==0)
        {
            break;
        }
    }

    //4、删除消息队列
    if(msgctl(msgid,IPC_RMID,NULL)==-1)
    {
        perror("rm error");
        return -1;
    }

}