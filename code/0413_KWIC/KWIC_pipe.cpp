#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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
    void operator()(const vector<string>& kwic) {//创建一个ofstream对象outfile用于写入输出结果
        ofstream outfile(m_filename.c_str());//于每个字符串kwic[i]，将其写入到outfile中，并在末尾添加一个换行符。
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
