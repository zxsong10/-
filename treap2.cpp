#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cassert>
using namespace std;
struct Node
{
    Node *ch[2];
    int r,v,s;//s表示节点数

    Node(int v):v(v)
    {
        ch[0]=ch[1]=NULL;
        r=rand();//在cstdlib头声明
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
}; //root全局使用的话可以在这里跟上*root
void rotate(Node* &o,int d)
{
    Node *k=o->ch[d^1];
    o->ch[d^1]=k->ch[d];
    k->ch[d]=o;
    o->maintain();
    k->maintain();
    o=k;
}
void insert(Node* &o,int x)//o子树中事先不存在x
{
    if(o==NULL) o=new Node(x);
    else
    {
        //如这里改成int d=o->cmp(x);
        //就不可以插入相同的值，因为d可能为-1
        int d=x<(o->v)?0:1;
        insert(o->ch[d],x);
        if(o->ch[d]->r > o->r)
            rotate(o,d^1);
    }
    o->maintain();
}

void remove(Node* &o,int x)
{
    if(o==NULL) return ;//空时返回

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
            delete u;//这个要放里面
        }
    }
    else remove(o->ch[d],x);
    if(o) o->maintain();//之前o存在,但是删除节点后o可能就是空NULL了,所以需要先判断o是否为空
}

//返回关键字从小到大排序时的第k个值
//若返回第K大的值，只需要把ch[0]和ch[1]全互换就可以了
int kth(Node* o,int k)
{
    assert(o && k>=1 && k<=o->s);//保证输入合法,根据实际问题返回
    int s=(o->ch[0]==NULL)?0:o->ch[0]->s;
    if(k==s+1) return o->v;
    else if(k<=s) return kth(o->ch[0],k);
    else return kth(o->ch[1],k-s-1);
}

//返回值x在树中的排名,就算x不在o树中也能返回排名
//返回值范围在[1,o->s+1]范围内
int rank(Node* o,int x)
{
    if(o==NULL) return 1;//未找到x;

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
        Node *root=NULL; //初始化为NULL
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
