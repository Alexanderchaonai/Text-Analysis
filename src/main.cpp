#include<iostream>
#include"File.h"
#include"easyx.h"
#include"graphics.h"
#include "TextAnalyzer.h"
#include "Tokenizer.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include"string.h"
#include "TextSimilarity.h"
#include <iomanip>
#include<regex>
#include<vector>
using namespace std;
TextAnalyzer analyzer;
IMAGE image_tu;
double sim = 0;
int i = 0, j = 0;
std::string path,path2;
std::vector<std::string> lines,lines2;
ExMessage msg = { 0 };
std::vector<std::string> splitByEnglishPunct(const std::string& text)
{
    std::regex re(R"([,.\!?;:])");
    std::sregex_token_iterator it(text.begin(), text.end(), re, { -1, 0 }), end;
    std::vector<std::string> clauses;
    std::string sent;
    for (; it != end; ++it) {
        std::string s = it->str();
        s = std::regex_replace(s, std::regex(R"(^\s+|\s+$)"), "");
        if (s.empty()) continue;
        // ����Ǳ���ƴ��ǰһ�����
        if (std::regex_match(s, std::regex(R"([,.\!?;:])"))) {
            if (!sent.empty()) sent += s;
        }
        else {
            if (!sent.empty()) clauses.push_back(sent);
            sent = s;   // �¾俪ʼ
        }
    }
    if (!sent.empty()) clauses.push_back(sent);
    return clauses;
}
//mx��my�Ƿ���ָ����������
bool inArea(int mx, int my, int x, int y, int w, int h) {
    if (mx > x && mx<x + w && my>y && my < y + h) {
        return true;
    }
    return false;
}
bool button(int x, int y, int w, int h, const char* text, int fontHeight = 40) {
    //���ư�ť
    setlinecolor(BLACK);
    rectangle(x, y, x + w, y + h);
    settextstyle(fontHeight, 0, "΢���ź�");
    setbkmode(TRANSPARENT);
    //���ư�ť�ı�
    int hSpace = (w - textwidth(text)) / 2;
    int vSpace = (h - textheight(text)) / 2;
    settextcolor(GREEN);
    outtextxy(x + hSpace, y + vSpace, text);
    //�жϰ�ť�Ƿ񱻵��
    if (msg.message == WM_LBUTTONDOWN && inArea(msg.x, msg.y, x, y, w, h)) {
        return true;
    }
    return false;
}
bool button1(int x, int y, int w, int h, const char* text, int fontHeight = 40) {
    //���ư�ť
    setlinecolor(RED);
    rectangle(x, y, x + w, y + h);
    settextstyle(fontHeight, 0, "΢���ź�");
    setbkmode(TRANSPARENT);
    //���ư�ť�ı�
    int hSpace = (w - textwidth(text)) / 2;
    int vSpace = (h - textheight(text)) / 2;
    settextcolor(RED);
    outtextxy(x + hSpace, y + vSpace, text);
    //�жϰ�ť�Ƿ񱻵��
    if (msg.message == WM_LBUTTONDOWN && inArea(msg.x, msg.y, x, y, w, h)) {
        return true;
    }
    return false;
}
enum PAGE {
    PAGE_MAIN = 0,
    PAGE_TEXT1,
    PAGE_TEXT2,
    PAGE_SHUGAO,
    PAGE_GAOPCI,
    PAGE_WBSIM,
    PAGE_EXIT
};
PAGE pageMain() {
    BeginBatchDraw();
    loadimage(&image_tu, "assets/tu1.jpg");
    putimage(0, 0, &image_tu);
    if (button(96, 120, 200, 55, "ѡ���ı�1")) {
        return PAGE_TEXT1;
    }
    if (button(96, 190, 200, 55, "ѡ���ı�2")) {
        return PAGE_TEXT2;
    }
    if (button(96, 260, 200, 55, "����")) {
        return PAGE_SHUGAO;
    }
    if (button(96, 330, 200, 55, "��Ƶ��")) {
        return PAGE_GAOPCI;
    }
    if (button(96, 400, 200, 55, "�ı����ƶ�")) {
        return PAGE_WBSIM;
    }
    if (button1(96, 470, 200, 55, "����")) {
        return PAGE_EXIT;
    }
    EndBatchDraw();
    return PAGE_MAIN;
}
PAGE pageText1() {
    if (i == 0) {
        path = selectFile();
        if (path.empty())
            return PAGE_TEXT1;
        i++;
    }
    BeginBatchDraw();
    cleardevice();// ��������
    loadimage(&image_tu, "assets/tu2.jpg");
    putimage(0, 0, &image_tu);
    ifstream fin(path);
    if (!fin.is_open())
    {
        settextstyle(60, 0, "΢���ź�");
        settextcolor(RED);
        outtextxy(50, 0, "��open file error��");
    }
    else{
        settextstyle(60, 0, "΢���ź�");
        settextcolor(GREEN);
        outtextxy(56, 0, "�����سɹ���");
        std::vector<std::string>lines = readFileLines(path);
        settextstyle(16, 0, "΢���ź�");
        settextcolor(BLACK);
        std::vector<std::string> clauses = splitByEnglishPunct(lines[0]);
        int y = 60;
        for (size_t i = 0; i < clauses.size(); ++i) {
            outtextxy(10, y + i * 25, clauses[i].c_str());
            if (y + (i + 1) * 25 > 560) break;   // ���߱���
        }
    }
    if (button1(96, 470, 200, 55, "����")) return PAGE_MAIN;
    EndBatchDraw();
    return PAGE_TEXT1;
}
PAGE pageText2()
{
    if (j == 0) {
        path2 = selectFile();
        if (path.empty())
            return PAGE_TEXT2;
        j++;
    }
    j++;
    BeginBatchDraw();
    cleardevice();
    loadimage(&image_tu, "assets/tu3.jpg");
    putimage(0, 0, &image_tu);
    if(sim==0){
        settextstyle(60, 0, "΢���ź�");
        settextcolor(RED);
        outtextxy(56, 30, "������ʧ�ܡ�");
    }
    else {
        settextstyle(60, 0, "΢���ź�");
        settextcolor(GREEN);
        outtextxy(56, 0, "�����سɹ���");
        std::vector<std::string>lines2 = readFileLines(path2);
        int x0 = 10;
        int y0 = 20;
        int linesPerBlock = 10;
        int lineH = 25;
        settextstyle(16, 0, "΢���ź�");
        settextcolor(BLACK);
        std::vector<std::string> clauses = splitByEnglishPunct(lines2[0]);
        int y = 60;
        for (size_t i = 0; i < clauses.size(); ++i) {
            outtextxy(10, y + i * 25, clauses[i].c_str());
            if (y + (i + 1) * 25 > 560) break;   // ���߱���
        }
    }
    if (button1(96, 470, 200, 55, "����")) return PAGE_MAIN;
    EndBatchDraw();
    return PAGE_TEXT2;
}
PAGE pageShugao() {
    BeginBatchDraw();
    cleardevice();
    loadimage(&image_tu, "assets/tu4.jpg");
    putimage(0, 0, &image_tu);
    if (i > 0) {
        settextstyle(50, 0, "΢���ź�");
        settextcolor(BLACK);
        int h = analyzer.getTreeHeight();
    std:string txt = "���ĸ߶ȣ�" + std::to_string(h);
        outtextxy(90, 50, txt.c_str());
    }
    else {
        settextstyle(60, 0, "΢���ź�");
        settextcolor(RED);
        if (button(96, 120, 200, 55, "��ѡ���ı�1")) {
            return PAGE_TEXT1;
        }
    }
    if (button1(96, 470, 200, 55, "����")) return PAGE_MAIN;
    EndBatchDraw();
    return PAGE_SHUGAO;
}

