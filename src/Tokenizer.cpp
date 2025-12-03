#include "../include/Tokenizer.h"
#include <cctype>
std::vector<std::string> tokenize(const std::string &text)
{
    std::vector<std::string> res;
    std::string cur;
    for(char ch: text)
    {
        if(std::isalpha((unsigned char)ch))
        {
            cur.push_back(std::tolower((unsigned char)ch));
        }
        else
        {
            if(!cur.empty())
            {
                res.push_back(cur);
                cur.clear();
            }
        }
    }
    if(!cur.empty()) res.push_back(cur);
    return res;
}
