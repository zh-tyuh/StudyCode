#include<iostream>
using namespace std;
#ifndef SWAP_H
#define SWAP_H

class MySwap
{
public:
    //构造函数声明
    MySwap(int a, int b);
    
    //执行交换操作
    void run();

    //打印相关信息
    void printInfo();

    //要交换的两个数
    int m_a,m_b;
};


#endif