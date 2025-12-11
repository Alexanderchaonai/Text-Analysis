#include "../include/File.h"
#include <windows.h>
#include <fstream>
#include <sstream>

// 文件选择对话框
std::string selectFile()
{
    OPENFILENAMEA ofn;
    char fileName[MAX_PATH] = {0};

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFilter = "Text Files\0*.txt\0All Files\0*.*\0";
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

    if (GetOpenFileNameA(&ofn))
        return std::string(fileName);

    return "";
}

// 读取文件内容并按行返回
std::vector<std::string> readFileLines(const std::string& path, int max_chars)
{
    std::ifstream fin(path);
    std::vector<std::string> lines;

    if (!fin.is_open())
    {
        lines.push_back(std::string("[Error] Cannot open file: ") + path);
        return lines;
    }

    std::string line;
    int count_char = 0;

    while (std::getline(fin, line))
    {
        if (max_chars > 0)
        {
            if (count_char + line.size() > max_chars)
                break;
            count_char += line.size();
        }
        lines.push_back(line);
    }

    return lines;
}
