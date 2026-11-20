#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
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
    //1.创建key值
    key_t key=-1;
    if((key = ftok("/",'k'))==-1)
    {
        perror("ftok error");
        return -1;
    }
    printf("key = %#x\n",key);
    
    //2.通过key值创建消息队列
    int msgid = -1;
    if((msgid = msgget(key,IPC_CREAT|0664))==-1)
    {
        perror("msgget error");
        return -1;
    }
    printf("msgid = %d\n",msgid);


    //3、向消息队列中存放数据
    //定义一个结构体存储消息
    struct msgBuf tmsg;
    while(1)
    {
        printf("请输入消息类型：");
        scanf("%d",&tmsg.mtype);
        getchar();//吞掉换行字符，要不然换行字符始终在stdin缓存区中，就被加入到tmsg.text里面了
        
        printf("请输入消息内容：");
        fgets(tmsg.mtext,MSGSZ,stdin);
        tmsg.mtext[strlen(tmsg.mtext)-1]='\0';
        printf("消息为%s\n",tmsg.mtext);
        //将消息放进消息队列
        if(msgsnd(msgid,&tmsg,strlen(tmsg.mtext)+1,0)==-1)
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