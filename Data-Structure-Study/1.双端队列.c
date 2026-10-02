#include<stdio.h>
#include<stdlib.h>
//1、双端队列的顺序存储结构

#define MAXSIZE 10
typedef struct SQueue {
    int *data;
    int left;
    int right; 
}SQueue;

/*为了避免出现双端队列前端和后端空间不对等的情况，双端队列采取循环队列的方式。
  但是在使用过程中会遇到一个问题：刚开始左端指针t和右端指针r都指向0位置，然后进行入队。
  那么第一次入队算是从左端入队还是从右端入队？如果算作从左端入队的话，那么data[0]=kl没有问题
  但是此时r=0,再进行一次右端入队,data[r]=data[0]=kr，导致0的位置出现重合。
  为了解决这个问题，我们要提前规定好，第一次入队算是左端入队还是右端入队。
  如果规定了左端入队，那么从右端入队的元素就不应该放在索引0的位置。
  此时t指向的是左端元素的下一个元素，r指向的真实的右端元素   */

  
//1.1、 双端队列的初始化
void Init(SQueue *SQ1){
    SQ1->data=(int*)malloc(sizeof(int)*MAXSIZE);
    SQ1->right=0;
    SQ1->left=0;
}

//1.2、左端入队
void TruePush(SQueue *SQ1,int k){
    if((SQ1->left-1+MAXSIZE)%MAXSIZE == SQ1->right) return; //队满
    SQ1->data[SQ1->left]=k;
    SQ1->left=(SQ1->left-1+MAXSIZE)%MAXSIZE;
}

//1.3、右端入队
void RightPush(SQueue *SQ1,int k){
    if((SQ1->left-1+MAXSIZE)%MAXSIZE == SQ1->right) return; //队满
    SQ1->right=(SQ1->right+1)%MAXSIZE;
    SQ1->data[SQ1->right]=k;
}

//1.4、左端出队
void leftPop(SQueue *SQ1){
    if(SQ1->left==SQ1->right) return;   //队空
    SQ1->left=(SQ1->left+1)%MAXSIZE;
}

//1.5、右端出队
void RightPop(SQueue *SQ1){
    if(SQ1->left==SQ1->right) return;   //队空
    SQ1->right=(SQ1->right-1+MAXSIZE)%MAXSIZE;
}

//2、双端队列的链式存储结构
typedef struct LQNode{
    int val;
    struct LQNode* pre;
    struct LQNode* next;
}LQNode;

typedef struct LQuene{
    LQNode *left;
    LQNode *right;
}LQuene;

/* 双端列表的链式存储采用双向链表的方式，与普通双向链表不同的是，双端列表的头指针指向的的中间的mid结点，然后向两边延申
    但是如果从mid结点向两边延伸形成例如1-2-mid-4-3结构，如果不断的左出队，出队完2之后下一次出队的并不是4
    而mid结点究竟应该存储第一次左端入队的数据还是第一次右端入队的数据？
    所以在链表当中，我们同样得先规定第一次入队是左端还是右端，如果规定第一次入队是右端入队的话
    那么也会得出和顺序存储同样的结论，右端指针指向的实际上是最右端数据的下一个节点，左端指针指向的是真实的左端数据 */

//2.1、初始化
void Init2 (LQuene *LQ){
  LQNode*mid=(LQNode*)malloc(sizeof(LQNode));
  mid->next=mid->pre=NULL;
  LQ->right=mid;
  LQ->left=mid;
}

//2.2、左端入队
void leftPush2(LQuene *LQ,int k){
    LQNode* p=(LQNode*)malloc(sizeof(LQNode));
    p->val=k;
    p->pre=NULL;
    p->next=LQ->left;
    LQ->left->pre=p;
    LQ->left=p;
    p=NULL;
}

//2.3、右端入队
void RightPush2(LQuene *LQ,int k){
    LQNode* p=(LQNode*)malloc(sizeof(LQNode));
    LQ->right->val=k;
    LQ->right->next=p;   
    p->next=NULL;
    LQ->right=p;
    p=NULL;
}

//2.4、左端出队
void leftPop2(LQuene *LQ){
    if(LQ->right==LQ->left) return;  //判空
    LQNode *p=LQ->left;
    LQ->left=LQ->left->next;
    LQ->left->pre=NULL;
    free(p);
    p=NULL;
}

//2.5、右端出队
void RightPop2(LQuene *LQ){
    if(LQ->right==LQ->left) return;  //判空
    LQNode *p=LQ->right;
    LQ->right=LQ->right->pre;
    LQ->right->next=NULL;
    free(p);
    p=NULL;
}



int main(){
SQueue Sq11;
Init(&Sq11);
TruePush(&Sq11,10);
TruePush(&Sq11,12);
TruePush(&Sq11,14);
TruePush(&Sq11,15);
for(int i=0;i<MAXSIZE;i++) printf("%d\n",Sq11.data[i]);



}