#include"swap.h"

MySwap::MySwap(int a,int b)
{
    m_a=a;
    m_b=b;
}
void MySwap::run()
{
    int temp=m_a;
    m_a=m_b;
    m_b=temp;
}
void MySwap::printInfo()
{
    cout << "a = "<< m_a << endl;
    cout << "b = "<< m_b << endl;
}