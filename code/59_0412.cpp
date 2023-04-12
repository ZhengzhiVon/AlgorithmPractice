class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n,vector<int>(n,0));//n每行每列元素个数
        int startx=0,starty=0;//定义每循环一个圈的起始位置,每一圈需要变化
        int loop=n/2;//每个圈循环几次
        int mid=n/2;//矩阵中间的位置
        int count=1;//用来给矩阵中的每一个空格赋值,从1开始递增赋值
        int offset=1;//需要控制每一条边遍历的长度，每次循环完成后右边界收缩一位
        int i,j;
        while(loop--){
            i=startx;
            j=starty;

            //四个for循环模拟转了一圈(左闭右开)

            //填充上行，从左到右
            for(j=starty;j<n-offset;j++){//n-offset,左闭右开，不遍历最后一个位置
                res[startx][j]=count++;//填充一行
            }
            //填充右列，从上到下
            for(i=startx;i<n-offset;i++){//n-offset,左闭右开，不遍历最后一个位置
                res[i][j]=count++;//填充一列
            }
            //填充下行，从右到左
            for(;j>starty;j--){
                res[i][j]=count++;
            }
            //填充左列，从下到上
            for(;i>startx;i--){
                res[i][j]=count++;
            }

            //第二圈开始的时候，起始位置需要各自前移一位+1
            startx++;
            starty++;

            //控制每一圈里每一条边遍历的长度
            offset+=1;
        }

        //如果n为奇数，n/2之后最中间的位置将空出，需要独立赋值
        if(n%2){
            res[mid][mid]=count;
        }
        return res;
    }
};