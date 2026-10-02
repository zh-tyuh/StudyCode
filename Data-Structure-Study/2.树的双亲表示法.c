#include<stdio.h>
#include<stdlib.h>
//定义一个节点类型
#define maxx 100
typedef struct Node{
char data; //存储结点数据
int f;     //存储其父亲结点的下标
} Node;
Node T[maxx];   //建立一个节点类型的数组，用来存储所有节点
int len;        //记录结点的实际个数，全局变量默认为0

//1、树的初始化   传入根结点
void Init(char root){ 
    T[0].data=root;
    T[0].f=-1;
    len++;
}

int Find(char x);

//2、树结点的插入    传入待插入的结点的数据和其父节点对应的数据
void Insert(char x,char fx){
    //判断树满
     if(len-1==maxx){
        printf("树满了");
        return ;
     }
     //将新结点的数据和其父亲节点对应的下标存储进入树数组
    T[len].data=x;
    T[len].f=Find(fx);
    len++;
}

//3、树结点的查找   根据结点的数据找出对应的下标
int Find(char x){
    int i;
    for(i=0;i<len;i++){
        if(x==T[i].data){
          return i;
        }
    }
    return -1;
}


int main(){
    //第一步 先输入树结构数组的0索引数据和根结点（初始化）
    int n;      //总共要插入的结点个数
    char r;     //根节点数据
    char x,fx;  //x表示某节点的数据，fx表示该结点的父节点的数据
    scanf("%d",&n);  
    getchar();  //吞掉输入n之后的回车
    scanf("%c",&r);
    Init(r);

    //第二步 按顺序将数据一次存到树数组当中
    for(int i=2;i<=n;i++){
        getchar();
        scanf("%c %c",&x,&fx);
        Insert(x,fx);   //将数据插入数组当中
    }
    printf("数据输入成功\n");
    //------------------------------------------------------------------------
   

    //基本操作1 查找某数据的父亲是谁 时间复杂度为n
    getchar();
    scanf("%c",&x);
    int i=Find(x); 
    if(i==-1) printf("x为根节点");
    else if(T[i].data==x){
        printf("%c的父亲是%c\n",x,T[T[i].f]);
    }

    //基本操作2 查找某数据的孩子有谁 时间复杂度为
    getchar();
    scanf("%c",&x);
    for(int i=0;i<len;i++){
        if(T[i].f==Find(x)){
            printf("%c的孩子有%c\n",x,T[i].data);
        }
    }
    

}




/*
13
A 
B A
C A
D A
E B
F B
G C
H D
I D
J D
K E
L E
M H
*/