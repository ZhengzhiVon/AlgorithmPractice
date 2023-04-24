//哈希表，使用unordered_map
//时间复杂度：O(m+n)
//空间复杂度：O(min(m,n))
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.size()>nums2.size()){
            return intersect(nums2,nums1);//确保较长数组在前面nums1的位置
        }

        //创建一个无序哈希表 m，遍历 nums1 数组，将每个数字作为键，出现次数作为值，存入哈希表中
        //使用 unordered_map 是因为需要记录 nums1 中每个数字出现的次数，而 unordered_set 只能记录每个数字是否出现过，无法记录出现的次数
        unordered_map<int,int> m;
        for(int num:nums1){//每出现一次，键值对应次数++
            ++m[num];
        }

        //创建一个空的 vector intersection，遍历 nums2 数组，如果当前数字在哈希表 m 中出现过，则将其加入 intersection 中，并将哈希表中对应键的值减一。如果减一后该键对应的值为 0，则将该键从哈希表中删除。
        vector<int> intersection;
        for(int num:nums2){
            if(m.count(num)){
                intersection.push_back(num);
                --m[num];
                if(m[num]==0){
                    m.erase(num);
                }
            }
        }
        return intersection;
    }
};

//排序+双指针
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        //排序
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        int length1 = nums1.size(), length2 = nums2.size();
        vector<int> intersection;//目标容器
        int index1 = 0, index2 = 0;
        while (index1 < length1 && index2 < length2) {
            if (nums1[index1] < nums2[index2]) {
                index1++;
            } else if (nums1[index1] > nums2[index2]) {
                index2++;
            } else {
                intersection.push_back(nums1[index1]);
                index1++;
                index2++;
            }
        }
        return intersection;
    }
};