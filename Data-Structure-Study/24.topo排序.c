#include<stdio.h>
int n,m;//要存n个点，其中n>100，m条边
//======图的存储，采用邻接表存图=======
typedef struct GNode//图的结点
{
    char data;
    struct Node* first;//指向临界表
}GNode;
GNode g[105];

typedef struct Node//邻接表结点
{
    int val;//存储该点的下标
    struct Node* next;
}Node;

//根据数据查找下标
int Find(char x)
{
    for(int i=0;i<n;i++)
    {
        if(g[i].data==)
    }

}



int mian()
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
        
    }











}