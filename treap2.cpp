#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cassert>
using namespace std;
struct Node
{
    Node *ch[2];
    int r,v,s;//s��ʾ�ڵ���

    Node(int v):v(v)
    {
        ch[0]=ch[1]=NULL;
        r=rand();//��cstdlibͷ����
        s=1;
    }

    int cmp(int x)
    {
        if(x==v)return -1;
        return x<v?0:1;
    }
    void maintain()
    {
        s=1;
        if(ch[0]!=NULL) s+=ch[0]->s;
        if(ch[1]!=NULL) s+=ch[1]->s;
    }
}; //rootȫ��ʹ�õĻ��������������*root
void rotate(Node* &o,int d)
{
    Node *k=o->ch[d^1];
    o->ch[d^1]=k->ch[d];
    k->ch[d]=o;
    o->maintain();
    k->maintain();
    o=k;
}
void insert(Node* &o,int x)//o���������Ȳ�����x
{
    if(o==NULL) o=new Node(x);
    else
    {
        //������ĳ�int d=o->cmp(x);
        //�Ͳ����Բ�����ͬ��ֵ����Ϊd����Ϊ-1
        int d=x<(o->v)?0:1;
        insert(o->ch[d],x);
        if(o->ch[d]->r > o->r)
            rotate(o,d^1);
    }
    o->maintain();
}

void remove(Node* &o,int x)
{
    if(o==NULL) return ;//��ʱ����

    int d=o->cmp(x);
    if(d==-1)
    {
        Node *u=o;
        if(o->ch[0] && o->ch[1])
        {
            int d2=(o->ch[0]->r < o->ch[1]->r)?0:1;
            rotate(o,d2);
            remove(o->ch[d2],x);
        }
        else
        {
            if(o->ch[0]==NULL) o=o->ch[1];
            else o=o->ch[0];
            delete u;//���Ҫ������
        }
    }
    else remove(o->ch[d],x);
    if(o) o->maintain();//֮ǰo����,����ɾ���ڵ��o���ܾ��ǿ�NULL��,������Ҫ���ж�o�Ƿ�Ϊ��
}

//���عؼ��ִ�С��������ʱ�ĵ�k��ֵ
//�����ص�K���ֵ��ֻ��Ҫ��ch[0]��ch[1]ȫ�����Ϳ�����
int kth(Node* o,int k)
{
    assert(o && k>=1 && k<=o->s);//��֤����Ϸ�,����ʵ�����ⷵ��
    int s=(o->ch[0]==NULL)?0:o->ch[0]->s;
    if(k==s+1) return o->v;
    else if(k<=s) return kth(o->ch[0],k);
    else return kth(o->ch[1],k-s-1);
}

//����ֵx�����е�����,����x����o����Ҳ�ܷ�������
//����ֵ��Χ��[1,o->s+1]��Χ��
int rank(Node* o,int x)
{
    if(o==NULL) return 1;//δ�ҵ�x;

    int num= o->ch[0]==NULL ? 0:o->ch[0]->s;
    if(x==o->v) return num+1;
    else if(x < o->v) return rank(o->ch[0],x);
    else return rank(o->ch[1],x)+num+1;
}


int main()
{
    int n=0;
    while(scanf("%d",&n)==1 && n)
    {
        Node *root=NULL; //��ʼ��ΪNULL
        for(int i=0; i<n; i++)
        {
            int x;
            scanf("%d",&x);
            if(root==NULL) root=new Node(x);
            else insert(root,x);
        }

        int v;
        while(scanf("%d",&v)==1)
        {
            printf("%d\n",rank(root,v));
        }
    }
    return 0;
}
