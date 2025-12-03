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
    int getTreeHeight() const;

    // AVL 不再需要 getFrequencyMap()
};

#endif
