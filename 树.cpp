#include<stdio.h>
#include<stdlib.h>


typedef char ElementTypeT;
struct BTreeNode 
{
	ElementTypeT element;
	struct BTreeNode * left;
	struct BTreeNode *right;
};
typedef struct BTreeNode *ptrNode;
typedef ptrNode BTree;
ptrNode createNode(ElementTypeT e);
BTree addTree(BTree bt1,BTree bt2);
void disposeTree(BTree bt);//回收树，遍历着把树给free
void inorder(BTree bt);
void postorder(BTree bt);
void preorder(BTree bt);

ptrNode createNode(ElementTypeT e)
{
	ptrNode bt = (ptrNode)malloc(sizeof(struct BTreeNode));
	if(bt==NULL)
		return NULL;
	bt->element = e;
	bt->right = NULL;
	bt->left = NULL;
	return bt;
}
BTree addTree(BTree bt1,BTree bt2)
{
	if(bt1==NULL)
		bt1=bt2;
	else if(!bt1->right)
		bt1->right=bt2;
	else
		bt1->left = bt2;
	return bt1;
}
void disposeTree(BTree bt)
{
	if(bt==NULL)
		return ;
	disposeTree(bt->left);
	disposeTree(bt->right);
	free(bt);
}
void inorder(BTree bt)
{
	if(bt==NULL)
		return ;
	inorder(bt->left);
	printf("%c ",bt->element);
	inorder(bt->right);
}


typedef BTree ElementType;
typedef struct Node* PtrToNode;
typedef PtrToNode Stack;
struct Node{
	ElementType data;
	PtrToNode next;
};
Stack createStack();//创建堆栈
void makeEmpty(Stack);
void dispose(Stack);
void push(ElementType,Stack);//入栈
ElementType pop(Stack);//出栈


//堆栈细节
Stack createStack()
{
	Stack s;
	s = (Stack)malloc(sizeof(struct Node));
	if(s==NULL)
		return NULL;
	s->next = NULL;
	makeEmpty(s);
	return s;
}
void makeEmpty(Stack s)
{
	if(s==NULL)
		return ;
	while((s->next)!=NULL)
		pop(s);//将栈里元素全部弹出
}
void dispose(Stack s)
{
	if(s==NULL)
		return ;
	makeEmpty(s);
	free(s);
}
void push(ElementType e,Stack s)
{
	Stack node = (Stack)malloc(sizeof(struct Node));
	if(node ==NULL)
		return ;
	node->data = e;
	node->next = s->next;
	s->next = node;
}
ElementType pop(Stack s)
{
	if(s->next!=NULL)
	{
		Stack node = s->next;
		ElementType e = node->data;
		s->next = node->next;
		free(node);
		return e;
		
	}
	return NULL;
}
int main()
{
	char postfix[30]="ab+cde+**";
	
	Stack s = createStack();
	BTree a,b,bt,letter;
	int i = 0;
	while(postfix[i]!='\0')
	{
		char c = postfix[i];
		switch(c)
		{
			case'+':
			case'-':
			case'*':
			case'/':
				a = pop(s);
				b = pop(s);
				bt = createNode(c);
				bt = addTree(bt,a);
				bt = addTree(bt,b);
				push(bt,s);
				break;
			default:
				letter = createNode(c);
				push(letter,s);
		}

		i++;	
	}
		BTree expre_tree = pop(s);
		printf("zhong xu:\n");
		inorder(expre_tree);

		disposeTree(expre_tree);
		dispose(s);
		
		return 0;
		printf("\n");
}