#include <stdio.h>
#include <stdlib.h>
#define N 5
#define V 20

//��Ʒ��Ϣ
typedef struct {
    int gno;  //��Ʒ���
    int gv;   //��Ʒ���
}EGoods;

//��Ʒ���
typedef struct node{
    int gno;                //��Ʒ���
    struct node * link;     //��Ʒ����ָ��
}GoodsLink;

//���ӽ��
typedef struct box{
    int restV;          //����ʣ�����
    GoodsLink * hg;     //����Ҫ����Ʒ����ָ��
    struct box *next;  //���ӵ�ָ��
}BoxLink;

//�����齵������
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
        printf("��%d����Ʒ�����Ϊ%d\n",g[k].gno,g[k].gv);
}

//װ��
BoxLink * packingBox(EGoods * g){
    BoxLink *hbox = NULL;
    BoxLink *pbox, *tbox;
    GoodsLink *newg,*q;
    //����������Ʒ
    for (int i = 0; i < N; i++){
        //����������
        for (pbox = hbox; pbox&&pbox->restV<g[i].gv; pbox = pbox->next);
        //��������������
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
        //����Ʒ
          // i>������Ʒ���
        newg = (GoodsLink *)malloc(sizeof(GoodsLink));
        newg->gno = g[i].gno;
        newg->link = NULL;
          // ii>����
        for (q = pbox->hg; q&&q->link; q = q->link);
        if (!q)
            pbox->hg = newg;
        else
            q->link = newg;
          // iii>�����������
        pbox->restV -= g[i].gv;
    }
    return hbox;
}

//���������
void printBox(BoxLink *hbox){
    int cnt = 0;
    BoxLink * pbox;
    GoodsLink *q;
    for (pbox = hbox; pbox; pbox = pbox->next){
        printf("��%d�����ӣ�\n",++cnt);
        for (q = pbox->hg; q; q = q->link)
            printf("��Ʒ���Ϊ��%d\n",q->gno);
        printf("\n");
    }
}

int main(void){
    //��ʼ����Ʒ��Ϣ
    EGoods *g = (EGoods *)malloc(N*sizeof(EGoods));
    BoxLink *hbox;
    for (int i = 0; i < N; ++i){
        g[i].gno = i + 1;
        printf("��������Ʒ�����");
        scanf("%d",&g[i].gv);
    }
    sortD(g);
    printf("\n");
    hbox=packingBox(g);
    printBox(hbox);
    return 0;
}