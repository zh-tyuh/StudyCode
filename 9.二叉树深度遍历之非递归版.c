#include<stdio.h>
#include<stdlib.h>
//--------------------------------------二叉树的定义---------------------------------------
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
//--------------------------------------栈的定义（有头结点，头指针top指向首结点，然后才指向首元结点）---------------------------------------
typedef struct SNode{
struct Node* data;
struct SNode *next;
}SNode,*SStack;

//1、栈的初始化
SStack Sinit(){
    SNode* s=(SNode*)malloc(sizeof(SNode));
    s->next=NULL;
    return s;
}
//2、入栈操作
SStack Push(SStack top,TreeNode x){
    SNode* s=(SNode*)malloc(sizeof(SNode));
    s->data=x;
    s->next=top->next;
    top->next=s;
    return top;
}

//4、判空
int isEmpty(SStack top){
    if(top->next==NULL) return 0;//0表示空
    else return 1;//表式非空
    
}
//3、出栈操作
TreeNode Pop(SStack top){
    if(isEmpty(top)==0) 
    {
        printf("STACK IS EMPTY");
        return NULL;
    }
    SStack p=top->next;
    top->next=p->next;
    TreeNode outdata=p->data;
    free(p);
    p=NULL;
    return outdata;
}

TreeNode Get(SStack top){
if(isEmpty(top)==0){
    printf("STACK IS EMPTY");
    return NULL;

}
    TreeNode p=top->next->data;
    return p;

}





//-------------------------------遍历函数-----------------------------------
void visit(Node* x){
printf("%c",x->data);
}

/*先序遍历：
1、引入指针p，一开始指向根节点; 引入栈，用来保存经过的结点
2、循环：当指针p为非空 或 栈为非空的时候进行循环
    1)如果p是非空：访问p指向的元素k,将k入栈,然后p先序遍历p的左子树,即p指向p的左孩子
    2)如果p是空:取出栈顶元素f,p指向栈顶元素f的右孩子
*/
void PreOrder(TreeNode root){
if(root==NULL) //判空
{
    printf("TREE IS EMPTY SO CANNOT ORDER");
    return ;
}

    TreeNode p=root;
    SStack top=Sinit();
    while(p!=NULL || isEmpty(top)==1){
        if(p!=NULL)
        {
            visit(p);
            top=Push(top,p);
            p=p->l;
        }
        else{
           TreeNode f = Pop(top);
           p=f->r;
        }
    }
    printf("\n");
}

/*中序遍历：
1、引入指针p，一开始指向根节点; 引入栈，用来保存经过的结点
2、循环：当指针p为非空 或 栈为非空的时候进行循环
    1)如果p是非空：将p指向的结点k入栈,然后p先序遍历p的左子树,即p指向p的左孩子
    2)如果p是空:取出栈顶元素f,访问元素f,p指向栈顶元素f的右孩子
*/
void InOrder(TreeNode root){
if(root==NULL) //判空
{
    printf("TREE IS EMPTY SO CANNOT ORDER");
    return ;
}

    TreeNode p=root;
    SStack top=Sinit();
    while(p!=NULL || isEmpty(top)==1){
        if(p!=NULL)
        {
            top=Push(top,p);
            p=p->l;
        }
        else{
           TreeNode f = Pop(top);
           visit(f);
           p=f->r;
        }
    }
    printf("\n");
}

/*
后序遍历:
1、引入指针p,指向root结点;引入栈
2、进入循环：如果p非空或者栈非空，说明还有节点没有被访问完
    1）当p为非空时，将p入栈，p指向p的左孩子结点
    2）当p为空时，说明栈顶元素f的某根节点的一字数被访问完
        a.如果f不存在右子树 或者 pre指向的元素是f的右孩子 对栈顶f进行出栈，同时进行访问
        b.否则p指向f的右子树
*/
void PostOrder(TreeNode root){
if(root==NULL) //判空
{
    printf("TREE IS EMPTY SO CANNOT ORDER");
    return ;
}
TreeNode p=root;
TreeNode pre=NULL;
SStack top=Sinit();
while(p!=NULL||isEmpty(top)==1){
    if(p!=NULL){
        top=Push(top,p);
        p=p->l;
    }
    else{   //p为空,此时栈顶的元素某一棵子树被访问完
        TreeNode f=Get(top);
        if(f->r==NULL||pre==f->r){
            f=Pop(top);
            pre=f;
            visit(f);
        }else{
            p=f->r;
        }
    }

}
}







//--------------------------------------------------------------------------
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
//3、遍历
PreOrder(root);
InOrder(root);
PostOrder(root);

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