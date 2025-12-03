#include<iostream>
using namespace std;
struct BSTNode
{   
    int data;
    BSTNode *lchild,*rchild;
};  

//查找
BSTNode* Search(BSTNode *root,int x)//小了就往左子树继续，大了往右子树继续，直到找到了或者走到了NULL
{
    // while(root!=NULL)
    // {
    //     if(x<root->data)
    //         root=root->lchild;
    //     else if(x>root->data)
    //         root=root->rchild;
    //     else
    //         break;
    // }非递归写法
    if(root==NULL)
        return NULL;
    else if(x<root->data)
        return Search(root->lchild,x);
    else if(x>root->data)
        return Search(root->rchild,x);
    else
        return root;
}


void Insert(BSTNode *&root,int x)//加上引用符，就是对这个变量本身修改哈别忘了，函数内对root的修改在函数外也会生效
{
    if(root==NULL)
    {
        root = new BSTNode;
        root->data = x;
        root->lchild = root->rchild = NULL;
    }
    else if(x<root->data)
    {
        Insert(root->lchild,x);
    }
    else if(x>root->data)
    {
        Insert(root->rchild,x);
    }
    else{}
}

//二叉树的构建:依次对数组里的每个数进行插入操作
BSTNode * Create(int a[],int n)
{
    BSTNode *root = NULL;
    for(int i=0;i<n;i++)
    {
        Insert(root,a[i]);
    }
    return root;
}

BSTNode* FindMin(BSTNode* p)
{
    if (p == NULL) return NULL;
    while(p->lchild!=NULL)
    {
        p=p->lchild;
    }
    return p;
}
void Delete(BSTNode *&root,int x)//二叉树的删除,记得加引用符，因为删除之后根指针可能也需要变化
{
    if(root==NULL)
        return;
    if(x<root->data)
        Delete(root->lchild,x);
    else if(x>root->data)
        Delete(root->rchild,x);
    else//注意接下来要分四种情况，实际上是三种，左右字数均为空，直接删除，；左不空右空--左替代之
    //左空右不空--右替代之；左右子树均不空--前驱/后继值替换，并删除原来的前驱/后继
    {
        if(root->lchild==NULL&&root->rchild==NULL)
        {
            delete(root);//注意下，释放这个root只会释放root所占用的空间，不会让root自动指向NULL
            root=NULL;
            return;
        }
        else if(root->lchild!=NULL&&root->rchild==NULL)
        {
            BSTNode *temp = root;//确保指针可以提前备份需要删除的节点，方便后续删除
            root = root->lchild;
            delete(temp);
        }
        else if(root->lchild==NULL&&root->rchild!=NULL)
        {
            BSTNode *temp = root;//确保指针可以提前备份需要删除的节点，方便后续删除
            root = root->rchild;
            delete(temp);
        }
        else//此时，一定要找到该节点的直接前驱或者直接后继，注意是中序遍历下的哈，也就是左子树的最右边或者右子树的最左边
        {
            BSTNode *next = FindMin(root->rchild);
            root->data = next->data;
            Delete(root->rchild,next->data);//注意这一步至关重要，我们要做的是通过root->的右子树，递归的前往我们要删除的原本的后继节点，千万不能直接删除next
        }
    }
}