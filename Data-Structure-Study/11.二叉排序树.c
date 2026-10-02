#include<stdio.h>
#include<stdlib.h>
//结点类型
typedef struct BSTNode {
int data;
struct BSTNode *l ;
struct BSTNode *r ;
}BSTNode;

//=============查找操作====================

/*1、递归查找数据x
    a、判断是否为空，如果为空，返回NULL。
    (1)如果x==root->data，返回root;否则：
    进入循环：
        (2)如果x<root->data，则只需要在左子树中查找即
        (3)如果x>root->data，则只需要在右子树中查找即
*/
BSTNode* Search1(BSTNode*root,int x){
if(root==NULL||root->data==x) return root; //也可以if(x==root->data) return root;
if(x<root->data) return Search1(root->l,x);
else return Search1(root->r,x);
return NULL;
}

//非递归查找
BSTNode* Search2(BSTNode*root,int x){
if(root==NULL)   return NULL;
BSTNode* p=root;
while(p!=NULL&&p->data!=x){   //也可以将p->data==x放在循环中进行判断
if(x<p->data) p=p->l;//在左子树中
else p=p->r;//在右子树中
}
//当循环结束时，有两种情况:1、没找到 返回NULL 2、找到了 返回p   会发现如果没找到p正好也是NULL，所以可以直接返回p
return p;
}

//=============插入函数====================
//空树插入
BSTNode* CreatBST(int x){
    //创建一个新结点
    BSTNode*s=(BSTNode*)malloc(sizeof(BSTNode));
    s->data=x;
    s->l=s->r=NULL;
    return s;
}

/*1、递归插入
    a、如果传入的root为空，执行空树插入（递归出口）
    b、如果x<root,在左子树中进行插入操作，即以root->l为根节点进行插入
    c、如果x>root,在右子树中进行插入操作，即以root->r为根节点进行插入
*/
BSTNode* Insert1(BSTNode*root,int x){
    if(root==NULL)//递归出口
    {  //空树插入 根指针指向新创建的结点
        root=CreatBST(x);
        return root;
    }
    if(x<root->data){
        root->l=Insert1(root->l,x); //往左子树中插入x
    }
    else{
        root->r=Insert1(root->r,x);
    }
    return root; //插入之后返回新树
}

/*2、非递归插入
    找插入位置，利用指针p来找插入位置，但是实际上当p为空时，只能判断插入的时机，需要让pre时刻指向p的父亲，最后让pre的左指针或者右指针指向新结点
    当p==NULL的时候，比较pre和x来判断时左孩子还是右孩子
*/
BSTNode* Insert2(BSTNode *root,int x){
    if(root==NULL){//空树插入，根指针指向新创建的结点
        root=CreatBST(x);
        return root;
    }
    //创建一个新节点  也可以直接调用函数CreateBSTNode(x)
    BSTNode* s=(BSTNode*)malloc(sizeof(BSTNode));
    s->data=x;
    s->l=s->r=NULL;
    //查找s的父亲节点
    BSTNode* p=root;
    BSTNode*pre=NULL;
    while(p!=NULL){
        pre=p;
        if(x<p->data) p=p->l; //往左子树走
        else p=p->r;   //往右子树走
    }
    //此时pre就是s的父亲节点
    if(x<pre->data) pre->l=s;
    else pre->r=s;
    return root;
}

