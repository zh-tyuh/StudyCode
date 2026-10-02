#include<stdio.h>
#include<stdlib.h>
typedef struct AVLNode{
    int data;
    struct AVLNode* l;
    struct AVLNode* r;
    int h;
}AVLNode;
//获取最大值
int maxx(int a,int b){
return a>b?a:b;
}
/*结点的高度，就是结点左子树和右子树高度的最大值+1
但是不能直接p->h=maxx(p->l->h,p->r->h)+1; 因为p的左子树和右子树可能为空
空结点中不能获取数据h，因此需要用Get_h进行辅助
这样的话p->h=maxx(Get_h(p->l),Get_h(p->r))+1
*/
int Get_h(AVLNode* x){
    if(x!=NULL) return x->h;
    else return 0;
}
//===============平衡二叉树的插入操作===========
/* 1、右旋：只需要进行两步操作
    1、y->r=x;
    2、x->l=yr
*/
AVLNode* LLrotation(AVLNode* x){
    AVLNode* y=x->l;
    AVLNode* yr=y->r;
    y->r=x;
    x->l=yr;

    //需要重新计算x和y的高度
    x->h=maxx(Get_h(x->l),Get_h(x->r))+1;
    y->h=maxx(Get_h(y->l),Get_h(y->r))+1;
    return y; //返回调整之后的根结点
}
//2、左旋：和右旋方向相反的操作
AVLNode* RRrotation(AVLNode* x){
    AVLNode* y=x->r;
    AVLNode* yl=y->l;
    y->l=x;
    x->r=yl;
    //需要重新计算x和y的高度
    x->h=maxx(Get_h(x->l),Get_h(x->r))+1;
    y->h=maxx(Get_h(y->l),Get_h(y->r))+1;
    return y; //此时y为子树的根节点
}
//3、 LR:新节点插入在x左孩子的右子树中,需进行一次左旋,再进行一次右旋
AVLNode* LRrotation(AVLNode* x){
    //先对x的左子树进行左旋
    x->l=RRrotation(x->l);//x的左子树进行旋转x的左子树会发生变化需要重新接收
    //然后对x进行一次右旋操作
    x=LLrotation(x);
    return x;
}
//4、RL：新节点插入在x右孩子的左子树中,需进行一次右旋,再进行一次左旋
AVLNode* RLrotation(AVLNode* x){
    //先对x的右子树进行右旋
    x->r=LLrotation(x->r);//x的左子树进行旋转x的左子树会发生变化需要重新接收
    //然后对x进行一次右旋操作
    x=RRrotation(x);
    return x;
}

//空树插入
AVLNode* CreatNode(int x){
    AVLNode* s=(AVLNode*)malloc(sizeof(AVLNode));
    s->data=x;
    s->h=1;
    s->l=s->r=NULL;
    return s;
}


/*插入函数：
(1)先按照二叉排序树的插入方式进行插入保持顺序性(递归插入)
(2)再对二叉排序树进行调整,判断是否满足平衡性
*/
AVLNode* Insert(AVLNode* root,int x){
    if(root==NULL)
    {//空树插入
        root=CreatNode(x);
        return root;
    }

    if(x<root->data)
    {//在左子树中插入
        root->l=Insert(root->l,x);
       //此时root可能失衡 如果失衡 一定是root的左子树比右子树高2 ----》LL LR
        if(Get_h(root->l)-Get_h(root->r)>1) //root失衡
        {//LL或LR
            if(x<root->l->data)//Get_h(root->l->l)>Get_h(root->l->r)
            {//LL
                root=LLrotation(root);
            }
            else
            {//LR
                root=LRrotation(root);
            }
        }
    }

    if(x>root->data)
    {//在右子树中插入
        root->r=Insert(root->r,x);
        //此时root可能失衡 如果失衡 一定是root的右子树比左子树高2 ----》RR RL
        if(Get_h(root->r)-Get_h(root->l)>1) //root失衡
        {//RR或RL
              if(x<root->r->data)//判断使RR还是RL既可以比较数据也可以比较高度：Get_h(root->r->l)>Get_h(root->r->r)
            {//RL
                root=RLrotation(root);
            }
            else
            {//RR
                root=RRrotation(root);
            }
        }
    }
    //插入完成后需要重新计算root的高度，虽然在失衡调整中会有对高度的调整，但是并不是所有结点都会进行失衡调整，只有最小失衡子树结点才会进入到旋转过程中
    root->h=maxx(Get_h(root->l),Get_h(root->r))+1;
    return root;
}


/*平衡二叉树的删除
1、按照二叉排序树的删除操作进行删除，再判断平衡性
2、同时判断是否有结点失衡，如果存在失衡结点，进行调整

*/
AVLNode* Delet(AVLNode* root,int x){
    if(root==NULL)
    {//空树无法删除
        printf("X IS NOT EXISTS");
        return root;
    } 
    if(x<root->data)
    {//在x的左子树中删除
        root->l=Delet(root->l,x);
        //root的左子树中删除一个节点，root有可能失衡--->RR/RL
        if(Get_h(root->r)-Get_h(root->l)>1)
        {//失衡了 RR/RL
            //具体判断root的右孩子的两棵子树谁更高
            if(Get_h(root->r->l)>Get_h(root->r->r))
            {//RL
                root=RLrotation(root);
            }
            else
            {//RR
                root=RRrotation(root);
            }
        }
    }
    if(x>root->data)
    {//在x的右子树中删除
        root->r=Delet(root->r,x);
        //root的右子树中删除一个节点，root有可能失衡--->LL/LR
        if(Get_h(root->l)-Get_h(root->r)>1)
        {//失衡了 LL/LR
            if(Get_h(root->l->r)>Get_h(root->l->l))
            {//LR
                root=LRrotation(root);
            }
            else
            {//LL
                root=LLrotation(root);
            }
        }
    }
    if(x==root->data)
    {//删除root,需要判断root的度
        if(root->l!=NULL&&root->r!=NULL)
        {//度为2
            //1、找出root的中序前驱，即x左子树中最靠右的结点
            AVLNode* y=root->l;
            while(y->r!=NULL){
                y=y->r;
            }
            //2、将root的中序前驱结点y替换root，并删除y
            root->data=y->data;
            root->l=Delet(root->l,y->data);
        }
        else
        {//度为0或1
            //直接让root指向root唯一可能存在的结点，删除root结点
            AVLNode* p=root;
            if(root->l!=NULL)root=root->l;
            else root=root->r;
            free(p);
            p=NULL;
        }
    }
    if(root!=NULL) root->h=maxx(Get_h(root->l),Get_h(root->r))+1; //更新一下root的高度
    return root;
}


void Order(AVLNode* root){
    if(root==NULL) return; //递归出口
    Order(root->l);
    printf("%d ",root->data);
    //中序序列可以体现出顺序性质，平衡性可以通过计算平衡因子表示
    int p=Get_h(root->l)-Get_h(root->r);
    printf("%d\n",p);
    Order(root->r);
}



int main(){
int n,x;
scanf("%d",&n);
AVLNode* root=NULL;
for(int i=0;i<n;i++){
    scanf("%d",&x);
    root=Insert(root,x);
}
Order(root);
Delet(root,14);
Order(root);

}



/*
9
8 3 10 1 6 14 4 7 13
*/