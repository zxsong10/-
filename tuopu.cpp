#include <iostream>
#include <stdlib.h>
using namespace std;
typedef struct{ 
	char data[200];
	int top; 
}SqStack;
//初始化 
void InitStack(SqStack &S){
	S.top=-1;
} 
//判断栈满 
int StackFull(SqStack s){
	return(s.top==200-1?1:0);
}
//进站
int Push(SqStack &S,int e){
	if(StackFull(S)) return 0;
	S.top++;
	S.data[S.top]=e;
	return 1;
} 
int StackEmpty(SqStack S){
	return(S.top==-1?1:0);
} 
//出栈
int Pop(SqStack &S,int &e){
	if(StackEmpty(S)) return 0;
	e=S.data[S.top];
	S.top--;
	return 1;
} 
typedef	struct ArcNode{//边表 
	int adjvex;
	struct ArcNode *nextarc;
}ArcNode;

typedef struct VNode{   //定点表 
	char data;
	ArcNode *firstarc;
}VNode;

typedef struct {
	VNode vertexs [2000];
	int vexnum,arcnum;
}ALGraph;


void CreateAvg(ALGraph &p){
	int i, j,k;
	ArcNode * node = NULL;
	char c;
	int vexnum,arcnum;
	cout << "请输入图的顶点个数：" <<endl;
	cin >> p.vexnum;
	cout << "请输入图的边数：" <<endl;
	cin >> p.arcnum;
	for (i=0;i<p.vexnum;i++){
			cout << "请输入你的顶点" <<endl;
			cin >> c;
			p.vertexs[i].data = c;
			p.vertexs[i].firstarc = NULL;  
	}

	for(k=0;k<p.arcnum;k++) {  
	    cout << "请输入哪个顶点指向到哪个顶点："<<endl;
		cin >> i >> j ; 
		node=(ArcNode *)malloc(sizeof(ArcNode));
		node->adjvex=j;							//数组下标位置 
		node->nextarc=p.vertexs[i].firstarc;
		p.vertexs[i].firstarc=node;
    }	
}
	
void Print(int n ,char data){
	cout << "拓扑排序取出的点为："<<data <<endl;
}
void FindInDegree(ALGraph G,int indegree[])
{	int i,k;
	ArcNode *p;
	for(i=0;i<G.vexnum;i++)
		indegree[i]=0;
	for(i=0;i<G.vexnum;i++)
	{	p=G.vertexs[i].firstarc;
		while(p)
		{	k=p->adjvex;
			indegree[k]++;
			p=p->nextarc;
		}
	}
}
int TopologicalSort(ALGraph G){
	int i,k,n,count;
	ArcNode * p;
	int indegree [20];
	FindInDegree(G,indegree);
	SqStack L;
	InitStack(L);
	count = 0;
	for (i=0;i<G.vexnum;i++){
		if(indegree[i]==0){
			Push(L,i);
		}
	}
	while(!StackEmpty(L)){
		Pop(L,n);
		Print(n,G.vertexs[n].data);
		count++;
		for (p = G.vertexs[n].firstarc;p!=NULL;p=p->nextarc){
			k = p->adjvex;
			if(!(--indegree[k])){
				Push(L,k);
			} 
	}
	}
	if(count<G.vexnum)return -1;
	else return 0;
}



int main (){
	ALGraph G;
	CreateAvg(G);
	TopologicalSort(G);
	return 0;
}