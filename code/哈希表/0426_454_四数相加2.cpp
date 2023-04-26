//哈希表
//时间复杂度：O(n^2)
//空间复杂度：O(n^2)
class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        unordered_map<int, int> umap; //key:a+b的数值，value:a+b数值出现的次数
        // 遍历大A和大B数组，统计两个数组元素之和，和出现的次数，放到map中
        for (int a : A) {
            for (int b : B) {
                umap[a + b]++;
            }
        }
        int count = 0; // 统计a+b+c+d = 0 出现的次数
        // 在遍历大C和大D数组，找到如果 0-(c+d) 在map中出现过的话，就把map中key对应的value也就是出现次数统计出来。
        for (int c : C) {
            for (int d : D) {
                if (umap.find(0 - (c + d)) != umap.end()) {
                    count += umap[0 - (c + d)];
                }
            }
        }
        return count;
    }
};

//map中的find()方法
/*
在C++中，map和unordered_map的find()方法都是返回一个迭代器，该迭代器指向指定键对应的键值对。如果指定的键不存在，find()方法会返回一个指向容器末尾的迭代器，即map::end()或unordered_map::end()。因此，在查找指定键对应的值时，需要判断返回的迭代器是否等于end()，以确定是否找到了指定的键。

map中的元素是按照键的大小进行有序排列的，因此map的find()方法使用二分查找的方式来查找指定键对应的值。在查找过程中，先比较待查找的键与当前元素的键的大小关系，然后根据大小关系来判断待查找的键在左半边还是右半边，继续在相应的半边中进行查找，直到找到指定键对应的值或者查找范围为空为止。

unordered_map使用哈希表来存储元素，每个元素都被映射到哈希表中的一个桶中。在查找过程中，先根据待查找的键计算出它在哈希表中的桶的位置，然后在该桶中查找是否存在指定的键，如果存在，则返回对应的值；如果不存在，则返回unordered_map::end()，表示没有找到指定的键。
*/