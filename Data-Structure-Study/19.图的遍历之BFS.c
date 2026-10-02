#include<stdio.h>
#include<stdlib.h>
int n,m;
#define inf 105
int flag[105];//用来标记某节点有没有如果对
int dist[105];//该点到起点的最短距离
//----------------循环队列-------------------
typedef struct Queue{
    int data[105];//用来存取图的结点下标
    int l;//队首“指针” 
    int r; // 队尾“指针”
}Queue;
Queue Init(Queue *q){
    q->l=0;//l指向队首结点
    q->r=0;//r指向的是队尾的下一个节点
}
//入队
Queue Push(Queue *q,int x){
    if((q->r+1)%105==q->l)
    {
	printf("队满，不能入队\n"); 
    }
    q->data[q->r]=x;//将x入队
    q->r=(q->r+1)%105;
    //某节点入队的同时，将其进行标记
    flag[x]=1;
}
//判空
int is_empty(Queue q){
if(q.l==q.r)
{//队列空
    return 0;//空
}
return 1;//非空
}
//出队
int Pop(Queue *q){
    if(is_empty(*q)==0)
    {//队空
        printf("Q IS EMPTY CANNOT POP");
        return -1;
    }
    int x=q->data[q->l];
    q->l=(q->l+1)%105;
    return x;
}
//------------图的邻接表存储------------------
//邻接表结点
typedef struct Node{
    int adj;//该图的邻结点的下标
    struct Node*next;
}Node;

typedef struct gNode{
    char dat;
    Node* first;
}gNode;
gNode g[105];

int Find(int x)
{//查找下标
    for(int i=1;i<=n;i++)
    {
        if(g[i].dat==x) return i;
    }
}
//-----------BFS-------------
/*  1、创建空队列，选择任意结点作为起点，将起点入队
    2、循环：只要队列非空，将队首元素q出队并将q的没有入过队的邻结点入队，并对刚入队的邻接点打上标记
    3、当队列为空，访问结束
*/
void BFS(int i)
{//从编号为i点的开始遍历
    /*for(int j=0;j<=n;j++)
    {//对距离数组初始化
       dist[j]=inf;
    }*/
    Queue q;
    q=Init(&q);
    //dist[i]=0;//起点的距离为0
    Push(&q,i);
    int t,j;
    while(is_empty(q)==1)
    {   
        //将队首元素t出队，并将t的所有没入过队的邻接点进行入队
        t=Pop(&q);//t是出队元素的下标
        printf("%c ",g[t].dat);//访问
        Node* p=g[t].first;
        while(p!=NULL)
        {  
            j=p->adj;
            if(flag[j]==0)
            {//将未入过队的邻接点入队
                Push(&q,j);
                //dist[j]=dist[t]+1;//t的未被标记的邻接点j距离起点都比t远1格
            }
            p=p->next;
        }
    }
    



}


int main()
{
    scanf("%d %d",&n,&m);
    getchar();
    for(int i=1;i<=n;i++)
    {//存结点并对邻接链表初始化
        char c;
        scanf("%c",&c);
        g[i].dat=c;
        g[i].first=NULL;
    }
    char x,y;
    int xi,yi;
    for(int i=1;i<=m;i++)
    {//存边
        scanf(" %c %c",&x,&y);
        xi=Find(x);
        yi=Find(y);
        //将y存入x的邻接链表中
        Node* s1=(Node*)malloc(sizeof(Node));
        s1->adj=yi;
        s1->next=g[xi].first;
        g[xi].first=s1;
        //将x存入y的邻接链表中
        Node* s2=(Node*)malloc(sizeof(Node));
        s2->adj=xi;
        s2->next=g[yi].first;
        g[yi].first=s2;
    }
    
    for(int i=1;i<=n;i++)
    {//非连通图
        if(flag[i]==0) BFS(i);
    }
}
/*
9 16
ABCDEFGHI
A B
A F
B G
G F
B C
B I
C I
C D
I D
D G
D H
D E
G H
H E
E F
F G
*/