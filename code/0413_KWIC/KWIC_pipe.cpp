#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class InputFilter {
public:
    InputFilter(const string& filename) : m_filename(filename) {}
    vector<string> operator()() {
        vector<string> words;
        ifstream infile(m_filename.c_str());
        string line;
        while (getline(infile, line)) {
            string word;
            for (int i = 0; i < line.size(); i++) {
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

class TransformFilter {
public:
    vector<string> operator()(const vector<string>& words) {
        vector<string> kwic;
        for (int i = 0; i < words.size(); i++) {
            string line;
            for (int j = i; j < words.size() + i; j++) {
                int k = j % words.size();
                line += words[k] + " ";
            }
            kwic.push_back(line);
        }
        sort(kwic.begin(), kwic.end());
        return kwic;
    }
};

class OutputFilter {
public:
    OutputFilter(const string& filename) : m_filename(filename) {}
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