PAGE pageGaopci() {
    BeginBatchDraw();
    cleardevice();
    loadimage(&image_tu, "assets/tu5.jpg");
    putimage(0, 0, &image_tu);
    if (i > 0) {
        settextstyle(60, 0, "΢���ź�");
        settextcolor(RED);
    std:string txt = "Top 10 ��Ƶ��";
        outtextxy(40, 0, txt.c_str());
        settextstyle(30, 0, "΢���ź�");
        settextcolor(BLACK);
        auto top = analyzer.getTopN(10);
        for (size_t i = 0; i < top.size(); ++i) {
            std::string wenb = top[i].str + " :  " + std::to_string(top[i].num);
            outtextxy(120, 35 * i + 70, wenb.c_str());
        }
    }
    else {
        settextstyle(60, 0, "΢���ź�");
        settextcolor(RED);
        if (button(96, 120, 200, 55, "��ѡ���ı�1")) {
            return PAGE_TEXT1;
        }
    }
    if (button1(96, 470, 200, 55, "����")) return PAGE_MAIN;
    EndBatchDraw();
    return PAGE_GAOPCI;
}
PAGE pageWbsim() {
    BeginBatchDraw();
    cleardevice();
    loadimage(&image_tu, "assets/tu6.jpg");
    putimage(0, 0, &image_tu);
    if (i > 0&&j>0) {
        settextstyle(50, 0, "΢���ź�");
        settextcolor(BLACK);
        std::string txt1 = "�ı����ƶ� " + std::to_string(sim);
        outtextxy(20, 50, txt1.c_str());
    }
    else {
        if (i == 0 && j == 0) {
            settextstyle(60, 0, "΢���ź�");
            settextcolor(RED);
            if (button(96, 120, 200, 55, "��ѡ���ı�1")) {
                return PAGE_TEXT1;
            }
            if (button(96, 190, 200, 55, "ѡ���ı�2")) {
                return PAGE_TEXT2;
            }
        }
        if (i == 0&&j!=0) {
            settextstyle(60, 0, "΢���ź�");
            settextcolor(RED);
            if (button(96, 120, 200, 55, "��ѡ���ı�1")) {
                return PAGE_TEXT1;
            }
        }
        if (j == 0&&i!=0) {
            settextstyle(60, 0, "΢���ź�");
            settextcolor(RED);
            if (button(96, 190, 200, 55, "ѡ���ı�2")) {
                return PAGE_TEXT2;
            }
        }
    }
    if (button1(96, 470, 200, 55, "����")) return PAGE_MAIN;
    EndBatchDraw();
    return PAGE_WBSIM;
}

