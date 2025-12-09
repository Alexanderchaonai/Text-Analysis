// include/TextSimilarity.h
#ifndef TEXT_SIMILARITY_H
#define TEXT_SIMILARITY_H

#include "TextAnalyzer.h"
#include <string>

class TextSimilarity
{
public:
    static double calculate(const std::string& file1, const std::string& file2);
    static double calculate(const TextAnalyzer& ta1, const TextAnalyzer& ta2);
};

#endif // TEXT_SIMILARITY_H