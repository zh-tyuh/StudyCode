#include<stdio.h>
#include<string.h>
#include<iostream>

int main(int argc,const char* argv[])
{
    FILE* fp;
    if((fp = fopen("./fputgets.txt","w")) == NULL)
    {
        perror("fopen error");
        return -1;
    }

    //向文件中写入多个字符
    char wbuf[128]="";
    while(1)
    {
        std::cin >> wbuf;
        fputs(wbuf,fp);
        fputs("\n",fp);

        if(strcmp(wbuf,"quit") == 0)
        {
            break;
        }
    }
    fclose(fp);

    //打开文件读取字符串
    if((fp = fopen("./fputgets.txt","r")) == NULL)
    {
        perror("fopen error");
        return -1;
    }
    char rbuf[128]="";
    while(1)
    {
        char*res = fgets(rbuf,sizeof(rbuf),fp);
        if(res == NULL)
        {
            break;
        }
        printf("rbuf = %s" , rbuf );
    }
    fclose(fp);
}