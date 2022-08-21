#include <stdio.h>
#include <stdlib.h>
#define N 5
#define V 20

//物品信息
typedef struct {
    int gno;  //物品编号
    int gv;   //物品体积
}EGoods;

//物品结点
typedef struct node{
    int gno;                //物品编号
    struct node * link;     //物品结点的指向
}GoodsLink;

//箱子结点
typedef struct box{
    int restV;          //箱子剩余体积
    GoodsLink * hg;     //箱子要挂物品结点的指向
    struct box *next;  //箱子的指向
}BoxLink;

//将数组降序排列
void sortD(EGoods *g){
    EGoods temp;
    for (int i = 0; i < N-1; i++){
        for (int j = 0; j < N  - i-1; j++){
            if (g[j].gv<g[j+1].gv){
                temp = g[j];
                g[j] = g[j+1];
                g[j+1] = temp;
            }
        }
    }
    for (int k = 0; k < N; k++)
        printf("第%d号物品的体积为%d\n",g[k].gno,g[k].gv);
}

//装箱
BoxLink * packingBox(EGoods * g){
    BoxLink *hbox = NULL;
    BoxLink *pbox, *tbox;
    GoodsLink *newg,*q;
    //遍历所有物品
    for (int i = 0; i < N; i++){
        //遍历箱子链
        for (pbox = hbox; pbox&&pbox->restV<g[i].gv; pbox = pbox->next);
        //空箱子则开新箱子
        if (!pbox){
            pbox = (BoxLink *)malloc(sizeof(BoxLink));
            pbox->restV =V;
            pbox->hg=NULL;
            pbox->next = NULL;
            if (!hbox)
                hbox = tbox = pbox;
            else
                tbox = tbox->next = pbox;
        }
        //放物品
          // i>创建物品结点
        newg = (GoodsLink *)malloc(sizeof(GoodsLink));
        newg->gno = g[i].gno;
        newg->link = NULL;
          // ii>挂链
        for (q = pbox->hg; q&&q->link; q = q->link);
        if (!q)
            pbox->hg = newg;
        else
            q->link = newg;
          // iii>重置箱子体积
        pbox->restV -= g[i].gv;
    }
    return hbox;
}

//输出计算结果
void printBox(BoxLink *hbox){
    int cnt = 0;
    BoxLink * pbox;
    GoodsLink *q;
    for (pbox = hbox; pbox; pbox = pbox->next){
        printf("第%d个箱子：\n",++cnt);
        for (q = pbox->hg; q; q = q->link)
            printf("物品编号为：%d\n",q->gno);
        printf("\n");
    }
}

int main(void){
    //初始化物品信息
    EGoods *g = (EGoods *)malloc(N*sizeof(EGoods));
    BoxLink *hbox;
    for (int i = 0; i < N; ++i){
        g[i].gno = i + 1;
        printf("请输入物品体积：");
        scanf("%d",&g[i].gv);
    }
    sortD(g);
    printf("\n");
    hbox=packingBox(g);
    printBox(hbox);
    return 0;
}