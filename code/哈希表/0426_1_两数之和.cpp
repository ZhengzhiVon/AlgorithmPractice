//哈希表，用unordered_map
//时间复杂度：O(N)
//空间复杂度：O(N)

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> map;
        for(int i=0;i<nums.size();i++){
            //遍历当前元素，并在map中寻找是否有匹配的key
            auto iter=map.find(target-nums[i]);//iter为一个指向哈希表中某个键值对的迭代器
            if(iter!=map.end()){
                return {iter->second,i};//获取并返回符合条件的数的下标，{}直接快速创建一个vector<int>容器用来接收
            }
			//如果没找到匹配对，就把访问过的元素和下标加入到map中
            map.insert(pair<int,int>(nums[i],i));
        }
        return {};
    }
};


//iter
/*
iter是一个指向哈希表中某个键值对的迭代器，它指向的是一个pair对象，其中pair.first表示键，pair.second表示值。在这段代码中，我们使用iter->second来获取pair.second，也就是哈希表中符合条件的数的下标。

iter->second表示iter所指向的键值对中的值，即符合条件的数在原数组中的下标。这是因为在插入哈希表时，我们将nums[i]作为键，i作为值插入到哈希表中，因此iter->second就是i，即当前遍历到的数在原数组中的下标。而iter->first则表示哈希表中键的值，即nums[i]的值。

当在哈希表中查找到符合条件的数时，可以通过iter->second来获取其在原数组中的下标，然后将这个下标和当前遍历到的数的下标组成一个包含两个元素的vector<int>对象返回即可。
*/

//return {iter->second,i};
/*
使用了花括号{}来快速创建一个包含两个元素的vector<int>对象，并将iter->second和i按顺序插入到这个对象中。这种方式只在C++11及以上版本中才支持
*/


//暴力枚举
//时间复杂度：O(N^2)，其中 N 是数组中的元素数量。最坏情况下数组中任意两个数都要被匹配一次。
//空间复杂度：O(1)。

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        return {};
    }
};