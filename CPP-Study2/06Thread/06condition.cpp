#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

//11、创建一个条件变量
pthread_cond_t cond;
//111、创建互斥锁
pthread_mutex_t mutex;

void* task1(void* arg)
{//生产者
    /*唤醒队列中的单个消费者
    int num=3;
    while(num--)
    {
        sleep(1);
        printf("我生产了一量特斯拉，大家快来买！！！\n");
        //33、消费者唤醒条件变量中第一个进入队列的消费者线程
        pthread_cond_signal(&cond);
    }*/

    //唤醒队列中的全部消费者
    sleep(1);
    printf("我生产了三辆特斯拉，大家快来买！\n");
    //唤醒条件变量中所有进入队列的消费者
    pthread_cond_broadcast(&cond);
    pthread_exit(NULL);

}
void* task2(void* arg)
{//单个消费者
    //333、获取锁资源
    pthread_mutex_lock(&mutex);
    //33、消费者线程进入等待队列
    pthread_cond_wait(&cond,&mutex);
    sleep(1);
    printf("%#x:我买了一辆特斯拉，好开心:>\n",pthread_self());
    //444、释放锁资源
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL); 
}


int main()
{
    //22、初始化条件变量
    pthread_cond_init(&cond,NULL);
    //222、初始化互斥锁
    pthread_mutex_init(&mutex,NULL);

    //1、创建生产者和多个消费者
    pthread_t produce,cnsm1,cnsm2,cnsm3;
    pthread_create(&produce,NULL,task1,NULL);
    pthread_create(&cnsm1,NULL,task2,NULL);
    pthread_create(&cnsm2,NULL,task2,NULL);
    pthread_create(&cnsm3,NULL,task2,NULL);
    printf("produce = %#x , cnsm1 = %#x ,\ncnsm2 = %#x ,cnsm = %#x\n",produce,cnsm1,cnsm2,cnsm3);


    //2、阻塞等待支线程执行和资源回收
    pthread_join(produce,NULL);
    pthread_join(cnsm1,NULL);
    pthread_join(cnsm2,NULL);
    pthread_join(cnsm3,NULL);

    //3、销毁互斥锁和条件队列
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);

    printf("执行结束\n");
}