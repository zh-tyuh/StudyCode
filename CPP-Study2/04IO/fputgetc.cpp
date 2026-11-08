#include<stdio.h>


int main(int argc,const char* argv[])
{
    FILE* fp;
    if((fp=fopen("./test","w"))==NULL)
    {
        perror("fopen error");
        return -1;
    }

    //利用fputc向文件中写入字符
    fputc('D',fp);
    fputc('O',fp);
    fputc('N',fp);
    fputc('K',fp);
    fclose(fp);

    if((fp=fopen("./test","r"))==NULL)
    {
        perror("fopen error");
        return -1;
    }
    
    char ch=0;
    while(1)
    {
        ch=fgetc(fp);
        if(ch==EOF)
        {
            break;
        }
        printf("%c ",ch);
    }
    printf("\n");
    fclose(fp);
    return 0;
}