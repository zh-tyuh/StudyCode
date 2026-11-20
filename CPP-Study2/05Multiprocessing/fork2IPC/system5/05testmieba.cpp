#include<stdio.h>
#include<sys/ipc.h>
#include<string.h>
#include<sys/msg.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>
struct msgBuf
{
    long mtype;
    char mtext[1024];
};
#define MSGSZ (sizeof(struct msgBuf)-sizeof(long))


int main()
{
    //练习：使用消息队列完成两个进程间相互通信
    //灭霸端，父进程向消息队列中写入信息，子进程从消息队列中读取信息
    //如果类型是1，表示小浣熊向灭霸发送了消息
    //如果类型为2，表示灭霸向小浣熊发送了消息

    //创建key值并创建消息队列
    key_t key=-1;
    if((key=ftok("/",'k'))==-1)
    {
        perror("ftok error");
        return -1;
    }
    int msgid=-1;
    if((msgid=msgget(key,IPC_CREAT|0664))==-1)
    {
        perror("msgget error");
        return -1;
    }
    printf("key = %#x\nmsgid = %d\n",key,msgid);

    
    //创建子进程
    pid_t pid=-1;
    pid=fork();
    
    if(pid>0)
    {//父进程，负责向消息队列中写入数据，即向小浣熊发送消息
        while(1)
        {
            struct msgBuf tmsg;
            tmsg.mtype=2;//表示灭霸向小浣熊发送的消息
            while(1)
            {
                fgets(tmsg.mtext,MSGSZ,stdin);
                tmsg.mtext[strlen(tmsg.mtext)-1]='\0';
                if(msgsnd(msgid,&tmsg,MSGSZ,0)==-1)
                {
                    perror("msgsnd error");
                    return -1;
                }

                if(strcmp(tmsg.mtext,"quit")==0)
                {
                    break;
                }
            }
        }
        //回收子进程资源
        wait(NULL);
    }
    else if(pid==0)
    {//子进程，负责从消息队列中读取数据
        struct msgBuf tmsg;
        while(1)
        {
            bzero(tmsg.mtext,MSGSZ);
            msgrcv(msgid,&tmsg,MSGSZ,1,0);
            printf("小浣熊：%s\n",tmsg.mtext);

            if(strcmp(tmsg.mtext,"quit")==0)
            {
                printf("小浣熊下线了\n");
                break;
            }                
        }

       //退出进程并销毁消息队列
       if(msgctl(msgid,IPC_RMID,NULL)==-1)
       {
            perror("msgctl error");
            return -1;
       }
       exit(EXIT_SUCCESS);
    }
    else
    {
        perror("fork error");
        return -1;
    }
}