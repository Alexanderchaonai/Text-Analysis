# 文本词频统计与文本相似度分析系统（基于 AVL 树）

本项目为《程序设计综合实践》课程设计，实现一个基于 **AVL 树** 的文本词频统计与文本相似度分析系统，并预留接口给 EasyX 图形界面进行可视化展示。

---

## 一、项目功能简介

- 从文本文件中读取英文文本内容  
- 对文本进行简单分词（仅保留字母，全部转为小写）  
- 使用 AVL 树存储单词及出现频次  
- 支持 Top-N 高频词统计  
- 提供接口支持文本相似度计算（如余弦相似度）  
- 可接入 EasyX 图形界面实现图形可视化  

---

## 二、项目目录结构

```
文本分析/
│
├── include/                   # 头文件
│   ├── TextAnalyzer.h         # 文本分析器（词频统计 + TopN）
│   ├── Tokenizer.h            # 分词器
│   └── WordFreqTree.h         # AVL 树（用于统计词频）
│
├── src/                       # 源文件
│   ├── TextAnalyzer.cpp       # 实现文本分析逻辑
│   ├── Tokenizer.cpp          # 实现分词逻辑
│   ├── WordFreqTree.cpp       # AVL 树实现
│   └── test_main.cpp          # 测试 main（非最终版）
│
├── BST.cpp                    # 普通二叉搜索树
│
├── text.txt                   # 测试用文本文件（可保留）
│
├── README.md                  # 项目说明文档（已生成）
│
└── .gitignore                 # Git 忽略规则（避免上传 exe/.vscode 等）


---

## 三、模块说明

### 1. 词频统计（WordFreqTree —— AVL 树）

- 节点结构包含：
  - 单词 `word`
  - 出现次数 `count`
  - 子树高度 `height`
  - 左右子树指针

- 对外接口：
  ```cpp
  void Insert(const std::string &word);
  std::vector<StringCount> toVector() const;
  int getHeight() const;
  ```

---

### 2. 文本分析器（TextAnalyzer）

功能：

- 从文件读取文本
- 分词
- 插入 AVL 树统计词频
- 输出 Top-N 高频词

接口：

```cpp
void buildFromFile(const std::string &filename);
void insertWord(const std::string &word);
void printTopN(int n) const;
int getTreeHeight() const;
```

---

### 3. 分词器（Tokenizer）

功能：

- 去除非字母字符
- 转小写
- 返回单词数组

接口：

```cpp
std::vector<std::string> tokenize(const std::string &text);
```

---

## 四、编译与运行方式

在项目根目录执行：

```bash
g++ src/*.cpp -Iinclude -o TextAnalyzer.exe
```

运行：

```bash
./TextAnalyzer.exe
```

测试文本请放在：

```
text/text1.txt
```

或使用正确路径。

---

## 五、小组分工（示例）

- **成员 A：AVL 树与词频统计模块**
  - 负责 AVL 树节点设计、插入逻辑、平衡调整  
  - 实现 `WordFreqTree` + `TextAnalyzer` 模块  

- **成员 B：文本相似度计算**
  - 基于词频向量计算文本相似度（如余弦相似度）  
  - 为 EasyX 界面提供相似度结果  

- **成员 C：图形界面（EasyX）**
  - 使用 EasyX 绘制窗口、按钮、文本框  
  - 显示 Top-N 高频词（列表或柱状图）  
  - 调用 `TextAnalyzer` 进行文本加载与分析  

## 六、项目说明

本项目重点在于：

- 使用 AVL 树保证单词插入和查询均为 O(log n)  
- 词频统计准确、可视化方便  
- 模块化设计，便于扩展成 GUI 版本或加入相似度分析  

本项目文件结构清晰，易于维护，适合作为课程设计或文本分析入门项目。

