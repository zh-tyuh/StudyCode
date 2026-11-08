#include<stdio.h>
#include<iostream>
using namespace std;

int main()
{
    //向标准输出文件中写入数据
    fprintf(stdout,"%d %lf %s\n",100,1.25,"Fuck");

    //从标准输入中读取数据到程序中来
    int num = 0;
    fscanf(stdin,"%d",&num);
    printf("num = %d\n", num );

    //向文件中写入数据
    FILE* fp = NULL;
    if((fp = fopen("./fprintf.txt","w"))== NULL)
    {
        perror("fopen error");
        return -1;
    }

    fprintf(fp,"%d %s %d %lf\n",1,"m0NESY",18,1.83);
    fclose(fp);

    //从文件中读取数据
    if((fp = fopen("./fprintf.txt","r"))== NULL)
    {
        perror("fopen error");
        return -1;
    }

    int id=0,age=0;
    char name[128]="";
    double length=0;
    fscanf(fp,"%d %s %d %lf\n",&id,name,&age,&length);
    printf("id = %d , name = %s , age = %d , length = %lf\n",id,name,age,length);
    fclose(fp);
    return 0;
}