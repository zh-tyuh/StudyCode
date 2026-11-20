#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
void* func(void* argv)
{
    //子线程线程体
    for(int i=0;i<=10;i++)
    {
        sleep(1);
        printf("我是子线程,pid = %#x\n",pthread_self());
    }
    //退出子线程
    pthread_exit(NULL);
    
}

int main()
{
    //创建一个线程
    pthread_t pid = -1;
    if(pthread_create(&pid,NULL,&func,NULL)!=0)
    {//成功返回0，失败返回一个错误吗
        printf("pthread_create error\n");
        return -1;
    }

    //阻塞回收子线程资源
    //pthread_join(pid,NULL);

    //以非阻塞的方式回收子线程资源，即将子线程设为分离态
    pthread_detach(pid);


    for(int i=0;i<=10;i++)
    {
        sleep(1);
        printf("我是父线程，子线程pid = %#x\n",pid);
    }



}