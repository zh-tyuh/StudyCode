#include<stdio.h>
#include<stdlib.h>
//带权无向图为例。n个点 m条边  n<100  0<=w<=10000
int n,m;
//图结点，存放数据和邻接点链表的首地址
typedef struct ENode{
    char data;
    struct Node* first;
}ENode;
ENode e[105];

//邻接点链表结点：存放相邻结点的下标和两节点的权值和下一个邻结点的指针
typedef struct Node{
    int adi;//邻接点的下标
    int w;
    struct Node* next;
}Node;

int Find(int x)
{//查找下标
    for(int i=1;i<=n;i++)
    {
        if(e[i].data==x) return i;
    }
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf(" %c",&e[i].data);
        e[i].first=NULL;
    }
    char x,y;
    int xi,yi,w;
    for(int i=1;i<=m;i++)
    {
        scanf(" %c %c %d",&x,&y,&w);
        //采用头插法将边插入x的邻接点链表中
        xi=Find(x);
        yi=Find(y);

        //在x的邻接点链表中插入y的下标
        Node* s1=(Node*)malloc(sizeof(Node));
        s1->adi=yi;
        s1->w=w;
        s1->next=e[xi].first;
        e[xi].first=s1;
        //在y的邻接点链表中插入x的下标
        Node* s2=(Node*)malloc(sizeof(Node));
        s2->adi=xi;
        s2->w=w;
        s2->next=e[yi].first;
        e[yi].first=s2;
    }

    //查看某结点的度
    char p;
    scanf(" %c",&p);
    int pi=Find(p),pd=0;
    Node*q=e[pi].first;
    while(q!=NULL)
    {
        pd++;
        q=q->next;
    }
    printf("%c'S DU IS %d\n",p,pd);
}
/*
4 5
ABCD
A B 3
A D 6
A C 0
B D 9
D C 4
*/