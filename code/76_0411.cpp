//76 最小覆盖字串
//滑动窗口
class Solution {
public:
    string minWindow(string s, string t) {
       if(s.size()<t.size()) return "";
       if(s.size()==1&&t.size()==1){
           return s[0]==t[0] ? s : "";
       }//判空

       vector<int>need(128,0);//记录字符
       int needCount=t.size();
       for(char& c: t){
           need[c]++;
       }
       /*
        统计字符串t中每个字符出现的次数，并存储到一个长度为128的数组cnt中。
        这里的128是ASCII码表中字符的数量，因此cnt可以看作是一个哈希表，用于快速查找每个字符出现的次数。
       */
       for(int i=0;i<need.size();i++){
           if(need[i]==0) need[i]=INT_MIN;
       }
       //遍历数组cnt，将其中出现次数为0的字符的计数值设为INT_MIN，表示这些字符不会出现在最终的子串中。
       int right=0;//窗口右边界，左边界定义为局部变量for循环的索引
       int size=INT_MAX;//目标字符串的最小长度，表示目标子串的长度还未确定
       int start=0;//目标字符串出发点
       
       for(int left=0;left<s.size();left++){//所需字符数量不够，窗口一直右移，直到窗口内包含了字符串t的所有字符

           while(right<s.size() && needCount>0){
               if(need[s[right]]!=INT_MIN){//无关字符不用处理
                   if(need[s[right]]>0){
                       needCount--;//对于缺少的字符，needCount--
                   }else{
                   need[s[right]]--;//对于不缺的但是是目标字符仍要-1
                   }
               }
               right++;
           }
           /*
           对于每个右侧字符s[right]，首先检查它是否出现在字符串t中。
           如果不是，则直接跳过。如果是，则将need[s[right]]的计数值减1，表示这个字符已经被包含在窗口中了。
           如果need[s[right]]的计数值减为0，说明窗口中已经包含了t中的一个字符，因此needCount的值减1。
           在右侧字符s[right]被包含在窗口中之后，继续向右移动right，直到窗口内包含了所有t中的字符，或者right已经到达了字符串s的末尾。
           */

           //更新起点和长度
           if(needCount==0 && right-left<size){
               size=right-left;
               start=left;
           }
           /*
           如果needCount的值为0，说明窗口内包含了所有t中的字符，此时计算窗口的长度(right - left)，如果比当前的最小长度(size)还要小，则更新size和start。*/
           
           //窗口left右移1位
           if(need[s[left]]!=INT_MIN){//排除无关字符
               if(need[s[left]]==0){//等于0表示右移后会缺少
                   needCount++;
               }
               //小于0的表示还多出来有富余，只需数量减少
               need[s[left]]++;
           }
           /*
            将窗口的左侧向右移动1个字符，即将left的值加1。在此过程中，需要对need[s[left]]的计数值进行调整。
            如果s[left]不在字符串t中，则直接跳过。否则，将need[s[left]]的计数值加1，表示这个字符已经被从窗口中移除了。
            如果need[s[left]]的计数值加为0，说明窗口中已经不再包含t中的一个字符，因此needCount的值加1。
           */
       }

       //重复上述步骤，直到left到达字符串s的末尾。最终返回目标子串，如果没有找到合适的子串，则返回空字符串。

       return size<INT_MAX ? s.substr(start,size) : "";
       
    }
};


