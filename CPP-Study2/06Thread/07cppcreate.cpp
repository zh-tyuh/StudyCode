#include<iostream>
#include<chrono>
#include<thread>
#include<string>
using namespace std;

//无参数无返回值线程体
void task1()
{
    cout << "我是线程t1 我的tid = " << this_thread::get_id() << endl;
}
//有参数无返回值线程体
void task2(int age ,string name)
{
    cout << "我是线程t2 我的tid = " << this_thread::get_id() << endl;
    cout << "age = " << age << " name = " << name << endl; 
}
//类中的成员函数作为线程体函数
class player
{
public:
    void showInfo(){
        cout<< "我是线程t3 我的tid = " <<this_thread::get_id() << endl;
        cout << "name = " << this->name << " team = " << this->team <<endl;
    }
    string name;
    string team;
};




int main()
{
    //1、创建分支线程
    thread t1(task1);
    string name = "m0NESY";
    thread t2(task2,18,name);

    player p1;
    p1.name="donk";
    p1.team="spirit";
    thread t3(&player::showInfo,&p1);

    //lambda表达式作为线程体函数
    int num = 4;
    int age = 3;
    thread t4([num](int age){
        cout<<"第"<<num<<"个线程体t4,我的pid为"<<this_thread::get_id()<<endl;
        cout<<"我的参数是"<<age<<endl;
    },age);

    //2、阻塞执行分支线程
    t1.join();
    t2.join();
    t3.join();
    t4.join();


    cout<<"我是主线程"<<endl;
}
