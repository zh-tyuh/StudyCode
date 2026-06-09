#include<stdio.h>
#include<stdlib.h>
int n,m;//给出n个集合，m个操作
int f[105];//f[i]为i的父亲的下标
int h[105];
int maxx(int a,int b){return a>b?a:b;}
/*
int Find(int x)
{//查找到x的根节点下标---非递归
    int p=x;
    while(f[p]!=p)
    {
        p=f[p];//p不是根结点 就向上指向父亲
    }
    return p;
}
*/
/*
int Find(int x)
{//查找到x的根节点下标---递归
    if(x==f[x]) return x;
    else return Find(f[x]);//x父亲f[x]的根节点就是x的根节点
}
*/

int Find(int x)
{//查找到x的根节点下标---路径压缩--将x到fx的全部节点化为fx的孩子
     if(x==f[x]) return x;
    else
    {
        int p=Find(f[x]);//x的根节点就是x父亲f[x]的根节点
        f[x]=p;
        return p;
        //以上三步可以直接写成：return f[x]=Find(f[x]);
    }
 }

int main(){    
//输入集合个数和操作次数
scanf("%d %d",&n,&m);
//初始化：将每个数据的父亲初始化为自己
for(int i=1;i<=n;i++)
{
    f[i]=i;
    h[i]=1;//将所有集合的高度初始化为1
}

for(int i=0;i<m;i++)
{
    int op,x,fx,y,fy;//op表示要执行的操作：1表示合并 2表示查询
    scanf("%d %d %d",&x,&y,&op);
    if(op==1)
    {//将x和y所在的集合合并
        //1、查找到x和y所在集合的根节点fx,fy
        fx=Find(x);
        fy=Find(y);
        //2、判断是否属于同一集合,如果不,比较两棵树的高度,让高度较高的树的根节点作为高度较低的根节点的孩子
        if(fx!=fy){
            if(h[fx]>=h[fy])
            {
                f[fy]=fx;//合并
                h[fx]=maxx(h[fx],h[fy]+1);//更新高度
            }
            else
            {
                f[fx]=fy;//合并
                h[fy]=maxx(h[fx]+1,h[fy]);//更新高度
            }
        }
    }
    else
    {//查询x和y是否属于同一个集合:判断x和y的根节点是否相同
        fx=Find(x);
        fy=Find(y);
        if(fx==fy) printf("YES\n");
        else printf("NO\n");
    }
}
}