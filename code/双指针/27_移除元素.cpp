//双指针法
//时间复杂度：O(n)，其中 n 为数组长度。
//空间复杂度：O(1)。

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
      int slow=0;
      for(int fast=0;fast<nums.size();fast++){
          if(val!=nums[fast]){
              nums[slow++]=nums[fast];
          }
      }
      return slow;
    }
};