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

    void buildFromFile(const std::string &filename);
    void insertWord(const std::string &word);

    void printTopN(int n) const;
    std::vector<StringCount> getTopN(int n) const;
    int getTreeHeight() const;
    std::vector<StringCount> toVector() const;

};

#endif
