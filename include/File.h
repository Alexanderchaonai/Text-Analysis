#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>

// 选择文件路径
std::string selectFile();

// 读取全文内容，按行切分，放入 vector<string>
// max_chars 可限制最多读取多少字符（0 = 不限制）
std::vector<std::string> readFileLines(const std::string& path, int max_chars = 0);

#endif
