#include"sem.h"
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<errno.h>
union semun 
    {
        int val; // 设置信号量的值
        struct semid_ds *buf; // 关于信号量集属性的操作
        unsigned short *array; // 对于信号量集中所有信号量的操作
        struct seminfo *__buf; /* Buffer for IPC_INFO (Linux-specific) */
    };

void init_sem(int semid,int semno)
{
    //用户手动输入信号量
    int val=-1;
    printf("请输入第%d个信号灯的信号量：",semno+1);
    scanf("%d",&val);
    getchar();

    //执行有关信号量集的控制函数，完成初始化操作
    union semun us;
    us.val=val;
    if(semctl(semid,semno,SETVAL,us)==-1)
    {
        perror("semctl error");
        return;
    }
}

//创建信号量集并进行初始化：semcouunt表示要创建的信号量集中信号灯的个数，
int create_sem(int semcount)
{
    //1、创建key值
    key_t key=ftok("/",'k');
    if(key==-1)
    {
        perror("ftok error");
        return -1;
    }

    //2、创建信号量集
    int semid = -1;
    if((semid = semget(key,semcount,IPC_CREAT|0664|IPC_EXCL))==-1)
    {
        //如果错误码为EEXIST，表示已经存在信号量集，则不需要进行初始化，直接打开信号量集中断退出函数即可
        if(errno==EEXIST)
        {
            semid = semget(key,semcount,IPC_CREAT|0664);
            return semid;
        }
        perror("semget error");
        return -1;
    }

    //3、初始化信号量集
    //如果某个进程想要打开已经存在的信号量集，就不需要再对信号量集进行初始化，可以在打开后直接中断
    for(int i=0;i<semcount;i++)
    {
        //循环初始化信号量集中的信号量
        init_sem(semid,i);
    }
    return semid;
}

//申请资源操作，semno表示要申请资源的信号量编号
int P(int semid,int semno)
{
    //定义sembuf结构体，设置要操作的信号量、要进行的操作和操作标识符
    struct sembuf buf;
    buf.sem_flg = 0; //表示阻塞方式
    buf.sem_op = -1;  //小于0表示申请资源
    buf.sem_num = semno;  //表示要操作的信号量
    
    semop(semid,&buf,1);
    return 0;
}

//释放操作，semno表示要释放资源的信号量编号
int V(int semid,int semno)
{
    //定义sembuf结构体，设置要操作的信号量、要进行的操作和操作标识符
    struct sembuf buf;
    buf.sem_flg = 0; //表示阻塞方式
    buf.sem_op = 1;  //大于0表示释放资源
    buf.sem_num = semno;  //表示要操作的信号量
    
    semop(semid,&buf,1);
    return 0;
}


//删除信号量集
int delete_sem(int semid)
{
    if(semctl(semid,0,IPC_RMID)==-1)
    {
        perror("semctl error");
        return -1;
    }
    return 0;
}