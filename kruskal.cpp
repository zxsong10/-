//Kruskal算法：O(mlogm): m为边的数量
#include<bits/stdc++.h>//万能头文件
using namespace std;
const int M=100002;//边的数量
const int N=50001;//点的数量
struct Node//定义一个包含起点，终点，边权的结构体
{
	int x,y,v;
	bool operator<(const Node &A) const//重构//目的是进行边权由小到排序
    {
		return v<A.v;
	}
}a[M];
 
int n,m,fa[N];
//并查集的基本操作，在数据结构专题里我有讲解，大佬们要是忘记了，可以去看看
int Find(int x)//找父节点
{
	if(x==fa[x]) return x;
	return fa[x]=Find(fa[x]);
}
//Kruskal算法
int Kruskal()
{
	for(int i=1;i<=n;i++) fa[i]=i;//初始化父节点
	sort(a+1,a+1+m);//将边权排序
	int ans=0,cnt=n;//ans记录最小生成树的值，cnt代表有多少个集合
	for(int i=1;i<=m;i++)//枚举边
	{
		int x=Find(a[i].x),y=Find(a[i].y);//找起点和终点所属的集合
		if(x!=y)//若是不在一个集合（父节点）
		{
			fa[x]=y;//进行合并操作
			ans+=a[i].v;//加最小边权
			--cnt;//总集合树-1
		}
		if(cnt==1) break;//如果最终只有一个集合，说明已经生成了最小生成树，就结束循环
	}
	if(cnt!=1) return -1;//如果不为一个集合，返回-1
	else return ans;//否则返回最小生成树值
}
 
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)//存图操作
	scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].v);
	printf("%d",Kruskal());
}