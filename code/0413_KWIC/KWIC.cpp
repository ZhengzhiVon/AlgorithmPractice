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