//================删除操作====================
/*
1、当被删除的结点p度为0的时候，需要将p的父亲节点pre指向p的指针赋值为空，然后free(p)
2、当被删除的结点p度为1的时候，需要将p的父亲节点pre指向p的指针指向p唯一的孩子，然后free(p)
可以发现当p的度为0的时候，NULL也是p的孩子，因此可以把两种情况看成同一种情况
3、找到p之后，只需要判断p的一方是否为空即可。
比如说只判断p的左指针是否指向NULL，如果非空，pre指向这个非空；如果是空，无需判断右指针是不是空，直接指向就行
因为p的右指针此时只有两种情况，NULL和有数据，直接指向即可
4、当度为2的时候


*/
BSTNode* Delet1(BSTNode* root,int x){
    //判断空
    if(root==NULL) return NULL;
    //1、先找到要被删除的结点p和其父亲节点pre  两种情况：找到了和没找到
    BSTNode* p=root;
    BSTNode* pre=NULL;
    while(p->data!=x&&p!=NULL){  //p最后有两种情况:1、p==NULL即没有x这个元素 2、p->data==x 找到了
        pre=p;
        if(x<p->data) p=p->l;
        else p=p->r;
    } 
    if(p==NULL) //x不存在 
    {
        printf("NOT FOUND!\n");
        return root;
    }

    //当度为2的时候：只需要让其前驱结点顶替该节点
    if(p->l!=NULL&&p->r!=NULL)
    {   //1)找到删除结点的中序前驱结点y和其父亲节点fy,其前驱节点就是p左子树中最靠右的位置
        BSTNode* y=p->l;
        BSTNode* fy=p;
        while(y->r!=NULL){
            fy=y;
            y=y->r;
        }
        //2)让y结点取代p结点，只需要让p->data==y->data即可
        p->data=y->data;
        p=y;
        pre=fy;
        //于是就将问题转化为了删除度为0或1的结点
       
    }

    //当度为1或者0
        //找到p的可能存在的结点或指向NULL
        BSTNode* k=NULL;
        if(p->l!=NULL) k=p->l;
        else k=p->r;
        //将pre指向p的指针指向NULL或p的唯一存在的结点
        
        if(pre==NULL)//但是还要注意的一点是，如果要删除的是的根节点，也就是说pre==NULL
        {
            root=k;
        }
        else//p不是根节点,p有父亲,让p的父亲pre指向k
        {
        if(pre->l==p) pre->l=k;
        else pre->r=k;  
        }
    
    free(p);
    p=NULL;
    return root;
}


/*递归删除：在以root为根的树中 删除数据x
1、if(root==NULL) 无法删除
2、if(x<root->data) 在根节点的左子树中执行删除操作 
3、if(x>root->data) 在根节点的右子树中执行删除操作 
4、if(x==root->data) 分两种情况删除：1、度为2   2、度为1或者0 
    (1)度为1或者0:就是删除根节点，直接让root指向其唯一存在的孩子即可
    (2)度为2:让root->data等于其中序遍历的前驱后，递归执行删除操作
注意：递归删除操作的本质删除每个子递归的根节点的元素，root指针一定会发生变化，因此每次删除必须得接收新指针root->r=Delet2(root->r,x);
*/
BSTNode* Delet2(BSTNode* root,int x){
    if(root==NULL){
        printf("NOT FOUND");
        return NULL;
    }
    if(x<root->data){
       root->l=Delet2(root->l,x);//在root的左子树中进行删除操作，需要用root->l接受新的左子树
    }
    else if(x>root->data){
       root->r=Delet2(root->r,x);//记得赋值。也就是root->r指向新的左子树
    }
    else
    {//root==x 删除root
        //度为2：
        if(root->l!=NULL&&root->r!=NULL){
        //找到root的前驱节点
            BSTNode* y=root->l;
            while(y->r!=NULL){
            y=y->r;
            }
            root->data=y->data;
            //在root的左子树中删除y---递归调用
            root->l=Delet2(root->l,y->data);//记得赋值。也就是root->l指向新的左子树
        }
        //度为1或者0，直接让root指向其唯一存在的结点
        else{
            BSTNode*p=root;  //p指向被删除的结点
            if(root->l!=NULL) root=root->l;
            else root=root->r;
            free(p);
            p=NULL;
        }
    }
    return root;//注意

}



//=======中序遍历如果结果有序，则说明插入成功====
void Order(BSTNode* root){
    if(root==NULL){
        return;
    }
    Order(root->l);
    printf("%d | ",root->data);
    Order(root->r);
}

//===============主函数=======================
int main(){
int n;//要插入n个数据
scanf("%d",&n);
int x;
BSTNode *root=NULL;
for(int i=0;i<n;i++){
    scanf("%d",&x);
    root=Insert2(root,x);
}

Order(root);
printf("\n");
root=Delet2(root,6);
Order(root);




}


/*
9
8 3 10 1 6 14 4 7 13
*/