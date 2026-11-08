//使用fgetc和fputc完成两个文件的拷贝工作，实现指令cp的功能：cp srcfile destfile
#include<stdio.h>

int main(int argc,const char* argv[])//一共传入3个参数，第一个参数是a.out 第二个参数是srcfile.txt 第三个参数是destfile
{   
    //判断参数是否为三个
    if(argc!=3)
    {
        printf("input file error\n");
        printf("usage:./a.out srcfile destfile\n");
        return -1;
    }

    FILE *srcfp;
    FILE *destfp;
    if((srcfp=fopen(argv[1],"r"))==NULL || (destfp=fopen(argv[2],"w"))==NULL)
    {
        perror("fopen error");
        return -1;
    }

    char ch=0;
    while(1)
    {
        ch=fgetc(srcfp);
        if(ch==EOF)
        {
            break;
        }
        fputc(ch,destfp);
    }

    fclose(srcfp);
    fclose(destfp);
    printf("mession sucess\n");
    return 0;
}