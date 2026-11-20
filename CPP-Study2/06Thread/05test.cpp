#include<iostream>
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
//11、创建无名信号量
sem_t sem1,sem2,sem3;

void* taskA(void* arg)
{
    while(1)
    {
        sem_wait(&sem3);
        sleep(1);
        printf("A");
        fflush(stdout);
        //taskA执行完之后，释放信号灯资源
        sem_post(&sem1);
    }
}
void* taskB(void* arg)
{
    while(1)
    {
        //申请信号灯资源
        sem_wait(&sem1);
        sleep(2);
        printf("B");
        fflush(stdout);
        //taskB执行完之后，释放信号灯资源
        sem_post(&sem2); 
    }

}
void* taskC(void* arg)
{
    while(1)
    {
        //申请信号灯资源
        sem_wait(&sem2);
        sleep(3);
        printf("C");
        fflush(stdout);
        //taskC执行完之后，释放taskA信号灯资源
        sem_post(&sem3);
    }

}

int main()
{
//使用无名信号量完成，定义三个任务，任务1打印A，任务2打印B，任务3打印C，最终输出的结果为ABCABCABCABC...

    //22、完成无名信号量的初始化
    sem_init(&sem1,0,0);
    sem_init(&sem2,0,0);
    sem_init(&sem3,0,1);

    //1、创建三个线程
    pthread_t pidA,pidB,pidC;
    pthread_create(&pidA,NULL,taskA,NULL);
    pthread_create(&pidB,NULL,taskB,NULL);
    pthread_create(&pidC,NULL,taskC,NULL);
    printf("pidA = %#x , pidB = %#x , pidC = %#x \n",pidA,pidB,pidC);
    //2、阻塞执行支线程并回收资源
    pthread_join(pidA,NULL);
    pthread_join(pidB,NULL);
    pthread_join(pidC,NULL);
    
    //销毁信号量
    sem_destroy(&sem1);
    sem_destroy(&sem2);
    sem_destroy(&sem3);
    printf("执行结束\n");
}











