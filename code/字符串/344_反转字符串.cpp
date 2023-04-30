class Solution {
public:
    void reverseString(vector<char>& s) {
        for (int i = 0, j = s.size() - 1; i < s.size()/2; i++, j--) {
            swap(s[i],s[j]);
        }
    }
};

//swap()函数的实现
/*
int tmp = s[i];
s[i] = s[j];
s[j] = tmp;

s[i] ^= s[j];
s[j] ^= s[i];
s[i] ^= s[j];
*/