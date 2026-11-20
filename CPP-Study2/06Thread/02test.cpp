#include<stdio.h>
#include<pthread.h>
struct file{
    FILE* scv ;
    FILE* obj ;
};


//支线程：将源文件内容拷贝到目标文件
void* cp1(void* argv)
{
    //接收参数并将参数转化为正常file格式
    struct file f =* (struct file*)argv; 

    //将源文件拷贝到目标文件
    char buf[1024]="";
    while(1)
    {
        //从源文件中获取字符到buf容器，遇到换行自动结束一次读取，并将回车放在容器中并加入'\0'
        char * ptr = fgets(buf,sizeof(buf),f.scv);
        //判断fgets返回值是否为NULL,如果是NULL，表示读取失败即文件结束
        if(ptr==NULL)
        {
            break;
        }
        //将字符串放到目标文件中
        fputs(buf,f.obj);
    }


    //关闭文件并回收进程资源
    fclose(f.scv);
    fclose(f.obj);
    pthread_exit(NULL);
}




int main()
{
    //使用多线程完成两个文件的拷贝，线程1拷贝前一半内容，线程2拷贝后一半内容，主线程用于回收两个分支线程的资源

    //1、打开两个文件
    FILE* scv = fopen("./scv.txt","r");
    FILE* obj = fopen("./obj.txt","w");
    if(scv == NULL||obj==NULL)
    {
        perror("fopen error");
        return -1;
    }
    //利用结构体，将两个文件作为参数传入线程中
    struct file fi = {scv,obj};

    //2、创建两个线程
    pthread_t former = -1;
    //pthread_t latter = -1;
    pthread_create(&former,NULL,cp1,&fi);
    //pthread_create(&latter,NULL,cp2,&f);

    //3、阻塞等待支线程执行完并回收资源
    pthread_join(former,NULL);
    //pthread_join(latter,NULL);

    printf("文件复制完成\n");
    


}