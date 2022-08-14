//Kruskal�㷨��O(mlogm): mΪ�ߵ�����
#include<bits/stdc++.h>//����ͷ�ļ�
using namespace std;
const int M=100002;//�ߵ�����
const int N=50001;//�������
struct Node//����һ��������㣬�յ㣬��Ȩ�Ľṹ��
{
	int x,y,v;
	bool operator<(const Node &A) const//�ع�//Ŀ���ǽ��б�Ȩ��С������
    {
		return v<A.v;
	}
}a[M];
 
int n,m,fa[N];
//���鼯�Ļ��������������ݽṹר�������н��⣬������Ҫ�������ˣ�����ȥ����
int Find(int x)//�Ҹ��ڵ�
{
	if(x==fa[x]) return x;
	return fa[x]=Find(fa[x]);
}
//Kruskal�㷨
int Kruskal()
{
	for(int i=1;i<=n;i++) fa[i]=i;//��ʼ�����ڵ�
	sort(a+1,a+1+m);//����Ȩ����
	int ans=0,cnt=n;//ans��¼��С��������ֵ��cnt�����ж��ٸ�����
	for(int i=1;i<=m;i++)//ö�ٱ�
	{
		int x=Find(a[i].x),y=Find(a[i].y);//�������յ������ļ���
		if(x!=y)//���ǲ���һ�����ϣ����ڵ㣩
		{
			fa[x]=y;//���кϲ�����
			ans+=a[i].v;//����С��Ȩ
			--cnt;//�ܼ�����-1
		}
		if(cnt==1) break;//�������ֻ��һ�����ϣ�˵���Ѿ���������С���������ͽ���ѭ��
	}
	if(cnt!=1) return -1;//�����Ϊһ�����ϣ�����-1
	else return ans;//���򷵻���С������ֵ
}
 
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)//��ͼ����
	scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].v);
	printf("%d",Kruskal());
}