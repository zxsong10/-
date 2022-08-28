#include<stdio.h>
#include<stdlib.h>

#define max 1000000

int place[max];//皇后所在列。
int uppertri[2*max-1];//某个皇后对应的倾斜度为135度的对角线，这里每个皇后所在的行raw减去所在的列col再加上棋盘行数减1（n-1）表示皇后的上三角对角线
int lowtri[2*max-1];//某个皇后对应的倾斜度为45度的对角线，这里每个皇后所在的行raw加上所在的列col，表示皇后的下三角对角线
int flag[max];//作为标志，flag[i]==1表示第row行的第i列放置了皇后，flag[i]==0表示第raw行的第i列还没有被放置皇后
int count=1;//计数使用
 
//核心部分，n皇后问题中的某一行raw
void generate(int n,int raw){
    int col;//列
    for(col=0;col<n;col++){
        if(uppertri[raw-col+n-1]==0 && lowtri[raw+col]==0 && flag[col]==0){//if语句块里的语义即当前行的第col列是否允许摆放皇后
            //对第raw行第col列的位置进行“占领”
            flag[col]=1;
            place[raw]=col;
            uppertri[raw-col+n-1]=1;
            lowtri[raw+col]=1;
            //第raw行的完成了，就开始递归第raw+1行的情况
            if(raw<n-1){
                generate(n,raw+1);
            }
            //当递归到最后一行而且最后一行也找到了放置皇后的位置，即一种皇后摆放情况已经得到确定，就输出
            else
            {
                printf("这是第%d种情况\n",count);
                for(int i=0;i<n;i++){
                    printf("第%d行，第%d列可以使用\n",i+1,place[i]+1);
                }
                count++;
            }
            flag[col]=0;
            uppertri[raw-col+n-1]=0;
            lowtri[raw+col]=0;           
        }
    }
}

int main(){
    int n;
    printf("请输入棋盘总行数：");
    scanf("%d",&n);
    generate(n,0);
}
