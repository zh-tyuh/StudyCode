#include<stdio.h>
#include<stdlib.h>
int n,m;//要存n个点，其中n>100，m条边
int ind[105]={0};//用来存某个点的入度
//======图的存储，采用邻接表存图=======
typedef struct GNode//图的结点
{
    char data;
    struct Node* first;//指向临界表
}GNode;
GNode g[105];

typedef struct Node//邻接表结点 存储出边邻接点
{
    int val;//存储该点的下标
    struct Node* next;
}Node;

//根据数据查找下标
int Find(char x)
{
    for(int i=0;i<n;i++)
    {
        if(g[i].data==x)
        {
            return i;
        }
    }

}




//=======================链栈相关代码==========================
//节点类型
typedef struct SNode
{
    int index;
    struct SNode*next;
}SNode;
//链栈初始化
SNode* Init()
{
    SNode* s=NULL;
    return s;
}
//链栈的添加操作
SNode* Push(SNode* s,int x)//传入栈的头指针
{
    SNode* new =(SNode*)malloc(sizeof(SNode));
    new->index=x;
    new->next=s;
    s=new;
    return s;
}
//链栈的删除操作
SNode* Pop(SNode* s,int *val)
{
    //判空
    if(s==NULL)
    {
        return NULL;
    }
    SNode* t=s;
    *val=t->index;
    s=s->next;
    free(t);
    t=NULL;
    return s;
}

//===========topo排序==================
 char to[105]; //临时存储topo序列
void topo()
{   
    SNode* s=Init();
    for(int i=0;i<n;i++)
    {
        if(ind[i]==0)
        {
            s=Push(s,i);//将入度为0的结点的下标入栈
        }
    }
    for(int i=0;i<n;i++)
    {
        int temp=-1;
        Pop(s,&temp);  //将栈中的元素进行出栈，并返回出栈结点的下标
        to[i]=g[i].data;  //将出栈元素加入topo序列
        Node* n1=g[temp].first; //指向出栈元素的邻接表
        while(n1!=NULL)
        {
            ind[n1->val]--;//将出栈元素的出边邻接点的入度-1
            if(ind[n1->val]==0) Push(s,n1->val);
            n1=n1->next;
        }
        
    }
}


int main()
{
    scanf("%d %d",&n,&m);
    
    //输入点
    char c;
    for(int i=0;i<n;i++)
    {
        scanf("%c ",&c);
        g[i].data=c;
        g[i].first=NULL;
    }
    //输入边
    char x,y;
    int fx,fy;//记录x和y的下标
    for(int i=0;i<m;i++)
    {
        scanf("%c %c ",&x,&y);//y是x的邻接点
        fx=Find(x);
        fy=Find(y);
        Node* n=(Node*)malloc(sizeof(Node));
        n->val=fy;
        n->next=g[fx].first;
        g[fx].first=n;
        ind[fy]++;//y的入度+1
    }

    
    //进行topo排序
    topo();
    //输出结果
    for(int i=0;i<n;i++)
    {   
        printf("%c ",to[i]);
    }
}

/*
6 8
ABCDEF
A B
A C
A D
C B
C E
F D
F E
D E
*/ 