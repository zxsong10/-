//采用课后问题：
//【问题描述】
//假设以一个带权无向图表示某一区域的公交线路网，图中顶点代表一些区域中的重要场所，弧代表已有的公交线路，弧上的权表示该线路上的票价（或搭乘所需时间）<权值>，试设计一个交通指南系统，指导前来咨询者以最低的票价或最少的时间从区域中的某一场所到达另一场所。现在输出1到第n个场所的最低票价。
#include<stdio.h>
#include<stdlib.h>
#define Max 1001
#define MaxSize 100
//1)图的数据类型 
typedef struct 
{
	int vertex[MaxSize];//存储点的信息 
	int edge[MaxSize][MaxSize];//存储便之间的邻接关系 
	int vertexNum,edgeNum;//点的个数，边的个数 
}MGraph;
//2)构造一个图 
MGraph  CreatGraph(int n,int m)
{
	MGraph G;
	int i,j,a,b,c;
	//点 边 
	G.vertexNum=n;
	G.edgeNum=m;
	//点的信息
	for(i=1;i<=G.vertexNum;i++)
	{
		G.vertex[i]=i;
	} 
	//边邻接关系的初始化
	for(i=1;i<=G.vertexNum;i++)
	{
		for(j=1;j<=G.vertexNum;j++)
		{
			if(i==j)
			{
				G.edge[i][j]=0;
			} 
			else
			{
				G.edge[i][j]=Max;
			}	
		}
	}
	//输入m行边的信息 
	for(i=1;i<=G.edgeNum;i++)
	{
		scanf("%d %d %d",&a,&b,&c);
		G.edge[a][b]=c;
		G.edge[b][a]=c;//无向图 
	} 
	return G;
}
//3)核心算法
void Dijkstra(MGraph G, int v,int n)/*从源点v出发*/
{
    int i, k, num, dist[n],d[n];  
	//初始化 
    for (i = 2; i <=G.vertexNum; i++)
    {
        dist[i] = G.edge[v][i];//存储当前最短路径的长度   
    }
    for (num = 1; num < G.vertexNum; num++)
    {
		for (k = 2, i = 2; i <=G.vertexNum; i++)  
        { 
			if(dist[k]==0)
			{
				for(k=2;k<=G.vertexNum;k++)
				{
					if((dist[k]==0)&&(dist[k+1]!=0))
					{
						k++;
						break;
					}
				}
			}
			if ((dist[i] != 0) && (dist[i] < dist[k])) 
            {
            	k = i;
            }
        }
        for (i = 2; i <=G.vertexNum; i++)
        {
            if (dist[i] > dist[k] + G.edge[k][i]) 
            {
                dist[i] = dist[k] + G.edge[k][i];  
            }
        }
        d[k]=dist[k];
        dist[k] = 0;
    }
    printf("%d",d[G.vertexNum]);
} 
int main()
{
	int n,m;//场所，边 
	scanf("%d %d",&n,&m);
	//创造 
	MGraph G;
	G=CreatGraph(n,m);
	//Dijksra
	int v;
	v=1;
	Dijkstra(G,v,n); 

	return 0;
}
 //采用csdn代码更改过后，原本用的最简单的算法
