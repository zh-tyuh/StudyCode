#include<iostream>
using namespace std;

union Info
{
    int num; //四字节整数
    char ch; //一字节
};

int main()
{
    //使用共用体来判断本机是大端还是小端存储
    union Info temp;
    temp.num = 0x12345678;

    if(temp.ch==0x12)
    {//内存地址低位存储数据高位
        cout<<"big endian"<<endl;
    }
    else if(temp.ch==0x78)
    {//内存地址低位存储数据低位
        cout<<"little endian"<<endl;
    }
    else
    {
        cout<<"error"<<endl;
        return 0;
    }
    cout<<"Hello,World"<<endl;
    return 0;
}