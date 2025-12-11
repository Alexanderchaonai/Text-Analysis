#ifndef TEXTANALYZER_H
#define TEXTANALYZER_H

#include <string>
#include "WordFreqTree.h"

class TextAnalyzer
{
private:
    WordFreqTree tree;

public:
    TextAnalyzer() {}

    //返回文本的函数，放在vector里面，限制输入文本的字数，
    //允许用户选择电脑中的文本路径，选择文本，就是先select再buildfromfile
    void buildFromFile(const std::string &filename);
    void insertWord(const std::string &word);

    void printTopN(int n) const;
    std::vector<StringCount> getTopN(int n) const;

    int getTreeHeight() const;
    std::vector<StringCount> toVector() const;

};

#endif