int main() {
    sim = TextSimilarity::calculate("D:\\VirtualC\\vs2022\\DaiMa\\XiangMu\\XiangMu\\test.txt", "D:\\VirtualC\\vs2022\\DaiMa\\XiangMu\\XiangMu\\text2.txt");
    analyzer.buildFromFile("D:\\VirtualC\\vs2022\\DaiMa\\XiangMu\\XiangMu\\test.txt");
    initgraph(392, 588, EX_SHOWCONSOLE | EX_DBLCLKS);
    cleardevice();//����
    loadimage(&image_tu, "assets/tu1.jpg");
    putimage(0, 0, &image_tu);
    PAGE currentPage = PAGE_MAIN;       // �����˵���ʼ
    while (true)
    {
        // 1. ȡ��Ϣ
        while (peekmessage(&msg, EX_MOUSE));

        // 2. ���ݵ�ǰҳ����ö�Ӧ�������õ���һҳ
        switch (currentPage)
        {
        case PAGE_MAIN:  currentPage = pageMain();  break;
        case PAGE_TEXT1: currentPage = pageText1(); break;
        case PAGE_TEXT2: currentPage = pageText2(); break;
        case PAGE_SHUGAO:currentPage = pageShugao(); break;
        case PAGE_GAOPCI:currentPage = pageGaopci(); break;
        case PAGE_WBSIM:currentPage = pageWbsim(); break;
        case PAGE_EXIT:  closegraph(); return 0;
        }

        msg.message = 0;
        Sleep(16);
    }
    
    return 0;
}