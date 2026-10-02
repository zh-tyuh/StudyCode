#include<stdio.h>
#include<stdlib.h>
#define maxx 100
char Tree[maxx];

int Find(char fx){
    for(int i=1;i<maxx;i++){
        if(Tree[i]==fx){
            return i;
        }

    }
    return -1;
}


int main(){
//1、对树数组进行初始化，将数组全部赋值为空
for(int i=0;i<maxx;i++){
Tree[i]=' ';
}
//2、插入根节点
int n;
char r;
scanf("%d",&n);
scanf(" %c",&r);
Tree[1]=r;
int flag;//当flag=0表示该节点为左孩子，=1表示右孩子
for(int i=2;i<=n;i++){
char x,fx;
scanf(" %c %c %d",&x,&fx,&flag);
int j=Find(fx);
if(flag==0)
{
    Tree[j*2]=x;
}
else
{
    Tree[2*j+1]=x;
}
}

//3、查找某节点的孩子节点
char xx;
scanf(" %c",&xx);
int j=Find(xx);
if(Tree[2*j]==' ') printf("NOT HAVE LEFT SON\n");
else printf("LEFT SON IS: %c \n",Tree[2*j]);
if(Tree[2*j+1]==' ') printf("NOT HAVE RIGHT SON\n");
else printf("RIGHT SON IS: %c\n ",Tree[2*j+1]);

//4、查找父亲节点
if(xx==Tree[1]) printf("IS ROOT NODE\n");
else printf("FATHER IS %c\n",Tree[j/2]);

}


/*

7
a
b a 0
c a 1
d b 0
e b 1
f e 0
g e 1

*/