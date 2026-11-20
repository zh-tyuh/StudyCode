#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

//定义一个全局资源，临界资源
int num = 520;
//11、创建一个互斥锁
pthread_mutex_t mutex;

void* task1(void* arg)
{//线程1的线程体
    while(1)
    {//灭霸从num中取走20

        sleep(2); 
        //sleep不能写在临界区中。因为如果该进程获取得到锁资源此时其他资源处于休眠期中
        //如果sleep函数在临界区中的话，当该进程释放锁资源的时候，他会以苏醒状态跟其他休眠状态的进程抢占锁资源
        //该线程的执行速度很快，很快就能抢到新的锁资源

        //44、获取锁资源，当该进程获取到锁资源，其他进程就不能动用临界区中的资源
        pthread_mutex_lock(&mutex);
        num-=20;
        
        printf("灭霸从num中取走了20,num还剩%d\n",num);
        //55、释放锁资源，释放锁资源之后，所有进程才会继续抢占锁资源
        pthread_mutex_unlock(&mutex);
    }
}

void* task2(void* arg)
{//线程2的线程体  
    while(1)
    {//小浣熊从num中取走10
        sleep(2);
        
        //44、获取锁资源
        pthread_mutex_lock(&mutex);
        num-=10;
        printf("小浣熊从num中取走了10,num还剩%d\n",num);
        //55、释放锁资源
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    //线程的互斥机制之互斥锁
    //22、初始化互斥锁，一般在线程创建之前完成互斥锁的初始化
    if(pthread_mutex_init(&mutex,NULL)!=0)
    {
        printf("pthread_mutex_init error\n");
        return -1;
    }
    
    //1、创建两个线程
    pthread_t pid1 , pid2;
    pthread_create(&pid1,NULL,task1,NULL);
    pthread_create(&pid2,NULL,task2,NULL);



    //2、阻塞执行分支线程并回收资源
    pthread_join(pid1,NULL);
    pthread_join(pid2,NULL);

    //66、删除锁子原
    pthread_mutex_destroy(&mutex);
}