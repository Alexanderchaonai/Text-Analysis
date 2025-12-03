#include "../include/WordFreqTree.h"
#include <algorithm>

// 计算高度
int WordFreqTree::height(AVLNode *p) const
{
    if(p == NULL) return 0;
    return p->height;
}

// 平衡因子
int WordFreqTree::getBalance(AVLNode *p) const
{
    if(p == NULL) return 0;
    return height(p->left) - height(p->right);
}

// 右旋
AVLNode* WordFreqTree::rightRotate(AVLNode *y)
{
    AVLNode *x = y->left;
    AVLNode *t2 = x->right;

    x->right = y;
    y->left = t2;

    int hl = height(y->left);
    int hr = height(y->right);
    if(hl > hr) y->height = hl + 1;
    else y->height = hr + 1;

    hl = height(x->left);
    hr = height(x->right);
    if(hl > hr) x->height = hl + 1;
    else x->height = hr + 1;

    return x;
}

// 左旋
AVLNode* WordFreqTree::leftRotate(AVLNode *x)
{
    AVLNode *y = x->right;
    AVLNode *t2 = y->left;

    y->left = x;
    x->right = t2;

    int hl = height(x->left);
    int hr = height(x->right);
    if(hl > hr) x->height = hl + 1;
    else x->height = hr + 1;

    hl = height(y->left);
    hr = height(y->right);
    if(hl > hr) y->height = hl + 1;
    else y->height = hr + 1;

    return y;
}

// 插入
AVLNode* WordFreqTree::insertNode(AVLNode *node, const std::string &w)
{
    if(node == NULL){
        AVLNode *p = new AVLNode(w);
        return p;
    }

    if(w < node->word){
        node->left = insertNode(node->left, w);
    }
    else if(w > node->word){
        node->right = insertNode(node->right, w);
    }
    else{
        node->count++;
        return node;
    }

    int hl = height(node->left);
    int hr = height(node->right);
    if(hl > hr) node->height = hl + 1;
    else node->height = hr + 1;

    int balance = getBalance(node);

    if(balance > 1 && w < node->left->word){
        return rightRotate(node);
    }

    if(balance < -1 && w > node->right->word){
        return leftRotate(node);
    }

    if(balance > 1 && w > node->left->word){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if(balance < -1 && w < node->right->word){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void WordFreqTree::Insert(const std::string &w)
{
    root = insertNode(root, w);
}

void WordFreqTree::inorderToVector(AVLNode *node, std::vector<StringCount> &vec) const
{
    if(node == NULL) return;

    inorderToVector(node->left, vec);

    StringCount sc;
    sc.str = node->word;
    sc.num = node->count;
    vec.push_back(sc);

    inorderToVector(node->right, vec);
}

std::vector<StringCount> WordFreqTree::toVector() const
{
    std::vector<StringCount> v;
    inorderToVector(root, v);
    return v;
}

int WordFreqTree::getHeight() const
{
    return height(root);
}
