#include"http.h"

int init_server(int _port)
{
    //创建服务端套接字
    int sock = socket(AF_INET,SOCK_STREAM,0);
    //参数1 协议族 AF_INET表示IPV4通信方式  参数2 通信类型 SOCK_STREAM 支持TCP面向连接的通信协议 参数3 当2中明确指出通信类型可以填0
    if(sock==-1)
    {
        perror("socket error");
        return -1;
    }

    //将端口设置为可快速重用
    int reuse=1;
    if(setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse))==-1)
    {
        perror("setsockopt error");
        return -1;
    }

    //为服务端绑定端口
    sockaddr_in local;
    local.sin_family=AF_INET;
    local.sin_port=htons(_port);
    local.sin_addr.s_addr=INADDR_ANY; //不绑定固定IP，本机上所有网卡的IP都可以使用

    if(bind(sock,(sockaddr*)&local,sizeof(local))==-1)
    {
        perror("bind error");
        return -1;
    }

    //开启监听
    if(listen(sock,128)==-1)
    {
        perror("listen error");
        return -1;
    }

    //执行至此，说明服务器初始化创建完成
    return sock;
}


int get_line(int sock,char* buf)
{//自定义从客户端套接字中读取一行信息函数
    char ch = '\0';//读取一个字符
    int i=0;     //填充变量，用于填充buf,所以从0开始
    int ret=0;

    while(i<SIZE && ch!='\n')     //当buf没有满并且没有读取到换行时
    {
        ret = recv(sock,&ch,1,0);   //从缓冲区读取一个字符赋值给ch

        if(ret>0&&ch=='\r')
        {//读取成功且ch=='\r'表示下一个字符可能是'\n'
            int s = recv(sock,&ch,1,MSG_PEEK);    //将下一个字符拿出来开看看，但不获取出来
            if(s>0 && ch=='\n')
            {//将回车从缓存区读取出来
                recv(sock,&ch,1,0);   //这里必须重新从缓存区获取一下'\n'因为上一个recv只是拿出来看看，缓存区中的'\n'并没有受到影响
            }
            else
            {//直接放入回车结束
                ch='\n';   //
            }
        }

        //将符合条件的字符放入字符串中
        buf[i]=ch;
        i++; 
    }
    buf[i]='\0';
    return i; 
}


//清除上一次获取的请求的后续内容
static void clear_header(int sock)
{
    
    char buf[4096]="";
    int ret = 0;  //获取的行数的字符数
    do
    {   
        ret = get_line(sock,buf);  //也可以用recv直接把缓存区中的内容全部清除，但是为了避免将下一次请求的信息也清除掉，所以一行一行读取，直到读取到当前请求的末尾
    } while (ret!=1 && strcmp(buf,"\n")!=0);
    //当获取的行数的字符数为1或buf中只存在"\n"时，说明已经读取到该请求的末尾
}   

static void show_404(int _sock)
{
    //将获取的请求消息头部全部清除掉
    //为什么要进行这一步？因为在上面获取请求方法，URL的过程中，只获取了请求的第一行，其他Agent什么的还在缓存区中
    //因此要将缓存区中的信息全部清除点才行
    clear_header(_sock);


    //1、向客户端发出错误回应
    //1.1 组装响应头部信息
    const char *msg = "HTTP/1.1 404 NOT FOUND \r\n";
    /*
        这里我复习一下关于字符串的东西吧
        在没有string 的情况下  字符串的本质就是字符数组
        字符串一共有两种定义方式
        1、字符串数组  char arr[10]="hello world";
            注意1 如果要写数组长度，一定要预留出'\0'的位置
            注意2 字符数组的方式定义字符串，内容是可以改变的
        2、指针 const char* str ="hello world"
            细节1 在底层，系统还是会把引号中内容转化为字符数组的形式，并在末尾加上'\0'
            细节2 利用这种方式进行定义，会把底层的字符数组放在只读常量区，其内容不可修改，但是可以复用
        
        只读常量区可以复用是什么意思呢？
        比方说如果有一个字符串 const char* str1="abcd"；在只读常量区
        那么再定义一个字符串 char *str2="abcd" 会先检查只读常量区中有没有abcd，如果没有在创建新的，如果有就直接进行复用
    */
    //1.2 发送响应信息
    send(_sock,msg,strlen(msg),0);
    send(_sock,"\r\n",strlen("\r\n"),0);   //注意不要忘记发送一个空行



    //2、向客户端展示错误页面
    //2.1 不用判断文件 是否存在直接打开文件
    struct stat st;
    stat("./wwwroot/404.html",&st); //获取该路径下的文件信息，主要是获取文件大小
    int fd=open("./wwwroot/404.html",O_RDONLY);
    if(fd==-1)
    {
        perror("open 404 error");
        return;
    }

    //2.2 将整个文件发送出去
    //函数原型：ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count);
    sendfile(_sock,fd,NULL,st.st_size);
    close(fd);
}

static void show_405(int sock)
{
    //1.回复异常码
    const char* msg = "HTTP/1.1 405 Method Not Allowed\r\n";
    send(sock,msg,strlen(msg),0);
    send(sock,"\r\n",strlen("\r\n"),0);

    //2、将html文件发送过去
    struct stat st;
    stat("./wwwroot/405.html",&st);
    int fd = open("./wwwroot/405.html",O_RDONLY);
    if(fd == -1)
    {
        perror("open 405 error");
        return;

    }
    sendfile(sock,fd,NULL,st.st_size);
    close(fd);
}



