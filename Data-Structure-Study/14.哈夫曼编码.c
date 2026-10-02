#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Node{
    int w;//权值
    int f;//父亲下标
    int l,r;//左右孩子，用于编码操作
}HuffmanNode;
//查找函数
void Find(int* s1,int* s2,int m,HuffmanNode *tree){
    //1、让s1指向0~m中权值最小的根节点(根节点就是f==-1的结点)
    for(int i=0;i<m;i++)
    {//让s1指向树中任意根节点
    //为什么呢？因为如果s1==0，恰好0不是根节点，而且tree[0].w<tree[i].w就不会触发更新判断
        if(tree[i].f==-1)
        {
            *s1=i;
            break;
        }
    }
    for(int i=0;i<m;i++)
    {//不断更新s1的值
        if(tree[i].f==-1&&tree[i].w<tree[*s1].w)
        {//让s1指向权值更小的根节点
            *s1=i;
        }
    }
    //2、让s1指向0~m中权值第二小的根节点(根节点就是f==-1的结点)
    for(int i=0;i<m;i++)
    {//让s2指向除了s1之外的任意根节点
    //为什么呢？这个更好理解了，如果s2一开始就==s1的话，就不存在i使得tree[i].w<tree[*s2]，更新判断同样不会触发
        if(tree[i].f==-1&&i!=*s1)
        {
            *s2=i;
            break;
        }
    }
    for(int i=0;i<m;i++)
    {//不断更新s2的值
        if(tree[i].f==-1&&tree[i].w<tree[*s2].w&&i!=(*s1))
        {//让s2指向权值更小的根节点
            *s2=i;
        }
    }
}

//1、建树
HuffmanNode* CreatHuffmanTree(int n,int w[])
{//将n个节点作为叶子节点存放在哈夫曼树中
    //1、开辟哈夫曼树数组：那么哈夫曼树数组需要开多大空间呢？m=2n-1
    int m=2*n-1;
    HuffmanNode* tree=(HuffmanNode*)malloc(sizeof(HuffmanNode)*m);
    //2、为将n个叶子节点权值放入树中
    for(int i=0;i<n;i++){
        tree[i].w=w[i];
        tree[i].f=-1;
        tree[i].l=tree[i].r=-1;
    }
    //3、进行合并
    for(int i=n;i<m;i++)
    {//此时已经在下标0~n-1中存储了结点，需要在n~m-1中存储合并了的结点
        //1)查找当前数组中权值最小的两个结点的下标
        int s1,s2;
        Find(&s1,&s2,m,tree);
        //2)将合并后权值最小的两个结点进行合并
        tree[i].w=tree[s1].w+tree[s2].w;
        tree[i].f=-1;
        tree[i].l=s1;
        tree[i].r=s2;
        tree[s1].f=tree[s2].f=i;
    }
    return tree;
}

//2、哈夫曼编码
char** CreateCode(HuffmanNode*Tree,int n){
    //开辟一个临时数组临时存储编码
    char* temp=(char*)malloc(sizeof(char)*n);
    //二维指针模拟开二维数组，用来存放n个密码
    char** codes=(char**)malloc(sizeof(char*)*n);

    //将存放编码的字符串数组的指针分别传递到指针数组中
    for(int i=0;i<n;i++){
        //1、从叶子节点开始向上直到根节点
        int p=i,pre=Tree[p].f;//p指向根节点，pre指向p的父亲节点
        //因为是从叶子节点向上查找，而密码是从根节点向下解开，所以存入数组的过程中，必须倒序存储，因为temp[n-1]位置是'\0'，所以start从n-2位置开始
        int start=n-2;
        temp[n-1]='\0';
        while(Tree[p].f!=-1)
        {//从叶子节点开始，遍历到根节点。如果
            if(p==Tree[pre].l)temp[start]='1';//p是其父亲的左孩子,编码为1
            else temp[start]='0';//p是其父亲的右子,编码为0
                start--;
            p=pre;
            pre=Tree[p].f;
        }
        //最后得出的编码长度为多少？len=n-start-1
        int len=n-start-1;
        char* code=(char*)malloc(sizeof(char)*len);
        strcpy(code,&temp[start+1]);
        codes[i]=code;
    }
    return codes;
}


int main(){
    int n;
    scanf("%d",&n); //对n个字符进行编码
    getchar();
    char a[105];//存放字符
    int w[105];
    for(int i=0;i<n;i++)
    {//输入要要编码的n个字符
        scanf("%c",&a[i]);
    }
    for(int i=0;i<n;i++){
        scanf("%d",&w[i]);
    }
    //建树
    HuffmanNode*Tree=CreatHuffmanTree(n,w);
    //哈夫曼编码：用二维指针开的二维数组来存储 优点：数组长度不一定一样
    char** HuffmanCode=CreateCode(Tree,n);

    for(int i=0;i<n;i++)
    {//打印所有结果
        printf("%c:%s\n",a[i],HuffmanCode[i]);
    }




//我在想能不能w[105]和a[105]能不能动态内存分配


}

/*
9
agmteh is
1 1 1 1 2 2 3 3 5    
*/