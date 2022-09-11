#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LEN 30
#define RED 1				//��ɫ 
#define BLACK 0				//��ɫ	

typedef struct tree{
	int key;			//�ؼ��� 
	int color;			//�����ɫ	
	struct tree *parent;	//ָ���׵�ָ�� 
	struct tree *lchild;	//ָ������ 
	struct tree *rchild;	//ָ���Һ��� 
}Node, *RBtree;

typedef struct{
	RBtree pt[LEN];
	int rear;
	int front;
}Queue;

Node * Insert(RBtree * t, int data);	//������ 
Node * CreateNode(int data);		//������� 
void CreateRBtree(RBtree * t, Node *node);		//������������� 
bool FindNode(RBtree *t, int data);		//�ҵ�Ҫɾ���Ľ�� 

Node * RedDelete(RBtree *t, Node *node);				//ɾ������ 
void BlackDelete(RBtree *t, Node *node, Node *fat);				//ɾ���ڽ��



void Lsp(Node **root, Node *node);		//���� 
void Rsp(Node **root, Node *node);		//���� 
Node * PriorNode(Node *node);			//���ظý��� ǰ����� 
Node * NextNode(Node *node);		//���ظý��� ��̽��

void Clear(RBtree *t);		//���� 

void Traverse(RBtree *t);		//������� 

void TraColor(RBtree *t);		//������� ��ɫ 

Node *pnode(RBtree *t, int data);		//�������ݽ���ָ�� 


void InitQueue(Queue *q);	//��ʼ�� 
bool DeQueue(Queue *q, Node ** t); //����
bool EnQueue(Queue *q, Node ** t); //��� 
bool Full(Queue *q);		//����
bool Empty(Queue *q);		//�ӿ� 



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


	TraColor(&root);		//������� ��ɫ 
//	Traverse(&root);		//������� 
	
	printf("����Ҫɾ��������: ");
	while(scanf("%d", &i) == 1)
	{
		while(getchar() !='\n')
			continue;
		if(FindNode(&root, i))			//�ҵ�Ҫɾ���Ľ�� 
		{
	    	printf("\n");
	    	TraColor(&root);		//������� ��ɫ 
	    	printf("\n");	
		}
		else
		{
			printf("���ݲ�����\n");
		}

		printf("����Ҫɾ��������: ");	
	}


	Clear(&root);
	
	return 0;
}

bool FindNode(RBtree *t, int data)		//�ҵ�Ҫɾ���Ľ�� 
{
	Node *del;
	Node *fat;   //���׽�� 
	Node *gra; //үү���
	Node *tp; 
	Node *node;
	
	int temp;

	if(*t == NULL)
		return false;
	
	del=pnode(t, data);	//�������ݽ���ָ�� 
	if(del == NULL)
		return false;

	if(del->lchild != NULL)
	{
		node = PriorNode(del);			//���ظý��� ǰ�����
		temp = node->key;
		node->key = del->key;
		del->key = temp;
		
	}
	else if(del->rchild != NULL)
	{
		node = NextNode(del);		//���ظý��� ��̽��
		temp = node->key;
		node->key = del->key;
		del->key = temp;
	}
	else	
	{
		node = del;
	}
	
	if(node->parent == NULL)	//���ɾ�����Ǹ��ڵ�ֱ��ɾ�� 
		*t = NULL;
	else
	{
		fat = node->parent;
		tp = RedDelete(t, node);				//ɾ������ ������ɾ����������Ӹ�λ�õĽ�� 
		if(node->color == BLACK)
		{
			BlackDelete(t, tp, fat);		//ɾ���ڽ�� 
		}
		
	}	
			
	free(node);
	
	return true;
}

void BlackDelete(RBtree *t, Node *node, Node *fat)				//ɾ���ڽ�㣬 ������У��սڵ����ںڽڵ�  
{
	Node * bro;	  //�ֵܽ�� 
	Node **pf;   //ָ���׽���ַ��ָ�� 
	Node *temp;
	
	if(node != NULL && node->color == RED)		//������Ӻ�Ľ���Ǻ��㣬 ֱ�Ӹĺ� 
		node->color = BLACK;
	else if(node != NULL && node->parent == NULL)		//����ڵ��Ǹ��ڵ㣬ֱ�Ӹĺ� 
	{
		node->color = BLACK;
	}
	else							//������У��սڵ����ںڽڵ� 
	{
		if(fat->parent != NULL && fat == fat->parent->lchild)		//��Ÿ��ڵ�ĵ�ַ 
			pf = &(fat->parent->lchild);
		else if(fat->parent != NULL && fat == fat->parent->rchild)
			pf = &(fat->parent->rchild);
		else
			pf = t;	
			
		if(node == fat->lchild)		//�ýڵ��Ǹ��ڵ������ 
		{
			bro = fat->rchild;		//�ֵܽڵ�
			if(bro->color == RED)		//1. ����ֵ��Ǻ�ɫ 
			{
				bro->color = BLACK;
				fat->color = RED;
				Lsp(pf, fat);		//�Ը��ڵ�Ϊ֧�� ���� 
				BlackDelete(t, node, fat);	//���ϵݹ�, ��Ҫ�ǰ� node���ֵܽڵ��Ϊ��ɫ 
			} 
			else if(bro->color == BLACK)	//����ֵ��Ǻڽڵ� 
			{
				if((bro->lchild == NULL && bro->rchild == NULL) || (bro->lchild == NULL && bro->rchild != NULL && bro->rchild->color == BLACK) 		//2. �ֵܵ��������Ӷ��Ǻ�ɫ 
				  || (bro->rchild == NULL && bro->lchild != NULL && bro->lchild->color == BLACK) || (bro->lchild != NULL && bro->lchild->color == BLACK && bro->rchild != NULL && bro->rchild->color == BLACK))
				{
					bro->color = RED;			//���ֵܸ�Ϊ��ɫ 
					if(fat->color == RED)
						fat->color = BLACK;		//���׸�Ϊ��ɫ 
					else
						BlackDelete(t, fat, fat->parent);	//���������ǰ���Ǻ�ɫ���Ը��׽ڵ����ϵݹ�		
				}
				else if((bro->lchild != NULL && bro->lchild->color == RED) && (bro->rchild == NULL || bro->rchild->color == BLACK))		//3. �ֵܵ������Ǻ�ɫ���Һ����Ǻ�ɫ 
				{
					temp = bro->lchild;				//�������µ��ֵܽڵ� 
					bro->lchild->color = BLACK;		//�ֵܵ����Ӹ�Ϊ��ɫ 
					bro->color = RED;				//�ֵܸ�Ϊ��ɫ 
					
					Rsp(&fat->rchild, bro);		//���ֵ�Ϊ֧�� ����	
					bro = temp; 
					
					//��Ҫ�ǰѵ� 3 �������Ϊ �� 4 ��������� 
					bro->color = fat->color;	//���׵���ɫ���ֵ� 
					fat->color = BLACK;			//���ױ�� 
					bro->rchild->color = BLA