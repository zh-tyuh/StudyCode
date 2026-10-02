#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
char data;
struct Node* l;
struct Node* r;
}Node,*TreeNode;
//----------------------------链式队列定义---------------------------------------
//1、队列结点类型声明
typedef struct Qnode{
Node* BTnode;//队列元素是二叉树的节点类型
struct Qnode *next;
}Qnode,*Queuenode;
//2、队列数据结构声明
typedef struct Queue{
Queuenode l;
Queuenode r;
}Queue;

//3、队列初始化
Queue QInit(){
Qnode* p =(Qnode*)malloc(sizeof(Qnode));
Queue q;
q.l=q.r=p;
return q;
}

//4、入队
void pushQ(Queue *q,Node* v ){
    //开辟新结点，将数据存储到节点中
    Qnode* s=(Qnode*)malloc(sizeof(Qnode));
    s->BTnode=v;
    s->next=NULL;
    //将新的队列节点插入在队列中
    q->r->next=s;
    q->r=s;
    s=NULL;
}

//5、出队
Node* popQ(Queue *q ){
    if(q->r==q->l->next) q->r=q->l;//避免q.r指向被删除的首元结点变成空指针
    Qnode*s=q->l->next;
    q->l->next=q->l->next->next;
    Node*p=s->BTnode;
    printf("%c ",p->data);
    free(s);
    return p;
}

//6、判空
int isEmpty(Queue *q){//判空
    if(q->l==q->r)return 1;
    else return 0;
}

//--------------------------------------------
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


/*广度遍历函数
1、引入队列，将根节点入队
2、循环：只要队列非空,从队列中取出队首元素进行访问，将该元素的左右孩子入队
3、当队列为空，访问结束
*/
void BTOrder(TreeNode root){
//1、引入队列，将根节点入队
Queue q;
q=QInit();
pushQ(&q,root);
//2、循环：只要队列为非空，将队首元素进行出队
while(isEmpty(&q)==0){
Node* p=popQ(&q);
if(p->l!=NULL) pushQ(&q,p->l);
if(p->r!=NULL) pushQ(&q,p->r);
}
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
//3、进行遍历

BTOrder(root);




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