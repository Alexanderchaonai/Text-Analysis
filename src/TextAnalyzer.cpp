#include "../include/TextAnalyzer.h"
#include "../include/Tokenizer.h"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

// ===========================
//  构建树：从文件读取 + 分词
// ===========================
void TextAnalyzer::buildFromFile(const std::string &filename)
{
    ifstream fin(filename);
    if (!fin.is_open())
    {
        cerr << "open file error: " << filename << "\n";
        return;
    }

    string line;
    while (getline(fin, line))
    {
        auto words = tokenize(line);
        for (auto &w : words)
            tree.Insert(w);
    }

    fin.close();
}

//   手动插入一个单词（测试用）
void TextAnalyzer::insertWord(const std::string &word)
{
    tree.Insert(word);
}

//   打印 Top-N 高频词
void TextAnalyzer::printTopN(int n) const
{
    vector<StringCount> vec = tree.toVector();

    // 按频率降序排列
    sort(vec.begin(), vec.end(),
         [](const StringCount &a, const StringCount &b) {
             if (a.num != b.num) return a.num > b.num;
             return a.str < b.str;
         });

    int cnt = 0;
    for (auto &p : vec)
    {
        cout << p.str << " : " << p.num << "\n";
        if (++cnt >= n) break;
    }
}

//   获得 AVL 树的高度
int TextAnalyzer::getTreeHeight() const
{
    return tree.getHeight();
}
