#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

//11、创建无名信号量
sem_t sem;


void* task1(void* arg)
{
    int num=5;
    while(num--)
    {
        sleep(1);
        printf("我生产了一辆特斯拉，大家快来购买啊\n");
        //33、生产一辆之后释放一次无名信号量资源
        sem_post(&sem);
    }

    //退出线程
    pthread_exit(NULL);
}

void* task2(void* arg)
{
    int num=5;
    while(num--)
    {
        //44、申请无名信号量的资源
        sem_wait(&sem);
        printf("我购买了一辆特斯拉，好开心！\n");
    }
    pthread_exit(NULL);
}


//线程同步机制之无名信号量
//线程同步就是多个线程之间有先后顺序，比如在消费者和生产者之间的关系，每当消费者生产出一辆车，消费者才可以进行消费
int main()
{
    //22、初始化无名信号量
    sem_init(&sem,0,0);

    //1、创建两个线程，一个代表消费者，一个表示生产者
    pthread_t prds , cnsm;
    pthread_create(&prds,NULL,task1,NULL);
    pthread_create(&cnsm,NULL,task2,NULL);
    printf("prds = %#x , cnsm = %#x\n",prds,cnsm);


    //2、阻塞等待分支线程执行结束并回收资源
    pthread_join(prds,NULL);
    pthread_join(cnsm,NULL);

    //55、销毁无名信号量
    sem_destroy(&sem);

    printf("执行结束\n");
}

