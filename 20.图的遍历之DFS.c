#include<stdio.h>
#include<stdlib.h>
//采用邻接矩阵存图有n（<=100）个点 m条边的无权无向图 对该图进行遍历。
int n,m;
char data[105];
int flag[105];//标记数组，当flag[i]==1时，表示该点已经被遍历过
int g[105][105];//邻接矩阵,当g[i][j]==g[j][i]==1时,表示存在边
int Find(char x)
{//根据字符找下标
    for(int i=1;i<=n;i++)
    {
        if(data[i]==x) return i;
    }
    return -1;
}
/*DFS遍历法：先选取一个点i作为起始点，从起始点开始遍历->将起始点进行标记
            ->继续遍历w没有被标记过的邻接点
*/
void DFS(int i)
{  
    printf("%c ",data[i]);//访问i
    flag[i]=1;
    for(int j=1;j<=n;j++)
    {//遍历i的所有邻接点，当g[i][j]==1时，表示有边，即应该遍历
        if(g[i][j]==1&&flag[j]==0)
        {//找i点未被访问过的邻接点j
            DFS(j);
        }
    }
}

int main()
{
    scanf("%d %d",&n,&m);
    getchar();
    for(int i=1;i<=n;i++)
    {
        scanf("%c",&data[i]);
    }
    char x,y;
    int xi,yi;
    for(int i=1;i<=m;i++)
    {
        scanf(" %c %c",&x,&y);
        xi=Find(x);
        yi=Find(y);
        //将边进行存储
        g[xi][yi]=g[yi][xi]=1;//表示x和y中间有一条边
    }

    //使用深度搜索进行遍历
    DFS(1);



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