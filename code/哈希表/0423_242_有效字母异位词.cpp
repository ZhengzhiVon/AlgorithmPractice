//数组哈希表，统计每个字符串个字符出现的次数，遍历三次，第一次遍历s，计数器++；第二次遍历t，字符计数器--。最后在遍历计数器数组，若存在索引下标处不为0，则说明s和t不是字母异位词，返回fasle
class Solution {
public:
    bool isAnagram(string s, string t) {
        int record[26] = {0};
        if(s.length()!=t.length()){
            return false;
        }
        for (int i = 0; i < s.size(); i++) {
            // 并不需要记住字符a的ASCII，只要求出一个相对数值就可以了
            record[s[i] - 'a']++;
        }
        for (int i = 0; i < t.size(); i++) {
            record[t[i] - 'a']--;
        }
        for (int i = 0; i < 26; i++) {
            if (record[i] != 0) {
                // record数组如果有的元素不为零0，说明字符串s和t 一定是谁多了字符或者谁少了字符。
                return false;
            }
        }
        // record数组所有元素都为零0，说明字符串s和t是字母异位词
        return true;
    }
};

//排序
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) {
            return false;
        }
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t;
    }
};
//时间复杂度：0（nlogn），其中n为s的长度。排序的时间复杂度为O（nlogn），比较两个字符串是否相等时间复杂度为O（n），因此总体时间复杂度为C（nlogn+n）=O（nlogn）。
//空间复杂度：O（logn）。排序需要O（logn）的空间复杂度。