#include<stdio.h>
#include<stdlib.h>
#define maxx 100

//建立一个孩子链表的结点类型
typedef struct Node{
    int son;//存放该节点孩子结点的下标
    struct Node* next;
}*SonNode,sonNode;

//建立一个结构体数组，存储该节点的数据和孩子链表的指针
struct tree1{
char data;  //存储该节点的数据
SonNode firstSon;//存储第一个孩子的地址
};

struct tree1 tree[maxx];//创建一个数组
int len;//记录当前数组的长度

//1、数组的初始化
void Init(char root){
tree[len].data=root;
tree[len].firstSon=NULL;
len++;
}

//3、根据元素查找下标
int Find(char x){
for(int i=0;i<len;i++){
    if(tree[i].data==x){
        return i;
    }
}
printf("该数据没有查到");
return -1;
}

//2、数组的插入
void Insert(char x,char fx){
//1）将x的数据插入数组
tree[len].data=x; 
tree[len].firstSon=NULL;
//2）查找x的父亲节点位置，将x结点插入fx孩子链表中
int i=Find(fx); //查找fx的下标
SonNode s=(SonNode)malloc(sizeof(struct Node));//开辟一个新结点,利用x的用结点的方式插入再fx的孩子链表中
//头插法
s->son=len;
s->next=tree[i].firstSon;
tree[i].firstSon=s;
//3）
len++;
}


int main(){
    //1、初始化数组
    int n;
    scanf("%d",&n);
    char root;
    scanf(" %c",&root);//用占位符过滤掉空白字符（回车换行 空格等）
    Init(root);
    
    //2、输入字符和该字符的双亲结点
      char x,fx;
    for(int i=0;i<n-1;i++){
      
        scanf(" %c %c",&x,&fx);
        Insert(x,fx);
    }
    
    
    //3、查找某节点的孩子节点
    char x1;
    scanf(" %c",&x1);
    int index=Find(x1);

    printf("this Node's SonNode is fallowing:");
    SonNode p;
    p=tree[index].firstSon;
    if(p==NULL) printf("thisNode is leaveNode");  //是叶子结点
    else{
    while(p!=NULL){
        printf("%c ",tree[p->son].data);
        p=p->next;
    }
}

printf("\n");
    //4、查找某节点的父亲节点
    //查找某节点的父亲节点，需要遍历所有的数据的孩子节点，看看有哪些结点的孩子节点有x
    int is_Find = 0 ;
    p=tree[0].firstSon;
    printf("this Node's FatherNode is fallowing:");
    for(int i=0;i<len;i++){
        while(p!=NULL){
            if(p->son==index){
                printf("%c \n",tree[i].data);
                is_Find++;
                break;
            }
            p=p->next;
        }
    if(is_Find==1) break;
    }    
    if(is_Find==0) printf("is rootNode\n");


}







/*输入
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