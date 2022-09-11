#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LEN 30
#define RED 1				//红色 
#define BLACK 0				//黑色	

typedef struct tree{
	int key;			//关键字 
	int color;			//结点颜色	
	struct tree *parent;	//指向父亲的指针 
	struct tree *lchild;	//指向左孩子 
	struct tree *rchild;	//指向右孩子 
}Node, *RBtree;

typedef struct{
	RBtree pt[LEN];
	int rear;
	int front;
}Queue;

Node * Insert(RBtree * t, int data);	//插入结点 
Node * CreateNode(int data);		//建立结点 
void CreateRBtree(RBtree * t, Node *node);		//建立调整红黑树 
bool FindNode(RBtree *t, int data);		//找到要删除的结点 

Node * RedDelete(RBtree *t, Node *node);				//删除红结点 
void BlackDelete(RBtree *t, Node *node, Node *fat);				//删除黑结点



void Lsp(Node **root, Node *node);		//左旋 
void Rsp(Node **root, Node *node);		//右旋 
Node * PriorNode(Node *node);			//返回该结点的 前驱结点 
Node * NextNode(Node *node);		//返回该结点的 后继结点

void Clear(RBtree *t);		//销毁 

void Traverse(RBtree *t);		//中序遍历 

void TraColor(RBtree *t);		//层序遍历 颜色 

Node *pnode(RBtree *t, int data);		//返回数据结点的指针 


void InitQueue(Queue *q);	//初始化 
bool DeQueue(Queue *q, Node ** t); //出队
bool EnQueue(Queue *q, Node ** t); //入队 
bool Full(Queue *q);		//队满
bool Empty(Queue *q);		//队空 



int main(void)
{
	RBtree root = NULL;
	int i;
	Node * temp;
	int num[18] = {6,1,4,2,10,13,16,8,9,17,19,15,14,21,28,22,12,18};
	
	for(int i = 0; i <18;++i)
	{
		temp = Insert(&root, num[i]);
		CreateRBtree(&root, temp);
		
	}


	TraColor(&root);		//层序遍历 颜色 
//	Traverse(&root);		//中序遍历 
	
	printf("输入要删除的数据: ");
	while(scanf("%d", &i) == 1)
	{
		while(getchar() !='\n')
			continue;
		if(FindNode(&root, i))			//找到要删除的结点 
		{
	    	printf("\n");
	    	TraColor(&root);		//层序遍历 颜色 
	    	printf("\n");	
		}
		else
		{
			printf("数据不存在\n");
		}

		printf("输入要删除的数据: ");	
	}


	Clear(&root);
	
	return 0;
}

bool FindNode(RBtree *t, int data)		//找到要删除的结点 
{
	Node *del;
	Node *fat;   //父亲结点 
	Node *gra; //爷爷结点
	Node *tp; 
	Node *node;
	
	int temp;

	if(*t == NULL)
		return false;
	
	del=pnode(t, data);	//返回数据结点的指针 
	if(del == NULL)
		return false;

	if(del->lchild != NULL)
	{
		node = PriorNode(del);			//返回该结点的 前驱结点
		temp = node->key;
		node->key = del->key;
		del->key = temp;
		
	}
	else if(del->rchild != NULL)
	{
		node = NextNode(del);		//返回该结点的 后继结点
		temp = node->key;
		node->key = del->key;
		del->key = temp;
	}
	else	
	{
		node = del;
	}
	
	if(node->parent == NULL)	//如果删除的是根节点直接删除 
		*t = NULL;
	else
	{
		fat = node->parent;
		tp = RedDelete(t, node);				//删除红结点 ，返回删除后从新连接改位置的结点 
		if(node->color == BLACK)
		{
			BlackDelete(t, tp, fat);		//删除黑结点 
		}
		
	}	
			
	free(node);
	
	return true;
}

void BlackDelete(RBtree *t, Node *node, Node *fat)				//删除黑结点， 红黑树中，空节点属于黑节点  
{
	Node * bro;	  //兄弟结点 
	Node **pf;   //指向父亲结点地址的指针 
	Node *temp;
	
	if(node != NULL && node->color == RED)		//如果连接后的结点是红结点， 直接改黑 
		node->color = BLACK;
	else if(node != NULL && node->parent == NULL)		//如果节点是根节点，直接改黑 
	{
		node->color = BLACK;
	}
	else							//红黑树中，空节点属于黑节点 
	{
		if(fat->parent != NULL && fat == fat->parent->lchild)		//存放父节点的地址 
			pf = &(fat->parent->lchild);
		else if(fat->parent != NULL && fat == fat->parent->rchild)
			pf = &(fat->parent->rchild);
		else
			pf = t;	
			
		if(node == fat->lchild)		//该节点是父节点的左孩子 
		{
			bro = fat->rchild;		//兄弟节点
			if(bro->color == RED)		//1. 如果兄弟是红色 
			{
				bro->color = BLACK;
				fat->color = RED;
				Lsp(pf, fat);		//以父节点为支点 左旋 
				BlackDelete(t, node, fat);	//向上递归, 主要是把 node的兄弟节点该为黑色 
			} 
			else if(bro->color == BLACK)	//如果兄弟是黑节点 
			{
				if((bro->lchild == NULL && bro->rchild == NULL) || (bro->lchild == NULL && bro->rchild != NULL && bro->rchild->color == BLACK) 		//2. 兄弟的两个孩子都是黑色 
				  || (bro->rchild == NULL && bro->lchild != NULL && bro->lchild->color == BLACK) || (bro->lchild != NULL && bro->lchild->color == BLACK && bro->rchild != NULL && bro->rchild->color == BLACK))
				{
					bro->color = RED;			//把兄弟改为红色 
					if(fat->color == RED)
						fat->color = BLACK;		//父亲改为黑色 
					else
						BlackDelete(t, fat, fat->parent);	//如果父亲以前就是黑色，以父亲节点向上递归		
				}
				else if((bro->lchild != NULL && bro->lchild->color == RED) && (bro->rchild == NULL || bro->rchild->color == BLACK))		//3. 兄弟的左孩子是红色，右孩子是黑色 
				{
					temp = bro->lchild;				//右旋后，新的兄弟节点 
					bro->lchild->color = BLACK;		//兄弟的左孩子改为黑色 
					bro->color = RED;				//兄弟改为红色 
					
					Rsp(&fat->rchild, bro);		//以兄弟为支点 右旋	
					bro = temp; 
					
					//主要是把第 3 种情况变为 第 4 种情况处理 
					bro->color = fat->color;	//父亲的颜色给兄弟 
					fat->color = BLACK;			//父亲变黑 
					bro->rchild->color = BLA