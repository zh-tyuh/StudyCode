//使用fgets和fputs完成两个文件的拷贝 srcfile destfile
#include<string.h>
#include<stdio.h>

int main(int argc,const char* argv[])
{
    FILE* srcfp;
    FILE* destfp;
    if((srcfp=fopen("./srcfile.txt","r"))==NULL || (destfp=fopen("./destfile.txt","w"))==NULL)
    {
        perror("fopen error");
        return -1;
    }

    //从srcfile中读取字符写入destfile中
    char buf[128]="";
    while(1)
    {
        char* ptr=fgets(buf,sizeof(buf),srcfp);
        if(ptr==NULL)
        {
            break;
        }
        fputs(buf,destfp);
    }
    fclose(srcfp);
    fclose(destfp);

    return 0;
}