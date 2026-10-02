#include<stdio.h>
#include<stdlib.h>
//通过二叉链表，每个节点只存储该节点的数据和长子节点的地址和该节点右边的第一个亲兄弟节点的地址，将n叉树转化为二叉树
typedef struct Node{
char data;
struct Node* son;
struct Node* bro;
}Node,*TreeList ;

//初始化函数
TreeList Init(char r){
Node* s=(Node*)malloc(sizeof(Node));//定义根指针，指向根节点
s->data=r;
s->son=s->bro=NULL;
return s;
}

/*关于查找，需要利用递归查找的思想
如果想从以A为根节点的二叉树中查找某数据fx，只需要遍查找三个部分就行：根节点、根节点左叉树、根节点右叉树
1）需要先判断该根节点的数据与查找数据fx是否相等，如果相等返回该值即可.否则执行第二步
2）如果不相等，需要以根节点为左叉下的数据作为新的根节点进行查找fx，找到返回答案，否则执行第三部
3）如果左叉树没有查找到，再以右叉下的数据作为根节点进行查找
4）如果都没有查找到，返回NULL
如此一个递归过程
*/
TreeList Find(TreeList root , char fx){
    if(fx==root->data)
    {//递归出口
        return root;
    }
    TreeList ans=NULL;
    if(root->son!=NULL){
        ans=Find(root->son,fx);
        if(ans!=NULL) return ans;
    }
    if(root->bro!=NULL){
        ans=Find(root->bro,fx);
        if(ans!=NULL) return ans;
    }
return NULL;
}

//插入函数
TreeList Insert(TreeList r,char x,char fx){
//1、开辟一个新结点，存储数据。如果该树是个有序树，那么插入后该节点一定没有孩子和右边相邻的亲兄弟，所以节点指针域为空
Node* s=(Node*)malloc(sizeof(Node));
s->data=x;
s->bro=s->son=NULL;
/*2、查找到他的父亲节点
    1）如果父亲节点没有孩子，将父亲节点的son指针指向s
    2）如果父亲节点有孩子，将该节点插入在父亲节点的长子节点的兄弟节点的最右边
*/
TreeList fxNode=Find(r,fx);
if(fxNode->son==NULL){
    fxNode->son=s;
}
else{
    Node* p=fxNode->son;
    while(p->bro!=NULL){
       p=p->bro;
    }
    p->bro=s;
    }
return r;
}



int main(){
//1、输入头节点 进行初始化
int n;
scanf("%d",&n);
char r;
scanf(" %c",&r);
TreeList root=Init(r);
//2、输入各节点
for(int i=0;i<n-1;i++){
    char x,fx;
    scanf(" %c %c",&x,&fx);
    root=Insert(root,x,fx);
}

//找某节点的孩子
char c;
scanf(" %c",&c);
TreeList k;
k=Find(root,c);
printf("His Son has:");
k=k->son;
printf("%c ",k->data);
k=k->bro;
while(k!=NULL){
printf("%c ",k->data);
k=k->bro;
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