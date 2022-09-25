#include"head.h"
 
int main(void)
{
	BiTree T = NULL;
	TriTree triTree = NULL;
	TriTree triTree_temp = NULL;
	int tag;
	int i, count;
	int num;
	char sel;
	char tree[50];  //存储二叉树
	int flag = 1;
	while (flag)
	{
		system("cls");
		printf(" -------------------------------------------------\n");
		printf("|        0. 树的初始化                           |\n");
		printf("|        1. 遍历二叉树                           |\n");
		printf("|        2. 计算结点个数                         |\n");
		printf("|        3. 计算叶子数                           |\n");
		printf("|        4. 判断二叉树是否为小根树               |\n");
		printf("|        5. 将二叉树分解为根，左，右             |\n");
		printf("|        6. 替换左子树                           |\n");
		printf("|        7. 替换右子树                           |\n");
		printf("|        8. 求二叉树第k个访问到的结点            |\n");
		printf("|        9. 判断二叉树中是否存在元素为x的结点    |\n");
		printf("|        10.判断二叉树是否为正则二叉树           |\n");
		printf("|        11.交换树中每个结点的左右子树           |\n");
		printf("|        12.求以x为根结点的子树的深度            |\n");
		printf("|        13.求二叉树中分支结点数                 |\n");
		printf("|        14.判断两个二叉树是否相似               |\n");
		printf("|        15.销毁二叉树                           |\n");
		printf("|        16.分离左子树                           |\n");
		printf("|        17.分离右子树                           |\n");
		printf("|        18.退出                                 |\n");
		printf(" -------------------------------------------------\n");
		printf("\n请在0-16中选择，若一次输入多个选择，将执行首个选择\n");
		printf("请输入你想要执行的操作指令序号：");
		scanf("%d", &num);
		getchar();
		switch (num)
		{
		//创建树
		case 0:
			tag = 1;
			i = 0;
			printf("请按照先序遍历格式输入二叉树（‘#’表示空树）：");
			scanf("%s", tree);
			T = CreateBiTree(tree, i,tag);
			if (tag == 0)
			{
				printf("树输入错误，创建失败\n");
				break;
			}
			i = 0;
			triTree = CreateTriTree(tree, i);//后序三叉链表遍历时使用
			printf("树创建成功\n");
			printf("已经完成树的创建");
			flag = 1;
			break;
 
		//遍历树
		case 1:
			if (T == NULL)
			{
				printf("尚未创建树");
			}
			else
			{
				printf("a.先序遍历   b.中序遍历  c.后序遍历:");
				scanf("%c", &sel);
				getchar();
				switch (sel)
				{
				case 'a'://先序遍历
					PreOrderTraverse(T, visit);
					break;
				case 'b'://中序遍历
					InOrderTraverse(T);
					break;
				case 'c'://后序遍历
					i = 0;
					triTree_temp = CreateTriTree(tree, i);//每次后序遍历后，mark重定义
					PostOrder(triTree_temp, visit);//后序遍历
					break;
				default:
					printf("\n请输入正确的序号");
					break;
				}
			}
			break;
 
		//计算结点数
		case 2:
			count = 0;
			Node(T, count);
			printf("\n该树的结点共有：%d个", count);
			break;
 
		//计算叶子数
		case 3:
			count = 0;
			count = Leaves(T);
			printf("\n该树的叶子共：%d个",count);
			break;
 
		//判断二叉树是都为小根二叉树
		case 4:
			if (T == NULL)printf("树尚未建立");
			else
			{
				if (SmallBiTree(T) == TRUE)printf("\n当前二叉树为小根二叉树\n");
				else printf("\n当前二叉树不为小根二叉树\n");
			}
			break;
		//将二叉树分解为左，右，根三部分
		case 5:
			if (T == NULL)printf("树尚未建立");
			else
			{
				BreakBiTree(T);
			}
			break;
 
		//替换左子树
		case 6:
			if (T == NULL)printf("树尚未建立");
			else
			{
				BiTree l;
				char lchar[50];
				int temp = 0;
				tag = 1;
				printf("\n请输入你想要替换的左子树：");
				scanf("%s", lchar);
				l = CreateBiTree(lchar, temp,tag);
				if (tag == 0)
				{
					printf("\n树输入错误，创建失败\n");
					break;
				}
				ReplaceLeft(T, l);
				printf("替换后的树为：");
				PreOrderTraverse(T, visit);
			}
			break;
 
		//替换右子树
		case 7:
			if (T == NULL)printf("树尚未建立");
			else
			{
				BiTree r;
				char rchar[50];
				int temp = 0;
				tag = 1;
				printf("\n请输入你想要替换的左子树：");
				scanf("%s", rchar);
				r = CreateBiTree(rchar, temp,tag);
				if (tag == 0)
				{
					printf("\n树输入错误，创建失败\n");
					break;
				}
				ReplaceRight(T, r);
				printf("替换后的树为：");
				PreOrderTraverse(T, visit);
			}
			break;
 
		//第k个被访问到的结点
		case 8:
			if (T == NULL)printf("树尚未建立");
			else
			{
				int k;
				char temp;
				printf("\n你想要查看第几个被访问的结点：");
				scanf("%d", &k);
				getchar();
				temp=PreOrderK(T, k);
				printf("\n第%d个被访问到的结点是：%c", k,temp);
			}
			break;
		
		//判断二叉树中是否存在元素为x的结点
		case 9:
			if (T == NULL)printf("树尚未建立");
			else
			{
				char temp;
				int result;
				printf("\n你想要检查的结点数据是:");
				scanf("%c", &temp);
				result=SearchX(T, temp);
				if (result == 1)printf("\n该结点存在\n");
				else printf("\n该结点不存在\n");
			}
			break;
 
		//判断二叉树是否为正则二叉树
		case 10:
			if (T == NULL)printf("树尚未建立");
			else
			{
				int temp;
				temp=RegularBiTree(T);
				if (temp == 1)printf("\n树为正则二叉树\n");
				else printf("\n树不为正则二叉树\n");
			}
			break;
 
		//交换树中每个结点的左右子树
		case 11:
			if (T == NULL)printf("树尚未建立");
			else 
			{
				ExchangeSubTree(T);
				printf("\n交换完成\n");
			}
			break;
 
		//求以x为根结点的子树的深度
		case 12:
			if (T == NULL)printf("树尚未建立");
			else
			{
				char temp;
				int dep;
				printf("\n你想要求以什么为根的子树的深度:");
				scanf("%c", &temp);
				dep= Depthx(T, temp);
				if (dep == 0)
				{
					printf("以%c为值结点不存在，请重新输入\n",temp);
				}
				else
				{
					printf("\n以%c为根结点的子树深度为%d", temp, dep);
				}
				
			}
			break;
 
		//求树中分支结点数 
		case 13:
			if (T == NULL)printf("树尚未建立");
			else
			{
				int temp;
				temp = BranchNodes(T);
				printf("\n树中分支结点数为:%d", temp);
			}
			break;
 
		//判断两棵树是否相似
		case 14:
			if (T == NULL)printf("树尚未建立");
			else
			{
				BiTree T2;
				char t2[50];
				int temp = 0;
				tag = 1;
				printf("\n请输入你想要比较的新树：");
				scanf("%s", t2);
				T2 = CreateBiTree(t2, temp, tag);
				if (tag == 0)
				{
					printf("\n树输入错误，创建失败\n");
					break;
				}
				if (Similar(T, T2) == TRUE)printf("\n两棵树相似");
				else printf("\n两棵树不相似");
			}
			break;
 
		//销毁二叉树
		case 15:
			if (T == NULL)printf("树尚未建立");
			else
			{
				DestroyBiTree(T);
				printf("树已销毁");
			}
			break;
 
		//分离左子树
		case 16:
			if (T == NULL)printf("树尚未建立");
			else
			{
				Breakleft(T);
			}
			break;
 
		//
		case 17:
			if (T == NULL)printf("树尚未建立");
			else
			{
				Breakright(T);
			}
			break;
		case 18:
			flag = 0;
			printf("程序结束");
			break;
		default:
			printf("\n请输入正确的序号");
			break;
		}
		printf("\n");
		getchar();
		system("pause");
	}
	return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
typedef int Status;		    //用作函数返回类型，表示函数结果状态 
typedef char TElemType;		//假设二叉树结点的元素类型为字符
 
 
//二叉树链式
typedef struct BiTNode 
{
	TElemType data;
	BiTNode* lchild, * rchild;
} BiTNode, * BiTree;
 
//三叉链表
typedef struct TriTNode 
{
	int mark;
	TElemType data;
	TriTNode* parent, * lchild, * rchild;
}TriTNode, * TriTree;
 
 
//辅助栈
typedef struct BSNode
{
	BiTree data;
	struct BSNode* next;
}BSNode, *BStack;
//初始化栈
void InitStack(BStack& s)
{
	s = NULL;
}
//元素入栈
Status Push_BS(BStack& s, BiTree e)
{
	BSNode* p;
	p = (BSNode*)malloc(sizeof(BSNode));
	if (p == NULL)return OVERFLOW;
	p->data = e;
	p->next = s;
	s = p;
	return OK;
}
//出栈
Status Pop_Bs(BStack& s, BiTree& e)
{
	BSNode* p;
	if (s == NULL)return ERROR;
	p = s;
	e = s->data;
	s = s->next;
	free(p);
	return OK;
}
//判断栈空
Status StackEmpty_BS(BStack s)
{
	if (s == NULL)return TRUE;
	else return FALSE;
}
 
 
 
//特殊1，访问结点的值
Status visit(TElemType e)
{
	if (e)
	{
		printf("%c", e);
		return OK;
	}
	else return ERROR;
}
//特殊2，配合用于求对二叉树T先序遍历时第k个访问到的结点的值
TElemType visitsPreOrderK(BiTree T, Status& i, Status k)
{
	TElemType p = '#';
	if (T == NULL)return '#';
	if (i == k)return T->data;
	i++;
	if (T->lchild)
		p = visitsPreOrderK(T->lchild, i, k);
	if (T->rchild && p == '#')
		p = visitsPreOrderK(T->rchild, i, k);
	return p;
}
//特殊3，辅助求值为x的结点为根的子树深度
Status depth(BiTree T)
{
	int depl, depr;
	if (T == NULL)return 0;
	else
	{
		depl = depth(T->lchild);
		depr = depth(T->rchild);
		return 1 + (depl > depr ? depl : depr);
	}
}
 
//创建三叉树
TriTree CreateTriTree(TElemType* tree, Status& i)
{
	TriTree T;
	TElemType node = tree[i++];
	if (node=='#')
	{
		T = NULL; //T是空树
	}
	else 
	{
		T = (TriTree)malloc(sizeof(TriTNode));
		if (T == NULL)
			return NULL;
		T->data = node;
		T->mark = 0;
		T->parent = NULL;
		T->lchild = CreateTriTree(tree, i); //构建左子树
		if (T->lchild != NULL)
		{
			T->lchild->parent = T;
		}   //如果左子树存在，则赋其双亲值
		T->rchild = CreateTriTree(tree, i); //构建右子树
		if (T->rchild != NULL)
		{
			T->rchild->parent = T;      //如果右子树存在，则赋其双亲值
		}
	}
	return T;
}
 
//创建二叉树，初始化
Status InitBiTree(BiTree& T) 
{
	T = NULL;
	return OK;
}
 
//创建一棵二叉树T，其中根结点的值为e，L和R分别为左子树和右子树
BiTree MakeBiTree(TElemType e, BiTree L, BiTree R)
{
	BiTree T;
	T = (BiTNode*)malloc(sizeof(BiTNode));
	if (T==NULL) 
	{
		return NULL;
	}
	T->data = e;
	T->lchild = L;
	T->rchild = R;
	return T;
}
 
//先序构造二叉树
BiTree CreateBiTree(TElemType* T, Status& i, Status&tag)
{
	BiTree temp;
	TElemType ch;
	int len;
	len = strlen(T);
	ch = T[i++];
	if (i>len)
	{
		tag = 0;
		printf("第%d个数据输入错误或不存在，请重新输入\n",i);
		temp = NULL;
		return ERROR;
	}
	else if ('#' == ch)InitBiTree(temp);//创建空树
	else
	{
		temp = MakeBiTree(ch, NULL, NULL);
		temp->lchild = CreateBiTree(T, i,tag);
		temp->rchild = CreateBiTree(T, i,tag);
	}
	return temp;
}
 
//先序遍历二叉树（使用栈的非递归）
Status PreOrderTraverse(BiTree T, Status(*visit)(TElemType e))
{
	BStack s;
	InitStack(s);
	BiTree p = T;
	while (p != NULL || !StackEmpty_BS(s))
	{
		if (p != NULL)
		{
			visit(p->data);
			Push_BS(s, p);
			p = p->lchild;
		}
		else
		{
			Pop_Bs(s, p);
			p = p->rchild;
		}
	}
	return OK;
}
 
//中序遍历二叉树（递归）
void InOrderTraverse(BiTree T)
{
	if (T)
	{
		InOrderTraverse(T->lchild);       //前序遍历左子树
		printf("%c", T->data);              //访问根结点
		InOrderTraverse(T->rchild);       //前序遍历右子树
	}
}
 
//后序遍历三叉树(三叉树)
void PostOrder(TriTree bt, Status(*visit)(TElemType e))
{
	TriTree p = bt;
	// visit(p->data);
	while (p) {
		while (p->mark == 0) {  //先遍历左孩子
			p->mark = 1;
			if (p->lchild)
				p = p->lchild;
		}
		while (p->mark == 1) {  //再遍历右孩子
			p->mark = 2;
			if (p->rchild)
				p = p->rchild;
		}
		if (p->mark == 2) {
			visit(p->data);
			p = p->parent;
		}
	}
}
 
//销毁二叉树
void DestroyBiTree(BiTree& T)
{
	if (T == NULL)return;
	else
	{
		DestroyBiTree(T->lchild);
		DestroyBiTree(T->rchild);
		free(T);
		T = NULL;
	}
}
 
 
//对二叉树判空，空则返回TURE，否则返回FALSE
Status BiTreeEmpty(BiTree T)
{
	if (T == NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
 
//将一棵二叉树分解为根，左子树，右子树三个部分
Status BreakBiTree(BiTree& T)
{
	BiTree L, R;
	if (T == NULL)return ERROR;
	else
	{
		L = T->lchild;
		R = T->rchild;
		T->lchild = NULL;
		T->rchild = NULL;
		printf("根结点为（先序）：");
		PreOrderTraverse(T,visit);
		printf("\n");
		printf("左子树为（先序）：");
		PreOrderTraverse(L, visit);
		printf("\n");
		printf("右子树为（先序）：");
		PreOrderTraverse(R, visit);
		printf("\n");
		return OK;
	}
}
 
//分离左子树
Status Breakleft(BiTree& T)
{
	BiTree l;
	if (T == NULL)return ERROR;
	l = T->lchild;
	T->lchild=NULL;
	printf("被分离的左子树为(先序)：");
	PreOrderTraverse(l, visit);
	printf("\n");
	printf("分离后的原树为(先序):");
	PreOrderTraverse(T, visit);
	return OK;
}
 
//分离右子树
Status Breakright(BiTree& T)
{
	BiTree r;
	if (T == NULL)return ERROR;
	r = T->rchild;
	T->rchild = NULL;
	printf("被分离的右子树为(先序)：");
	PreOrderTraverse(r, visit);
	printf("\n");
	printf("分离后的原树为(先序):");
	PreOrderTraverse(T, visit);
	return OK;
}
 
//替换左子树。若T非空，则用LT替换T的左子树，并用LT返回T的原有左子树
Status ReplaceLeft(BiTree& T, BiTree& LT)
{
	BiTree temp;
	if (T == NULL)return ERROR;
	temp = T->lchild;
	T->lchild = LT;
	LT = temp;
	return OK;
}
 
//替换右子树。若T非空，则用RT替换T的右子树，并用RT返回T的原有右子树
Status ReplaceRight(BiTree& T, BiTree& RT)
{
	BiTree temp;
	if (T == NULL)return ERROR;
	temp = T->rchild;
	T->rchild = RT;
	RT = temp;
	return OK;
}
 
 
//递归算法，求对二叉树T先序遍历时第k个访问到的结点的值
TElemType PreOrderK(BiTree T, Status k)
{
	int x = 1;
	return visitsPreOrderK(T, x, k);
}
 
//求二叉树的叶子数
Status Leaves(BiTree T)
{
	if (T == NULL)return 0;
	else
	{
		if (T->lchild == NULL && T->rchild == NULL)return 1;
		else
			return Leaves(T->lchild) + Leaves(T->rchild);
	}
}
 
//求结点数
Status Node(BiTree T,int& num)
{
	if (T)
	{
		num++;
		Node(T->lchild, num);
		Node(T->rchild, num);
	}
	else return ERROR;
	return OK;
}
 
 
//判断是否为小根二叉树，返回TURE则是
Status SmallBiTree(BiTree T)
{  
	int l, r;
	int cur;
	if (T == NULL)return TRUE;
	if (T->lchild != NULL && T->rchild != NULL)
	{
 
		if (T->data <= T->lchild->data && T->data <= T->rchild->data)
		{
			l = SmallBiTree(T->lchild);
			r = SmallBiTree(T->rchild);
			cur = l & r;
		}
		else cur = 0;
		return cur;
	}
	if (T->lchild == NULL && T->rchild != NULL)
	{
		if (T->data <= T->rchild->data)
		{
			r = SmallBiTree(T->rchild);
			cur = r;
		}
		else
			cur = 0;
		return cur;
	}
	if (T->rchild == NULL && T->lchild != NULL)
	{
		if (T->data <= T->lchild->data)
		{
			l = SmallBiTree(T->lchild);
			cur = l;
		}
		else
			cur = 0;
		return cur;
	}
	if (T->lchild == NULL && T->rchild == NULL)
	{
		return TRUE;
	}
}
 
//判断二叉树中是否存在元素为x的结点，是则返回ok
Status SearchX(BiTree T, TElemType x)
{ 
	if (T == NULL)return ERROR;
	else
	{
		if (T->data == x)return OK;
		else
		{
			return SearchX(T->lchild, x) | SearchX(T->rchild, x);
		}
	}
}
 
//判断二叉树是否为正则二叉树(度为1的结点个数为0)
Status RegularBiTree(BiTree T)
{ 
	if (T == NULL)return TRUE;
	else
	{
		if (T->lchild == NULL && T->rchild == NULL)
		{
			return TRUE;
		}
		else if (T->lchild != NULL && T->rchild != NULL)
		{
			int l, r;
			l = RegularBiTree(T->lchild);
			r = RegularBiTree(T->rchild);
			return l & r;
		}
		else
			return ERROR;
	}
}
 
//将所有结点左右子树交换
void ExchangeSubTree(BiTree& T)
{
	if (T == NULL)return;
	BiTree l, r;
	l = T->lchild;
	r = T->rchild;
	T->lchild = r;
	T->rchild = l;
	ExchangeSubTree(T->rchild);
	ExchangeSubTree(T->lchild);
}
 
//求以x为根的结点的子树的深度
Status Depthx(BiTree T, TElemType x)
{
	int depth(BiTree T);
	int d;
	if (T == NULL)return ERROR;
	if (T->data != x)
	{
		int l, r;
		l = Depthx(T->lchild, x);
		r = Depthx(T->rchild, x);
		d = l > r ? l : r;
		return d;
	}
	else
	{
		return depth(T);
	}
 
}
 
//求树中分支结点数
Status BranchNodes(BiTree T)
{
	if (T == NULL)return 0;
	else
	{
		if (T->lchild != NULL || T->rchild != NULL)
		{
			return 1 + BranchNodes(T->lchild) + BranchNodes(T->rchild);
		}
		if (T->rchild == NULL && T->lchild == NULL)
		{
			return 0;
		}
	}
}
 
//判断两个二叉树是否相似
Status Similar(BiTree T1, BiTree T2)
{  
	if (T1 == NULL && T2 == NULL)return TRUE;
	else if (T1 == NULL && T2 != NULL)return FALSE;
	else if (T1 != NULL && T2 == NULL)return FALSE;
	else
	{
		if (Similar(T1->lchild, T2->lchild) == TRUE && Similar(T1->rchild, T2->rchild) == TRUE)return TRUE;
		else return FALSE;
	}
}
#include<stdio.h>
#include<stdlib.h>
#include"BinaryTree.h"
 
 
//创建二叉树
Status InitBiTree(BiTree& T); 
 
//创建一棵二叉树T，其中根结点的值为e，L和R分别为左子树和右子树
BiTree MakeBiTree(TElemType e, BiTree L, BiTree R);
 
//销毁二叉树
void DestroyBiTree(BiTree& T);
 
//对二叉树判空，空则返回TURE，否则返回FALSE
Status BiTreeEmpty(BiTree T);
 
//将一棵二叉树分解为根，左子树，右子树三个部分
Status BreakBiTree(BiTree& T);
 
//分离左子树
Status Breakleft(BiTree& T);
 
//分离右子树
Status Breakright(BiTree& T);
 
//替换左子树。若T非空，则用LT替换T的左子树，并用LT返回T的原有左子树
Status ReplaceLeft(BiTree& T, BiTree& LT);
 
//替换右子树。若T非空，则用RT替换T的右子树，并用RT返回T的原有右子树
Status ReplaceRight(BiTree& T, BiTree& RT);
 
//先序构造二叉树
BiTree CreateBiTree(TElemType* T, Status& i, Status& tag);//defBT为输入的数组
 
//递归算法，求对二叉树T先序遍历时第k个访问到的结点的值
TElemType PreOrderK(BiTree T, Status k);
 
//求二叉树的叶子数
Status Leaves(BiTree T);
 
//求二叉树结点数
Status Node(BiTree T, Status& num);
 
//判断是否为小根二叉树，返回TURE则是
Status SmallBiTree(BiTree T);
 
//判断二叉树中是否存在元素为x的结点，是则返回ok
Status SearchX(BiTree T, TElemType x);
 
//判断二叉树是否为正则二叉树(度为1的结点个数为0)
Status RegularBiTree(BiTree T);
 
//将所有结点左右子树交换
void ExchangeSubTree(BiTree& T);
 
//求树中分支结点数
Status BranchNodes(BiTree T);
 
//判断两个二叉树是否相似
Status Similar(BiTree T1, BiTree T2);
 
 
//先序遍历二叉树（使用栈的非递归）
Status PreOrderTraverse(BiTree T);
 
//中序遍历二叉树(递归)
void InOrderTraverse(TriTree T, Status(*visit)(TElemType e));
 
//后序遍历三叉树
void PostOrder(TriTree bt, Status(*visit)(TElemType e));
 
//创建三叉树
TriTree CreateTriTree(TElemType* tree, Status& i);
 
//特殊1，访问结点的值
Status visit(TElemType e);
//特殊2，配合用于求对二叉树T先序遍历时第k个访问到的结点的值
TElemType visitsPreOrderK(BiTree T, Status& i, Status k);
//特殊3，辅助求值为x的结点为根的子树深度
Status depth(BiTree T);