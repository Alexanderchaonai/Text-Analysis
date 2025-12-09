// src/TextSimilarity.cpp
#include "../include/TextSimilarity.h"
#include "../include/TextAnalyzer.h"
#include <unordered_map>
#include <vector>
#include <cmath>
#include <iostream>

static std::unordered_map<std::string, int> getFreqMap(const TextAnalyzer& analyzer)
{
    std::unordered_map<std::string, int> freq;
    std::vector<StringCount> vec = analyzer.toVector();
    for (const auto& item : vec)
        freq[item.str] = item.num;
    return freq;
}

double TextSimilarity::calculate(const TextAnalyzer& ta1, const TextAnalyzer& ta2)
{
    auto map1 = getFreqMap(ta1);
    auto map2 = getFreqMap(ta2);

    // 合并所有单词（并集）
    std::vector<std::string> words;
    words.reserve(map1.size() + map2.size());
    for (const auto& p : map1) words.push_back(p.first);
    for (const auto& p : map2)
        if (map1.find(p.first) == map1.end())
            words.push_back(p.first);

    // 计算余弦相似度
    double dot = 0.0, norm1 = 0.0, norm2 = 0.0;
    for (const std::string& w : words)
    {
        int f1 = map1[w];
        int f2 = map2[w];
        dot   += f1 * f2;
        norm1 += f1 * f1;
        norm2 += f2 * f2;
    }

    if (norm1 == 0.0 || norm2 == 0.0) return 0.0;
    return dot / (std::sqrt(norm1) * std::sqrt(norm2));
}

double TextSimilarity::calculate(const std::string& file1, const std::string& file2)
{
    TextAnalyzer ta1, ta2;

    ta1.buildFromFile(file1);
    ta2.buildFromFile(file2);

    
    if (ta1.getTreeHeight() == 0)
        std::cerr << "[Warning] 无法读取或文件为空: " << file1 << std::endl;
    if (ta2.getTreeHeight() == 0)
        std::cerr << "[Warning] 无法读取或文件为空: " << file2 << std::endl;

    if (ta1.getTreeHeight() == 0 && ta2.getTreeHeight() == 0)
        return (file1 == file2) ? 1.0 : 0.0;

    return calculate(ta1, ta2);
}