#ifndef WORDFREQTREE_H
#define WORDFREQTREE_H

#include <string>
#include <vector>

struct StringCount
{
    std::string str;
    int num;
};

struct AVLNode
{
    std::string word;
    int count;
    int height;
    AVLNode *left, *right;

    AVLNode(const std::string &w)
    {
        word = w;
        count = 1;
        height = 1;
        left = right = nullptr;
    }
};

class WordFreqTree
{
private:
    AVLNode *root;

private:
    int height(AVLNode *p)const;
    int getBalance(AVLNode *p)const;
    AVLNode* rightRotate(AVLNode *y);
    AVLNode* leftRotate(AVLNode *x);
    AVLNode* insertNode(AVLNode *node, const std::string &w);
    void inorderToVector(AVLNode *node, std::vector<StringCount> &vec) const;

public:
    WordFreqTree() { root = nullptr; }

    void Insert(const std::string &w);
    std::vector<StringCount> toVector() const;
    int getHeight() const;
    AVLNode* GetRoot() const { return root; }

};

#endif
