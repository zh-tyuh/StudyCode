#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
char data;
struct Node* l;
struct Node* r;
}Node,*TreeNode;

//1、初始化
TreeNode Init(char r){
Node*s=(Node*)malloc(sizeof(Node));
s->data=r;
s->l=s->r=NULL;
return s;
}

/*3、查找函数----和长子兄弟表示法类似，需要利用递归
1）从根节点开始，判断要查找的结点是不是根节点，如果是直接返回，如果不是，执行2
2）查找根节点的左边子树(以左孩子作为根节点)，如果查找的到(查找到非空)，返回该结点，否则执行3
3）查找根节点的右边子树(以右孩子作为根节点)，如果查找的到(查找到非空)，返回该节点，否则返回空
*/
TreeNode Find(TreeNode root,char fx){
if(fx==root->data){
    return root;
}
TreeNode ans;
//以某节点为根节点，查询左子树
if(root->l!=NULL){
    ans=Find(root->l,fx);
    if(ans!=NULL){
        return ans;
    }
}
//以某节点为根节点，查询右子树
if(root->r!=NULL){
    ans=Find(root->r,fx);
    if(ans!=NULL){
        return ans;
    }
}
return NULL;
}

//2、插入函数
TreeNode Insert(TreeNode root,char x,char fx,int flag){
//1)开辟新结点并赋值
Node*s=(Node*)malloc(sizeof(Node));
s->l=s->r=NULL;
s->data=x;
//2)将新结点插入二叉链表
TreeNode p=Find(root,fx);
if(flag==0){//左节点
    p->l=s;
}
else{
    p->r=s;
}
return root;
}


int main(){
int n;
char r;
scanf("%d",&n);
scanf(" %c",&r);
int flag;
//1、初始化
TreeNode root=Init(r);
//2、插入数据
for(int i=0;i<n-1;i++){
    char x,fx;
    scanf(" %c %c %d",&x,&fx,&flag);
    root=Insert(root,x,fx,flag);
}
printf("INSERT COMPELETE\n");
//3、查找某节点的孩子结点
char xx;
scanf(" %c",&xx);
TreeNode p=Find(root,xx);
if(p->l==NULL) printf("NOT HAVE LEFT SON\n");
else printf("LEFT SON IS %c\n",p->l->data);
if(p->r==NULL) printf("NOT HAVE RIGHT SON\n");
else printf("RIGHT SON IS %c\n",p->r->data);
//4、想要查找某节点的父亲节点不容易，需要将整个树进行遍历才行
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