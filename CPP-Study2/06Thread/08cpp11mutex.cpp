#include<iostream>
#include<mutex>
#include<unistd.h>
#include<thread>
using namespace std;
//创建一个互斥锁
mutex mux;

int num = 520;
void task1()
{
    while(1)
    {
        sleep(2);
        mux.lock();
        num-=20;
        cout<<"灭霸从num中取走了20 num = "<<num<<endl;
        mux.unlock();
    }
}
void task2()
{
    while(1)
    {
        sleep(1);
        mux.lock();
        num-=10;
        cout<<"小浣熊从num中取走了10 num = "<<num<<endl;
        mux.unlock();
    }
}

int main()
{
    thread t1(task1);
    thread t2(task2);

    t1.join();
    t2.join();
}