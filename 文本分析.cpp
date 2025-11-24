#include<iostream>
#include<vector>
#include<fstream>
#include<string>
using namespace std;
struct StringCount
{
    string str;//单词本身
    int num;//出现次数
};
vector <StringCount> WordList; 

int FindWord(const string& word)
{
    for(int i = 0;i<WordList.size();i++)
    {
        if(WordList[i].str==word)
        {
            return i;
        }
    }
    return -1;
}
//从一行字符串中提取单词
int div_word(const string& line)
{
    string word = "";
    for(char c:line)
    {
        if(isalnum(c))//如果是数字或者字母，，就加到word里面
        {
            word+=tolower(c);
        }
        else//遇到分隔符
        {
            if(!word.empty())//如果此时单词不为空
            {
                int pos = FindWord(word);
                if(pos==-1)
                {
                    WordList.push_back({word,1});
                }
                else
                {
                    WordList[pos].num++;
                }
                word.clear();
            }
        }
    }
    // 最后一个单词处理
    if (!word.empty())
    {
        int pos = FindWord(word);
        if (pos == -1)
            WordList.push_back({word, 1});
        else
            WordList[pos].num++;
    }
}
int main()
{
    string filename;
    cout<<"请输入文件名:";
    cin>>filename;
    ifstream fin(filename);
    string line;
    while (getline(fin, line))
    {
        div_word(line);
    }
    fin.close();
    // 输出结果
    cout << "\n=== 单词统计结果 ===\n";
    for (auto &item : WordList)
    {
        cout << item.str << " : " << item.num << endl;
    }   
    return 0;
}