#include<stdio.h>
#include<stdlib.h>
#define inf 10005
//带权无向图为例。n个点 m条边  n<=100  0<=w<=10000  
int n,m;
char data[105];
//verge用来存储边，v[i][j]的值为下标i指向下标j的边，v[i][j]的值表示该边的权值
//当v[i][j]==inf正无穷的时候，表示没有边(因为权值为0有时也有实际意义)
int verge[105][105];

int Find(int x)
{//查找下标
    for(int i=1;i<=n;i++)
    {
        if(data[i]==x) return i;
    }
}


int main()
{   
    scanf("%d %d",&n,&m);
    //将结点存放在节点数组
    char p;
    for(int i=1;i<=n;i++)   
    {
        scanf(" %c",&data[i]);
    }

    //边矩阵初始化
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            verge[i][j]=inf;
        }
    }

    char x,y;
    int w;
    for(int i=1;i<=m;i++)
    {
        scanf(" %c %c %d",&x,&y,&w);
        //查找x,y的下标
        int fx,fy;
        fx=Find(x);
        fy=Find(y);
        verge[fx][fy]=w;
    }

    //查看某节点的出度和入度
    char c;
    int outd=0,ind=0;
    scanf(" %c",&c);
     int ci=Find(c);
    for(int j=1;j<=n;j++)
    {//出度
        if(verge[ci][j]<inf)
        {
            outd++;
        }
    }
     for(int i=1;i<=n;i++)
    {//入度
        if(verge[i][ci]<inf)
        {
            ind++;
        }
    }
    printf("C'S OUTD IS %d | C'S IND IS %d",outd,ind);
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