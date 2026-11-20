#include<iostream>
#include<thread>
#include<condition_variable>
#include<unistd.h>
#include<mutex>
#include<chrono>
using namespace std;
condition_variable cond;
mutex mux;



void task1(int num)
{//生产者
    while(num--)
    {
        sleep(2);
        cout<<"我生产了一辆特斯拉，大家快来购买!!"<<endl;
        cond.notify_one();
    }

}

void task2()
{//消费者
    //进入休眠队列，等待生产者唤醒
    unique_lock<mutex> lock(mux);
    cond.wait(lock); 

    //被消费者唤醒 执行临界区代码
    cout<<"我的pid是"<<this_thread::get_id()<<"  我购买了一辆特斯拉"<<endl;

    lock.unlock();
}

int main()
{
    int num = 3 ;
    thread product(task1,num);
    
    for(int i=0;i<num;i++)
    {//创建num个消费者线程
        thread consume(task2);
        consume.detach();
    }

    product.join();

    return 0;
}