//处理错误信息
void echo_error(int _sock,int error_code)
{
    //根据错误码判断是出现了那种错误
    switch(error_code)
    {
        case 404:
            show_404(_sock);
            break;
        case 405:
            show_405(_sock);
            break;
        default:
            break;
    }
}


//返还PATH路径下的页面
static int echo_www(int _sock,const char* path,int s)
{
    clear_header(_sock);

    //1.返回响应码
    const char* msg = "HTTP/1.1 200 OK\r\n";
    send(_sock,msg,strlen(msg),0);
    send(_sock,"\r\n",strlen("\r\n"),0);

    //2.将文件发送给客户端
    //2.1 打开文件
    int fd = open(path,O_RDONLY);
    if(fd==-1)
    {
        perror("open error");
        return -1;
    }
    if(sendfile(_sock,fd,NULL,s)==-1)
    {
        echo_error(_sock,500);//返还错误界面
        return -1;
    }
    close(fd);
    return 0;
}


int hander_msg(int _sock)
{//信息处理函数

    //接收客户端发来的信息
    char del_buf[SIZE]="";
    recv(_sock,del_buf,sizeof(del_buf),MSG_PEEK);
    //参数MSG表示只查看套接字中的数据，并不读走

    #if 1
    //先读取一遍recv的数据
    printf("=======================================\n");
    printf("%s\n",del_buf);
    printf("=======================================\n");
    #endif



    //接下来就是解析HTTP请求

    char buf[SIZE]="";
    int count = get_line(_sock,buf);
    //printf("%s",buf);
    //自定义函数：功能获取recv的请求的一行数据
    //参数：通信套接字，获取的数据
    //返回值：当前行字符串长度


    //程序执行至此，表示已经获得了请求行的信息
    //之后要从该请求行中获取请求方法,URL
    char method[32]="";
    int k=0;//填充请求方法

    int i=0;//i要写在外面，因为后续要获取URL，方便可以直接从i位置开始继续获取
    for(i;i<count;i++)
    {
        //找到任意字符
        if(isspace(buf[i]))
        {//当读取到空格的时候，退出循环
            break;
        }
        method[k]=buf[i];
        k++;
    }
    method[k++]='\0'; //将字符串补充完整
    //程序执行至此，表示method已经获取了请求方法
    //判断请求方法是不是GET或者POST请求
    if(strcasecmp(method,"GET")!=0 && strcasecmp(method,"POST")!=0)
    {
        printf("METHOD ERROR\n");

        //向客户端回复一个错误界面
        echo_error(_sock,405);
    
        //关闭套接字并退出
        close(_sock);
        return -1;
    }
    //将空格跳过
    while(isspace(buf[i])&&i<SIZE)
    {
        i++;
    }

    //下面获取URL和需要处理的数据，例如获取/index.html?ttl=240
    char url[SIZE]=" ";
    int t=0;  //填充url的变量 
    char *querry_string=NULL; //用于区分URL和需要处理的数据，如果有需要处理的数据，指向其首地址

    for(i;i<count;i++)
    {
        if(isspace(buf[i])) //遇到空格则URL读取结束
        {
            break;  
        }

        //找到任意字符
        if(buf[i]=='?')
        {//当读取到?说明遇到了URL和需要处理的数据的分隔符，此时将定义的指针指向待处理数据的首地址
            url[t]='\0';    //添加结束符，表示URL字符存储完毕
            querry_string=&url[t];
            querry_string++;
        }
        else
        {//正常存储数据
            url[t]=buf[i];
        }
        t++;
    }
    url[t]='\0';


    //测试
    printf("method = %s\n",method);
    printf("url = %s\n",url);
    printf("querry_string = %s\n",querry_string);


    //获取到请求方法、URL和需要处理的数据之后就需要  判断需不需要手动处理界面
    //如果是Get方法且无需要处理的数据就不需要手动处理界面，只需要将需要的信息进行返回
    //如果是POST方法或者GET方法且有需要处理的数据，则需要对数据进行处理之后再将需要的信息返回
    int need_hander = 0;
    if(strcasecmp(method,"POST")==0 || (strcasecmp(method,"GET")==0 && querry_string!=NULL))
    {
        need_hander = 1;
    }
    else
    {
        need_hander = 0;
    }


    //我们可以把请求资源的路径固定为 wwwroot 下的资源
    char path[SIZE]="";   //用于确定要相应的文件路径
    sprintf(path,"./wwwroot%s",url); //将"../wwwroot"和url拼接并打印在path中
   

    //如果客户端没有输入对应的文件路径，即url="\"，默认打开index.html文件
    if(strcasecmp(url,"/")==0)
    {
        strcat(path,"index.html");
    }
    printf("path = %s\n",path);
    

    //还需要判断当前服务器是否存在该路径
    struct stat st;
    if(stat(path,&st)==-1)
    {
        //说明要访问的页面不存在
        printf("PATH NOT FOUND\n");
        //如果页面不存在则需要向客户端发送404页面
        echo_error(_sock,404);
        close(_sock);
        return -1;
    }

    printf("need_hander==%d\n",need_hander);
    //执行至此，说明处理方法是正确的且URL对应的路径存在，需要判断是否需要进行特殊处理
    if(need_hander==0)
    {//不需要进行特殊处理
        //此时表示的是GET请求，并且没有附加数据，只需要返回请求的界面即可
        echo_www(_sock,path,st.st_size);
    }
    else
    {//需要进行特殊处理
        //hander_request(sock,path,method,querry_string);
        //自定义函数：功能对请求进行处理
        //参数
    }




    


}


