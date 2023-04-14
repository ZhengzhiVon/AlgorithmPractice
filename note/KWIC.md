# KWIC(Key Word in Context）

**`KWIC`索引系统接受一些行，每行有若干字，每个字由若干字符组成；每行都可以循环移位，亦即重复地把第一个字删除，然后接到行末； `KWIC`把所有行的各种移位情况按照字母表顺序输出.**

## 主程序子程序风格

 

![image-20230413160351904](C:\Users\VoN\AppData\Roaming\Typora\typora-user-images\image-20230413160351904.png)





```c++
#include<iostream>
#include<string>
#include<set>
#include<vector>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>

using namespace std;
//移动行
//输出有序序列

vector<string> InPut(const char* filename,vector<string>& vv)
{
    ifstream file(filename);
    if(file.is_open()){
        string line;
        while(getline(file,line)){
            vv.push_back(line);
        }
        file.close();
    }
    return vv;

    /*
    FILE* fp = fopen(filename, "r+");
    if (fp == nullptr)
    {
        printf("文件打开失败！\n");
        exit(1);
    }
    char buff[256] = { 0 };
    while (!feof(fp))
    {
        fgets(buff, 255, fp);
        string tmp(buff);//将buff数组中的内容转换成string类型的tmp字符串
        tmp.pop_back();//删除字符串末尾的换行符
        vv.push_back(move(tmp));//使用vector的push_back函数将tmp字符串存储到vv中。
    }

    fclose(fp);
    */
}

void Circular_Shifter(vector<string>& vv, set<string>& ss)//变换&排序
{
    for (int i = 0;i < vv.size();i++)
    {
        string tmp = vv[i];//将当前行的内容存储到tmp字符串中。
        while (ss.find(tmp) == ss.end())//使用while循环不断进行循环移位操作，直到所有可能的移位结果都被存储到ss中。
        {
            ss.insert(tmp);
            for (int i = 0;i < tmp.size() && tmp[i] != ' ';i++)
            {
                if (i == 0)tmp.push_back(' ');

                tmp.push_back(tmp[i]);
            }
            //在循环移位操作中，首先使用set的find函数查找当前字符串是否已经被存储到ss中，如果没有，则将其插入到ss中。
            auto begin = tmp.begin();
            auto last = begin;
            for (;*last != ' ';)
            {
                last++;
            }
            if (*last == ' ')last++;
            tmp.erase(begin, last);
            //使用for循环遍历tmp字符串中的每一个字符，如果当前字符是第一个字符，则在字符串末尾添加一个空格。接着，将当前字符添加到字符串末尾。最后，使用auto关键字定义begin和last迭代器，并使用for循环找到第一个空格字符的位置，然后将begin到last之间的内容从tmp字符串中删除。
        }
    }
}

void OutPut(const char *filename,set<string>& ss)//输出
{
    for (auto& x : ss)
    {
        std::cout << x << std::endl;
    }
    
    /*std::ofstream swrite(string(filename), ostream::app);
    for (auto& len : ss)
    {
        swrite << len << endl;
    }
    swrite.close();*/
}
int main()
{
    vector<string> vv;
    InPut("input.txt",vv);

    set<string> ss;
    Circular_Shifter(vv,ss);
    
    OutPut("b.txt",ss);
    
    return 0;
}
```



https://www.cnblogs.com/qhong/p/7856157.html

https://www.cnblogs.com/youxin/p/3514594.html

https://cn.bing.com/search?q=KWIC%E9%97%AE%E9%A2%98&search=&form=QBLH



## 管道过滤器风格

```c++
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class InputFilter {
public:
    InputFilter(const string& filename) : m_filename(filename) {}//构造函数，初始化需要读取的文件
    vector<string> operator()() {
        vector<string> words;
        ifstream infile(m_filename.c_str());//C++中不接受string对象作为文件名，可以用方法c_str()返回一个C风格的字符串
        string line;
        while (getline(infile, line)) {//读取文件中每一行的内容至流迭代器infile中
            string word;
            for (int i = 0; i < line.size(); i++) {//将每一行分解成单词，并将每个单词添加到 "words" 容器中。
                if (isspace(line[i])) {
                    if (!word.empty()) {
                        words.push_back(word);
                        word.clear();
                    }
                } else {
                    word += line[i];
                }
            }
            if (!word.empty()) {
                words.push_back(word);
            }
        }
        return words;
    }
private:
    string m_filename;
};

class TransformFilter {//将输入的字符串向量进行循环移位，并按字典序排序后返回。
public:
    vector<string> operator()(const vector<string>& words) {
        vector<string> kwic;//存储循环移位后的结果
        for (int i = 0; i < words.size(); i++) {
            string line;
            for (int j = i; j < words.size() + i; j++) {//对于每个j，将j % words.size()作为下标取出words中的单词，拼接到line字符串中，并在单词之间添加一个空格。
                int k = j % words.size();
                line += words[k] + " ";
            }
            kwic.push_back(line);//循环移位完成后，将line字符串添加到kwic容器中。
        }
        sort(kwic.begin(), kwic.end());//排序
        return kwic;
    }
};

class OutputFilter {
public:
    OutputFilter(const string& filename) : m_filename(filename) {}//构造函数，初始化最终需要输出的文件
    void operator()(const vector<string>& kwic) {
        ofstream outfile(m_filename.c_str());
        for (int i = 0; i < kwic.size(); i++) {
            outfile << kwic[i] << endl;
        }
    }
private:
    string m_filename;
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " input_file output_file" << endl;
        return 1;
    }
    InputFilter input_filter(argv[1]);
    TransformFilter transform_filter;
    OutputFilter output_filter(argv[2]);
    vector<string> words = input_filter();
    vector<string> kwic = transform_filter(words);
    output_filter(kwic);
    return 0;
}
```

