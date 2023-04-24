//哈希表，使用unordered_set记录每次记录的sum值然后进行对比，若有重复则false,否则计算至sum==1
class Solution {
public:
    // 取数值各个位上的单数之和
    int getSum(int n) {
        int sum = 0;
        while (n) {
            sum += (n % 10) * (n % 10);//求当前个位数的平方
            n /= 10;//去除当前个位数
        }
        return sum;
    }
    bool isHappy(int n) {
        unordered_set<int> set;//记录每一次的平方和sum
        while(1) {
            int sum = getSum(n);
            if (sum == 1) {
                return true;
            }
            // 如果这个sum曾经出现过，说明已经陷入了无限循环了，立刻return false
            if (set.find(sum) != set.end()) {
                return false;
            } else {
                set.insert(sum);
            }
            n = sum;
        }
    }
};

//2
class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> hash;
        while (n != 1) {
            hash.insert(n);   // 每次记录n(sum)的值
            int sum = 0;
            // 计算中间结果sum (n的每个数位上的数的平方的和)
            while (n) {
                sum += (n % 10) * (n % 10);
                n /= 10;
            }
            if (hash.find(sum) != hash.end())   // 若之前计算得到的sum与当前sum相同，说明出现循环，因此返回false
                return false;
            n = sum;     // sum做为n继续进行计算
        }
        return true;    // 若最终n=1退出循环，说明起初的n为快乐数，因此返回true
    }
};