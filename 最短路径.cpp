//���ÿκ����⣺
//������������
//������һ����Ȩ����ͼ��ʾĳһ����Ĺ�����·����ͼ�ж������һЩ�����е���Ҫ���������������еĹ�����·�����ϵ�Ȩ��ʾ����·�ϵ�Ʊ�ۣ���������ʱ�䣩<Ȩֵ>�������һ����ָͨ��ϵͳ��ָ��ǰ����ѯ������͵�Ʊ�ۻ����ٵ�ʱ��������е�ĳһ����������һ�������������1����n�����������Ʊ�ۡ�
#include<stdio.h>
#include<stdlib.h>
#define Max 1001
#define MaxSize 100
//1)ͼ���������� 
typedef struct 
{
	int vertex[MaxSize];//�洢�����Ϣ 
	int edge[MaxSize][MaxSize];//�洢��֮����ڽӹ�ϵ 
	int vertexNum,edgeNum;//��ĸ������ߵĸ��� 
}MGraph;
//2)����һ��ͼ 
MGraph  CreatGraph(int n,int m)
{
	MGraph G;
	int i,j,a,b,c;
	//�� �� 
	G.vertexNum=n;
	G.edgeNum=m;
	//�����Ϣ
	for(i=1;i<=G.vertexNum;i++)
	{
		G.vertex[i]=i;
	} 
	//���ڽӹ�ϵ�ĳ�ʼ��
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
	//����m�бߵ���Ϣ 
	for(i=1;i<=G.edgeNum;i++)
	{
		scanf("%d %d %d",&a,&b,&c);
		G.edge[a][b]=c;
		G.edge[b][a]=c;//����ͼ 
	} 
	return G;
}
//3)�����㷨
void Dijkstra(MGraph G, int v,int n)/*��Դ��v����*/
{
    int i, k, num, dist[n],d[n];  
	//��ʼ�� 
    for (i = 2; i <=G.vertexNum; i++)
    {
        dist[i] = G.edge[v][i];//�洢��ǰ���·���ĳ���   
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
	int n,m;//�������� 
	scanf("%d %d",&n,&m);
	//���� 
	MGraph G;
	G=CreatGraph(n,m);
	//Dijksra
	int v;
	v=1;
	Dijkstra(G,v,n); 

	return 0;
}
 //����csdn������Ĺ���ԭ���õ���򵥵��㷨
