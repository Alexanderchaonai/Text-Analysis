#include <iostream>
#include "../include/TextAnalyzer.h"
using namespace std;

int main()
{
    TextAnalyzer analyzer;

    // 测试一：手动插入词
    analyzer.insertWord("apple");
    analyzer.insertWord("banana");
    analyzer.insertWord("apple");

    cout << "树的高度: " << analyzer.getTreeHeight() << endl;
    cout << "Top 3:" << endl;
    analyzer.printTopN(3);

    // 测试二：从文件加载
    analyzer.buildFromFile("test.txt");
    cout << "\n从 test.txt 加载后:" << endl;

    cout << "树的高度: " << analyzer.getTreeHeight() << endl;
    analyzer.printTopN(10);

    return 0;
}
