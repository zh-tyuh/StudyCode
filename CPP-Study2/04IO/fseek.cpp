#include<iostream>
#include<stdio.h>


class stu{
public:
    char name[20];
    int age;
    double socre;
};

int main()
{
    FILE* fd;
    fd = fopen("./fwriteread.txt","w");
    if(fd==NULL)
    {   
        perror("fopen error");
        return -1;
    }

    //利用fwrite向文件中写入结构体
    stu Stu[3]={{"莫内西",18,90.6},\
                {"尼克",29,95.2},\
                {"可优素可",17,98}};
    fwrite(Stu,sizeof(stu),3,fd);

    //关闭文件
    fclose(fd);

    fd = fopen("./fwriteread.txt","r");
    if(fd==NULL)
    {   
        perror("fopen error");
        return -1;
    }

    //用read的形式在控制台模块化输出结构体
    stu stu1;
    fseek(fd,0,SEEK_SET);
    long temp = ftell(fd);
    printf("ftell = %d\n" ,temp);

    fseek(fd,sizeof(stu)*2,SEEK_CUR);
    fread(&stu1,sizeof(stu),1,fd);
    printf("name = %s , age = %d , socer = %lf\n ",stu1.name,stu1.age,stu1.socre);


    fclose(fd);
    return 0;
}