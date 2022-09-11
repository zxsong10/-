#ifndef SplayTree_h
#define SplayTree_h
 
#include <stdio.h>
#include <stdlib.h>
typedef struct SplayTree *PSplayTree;
typedef int ElemType;
 
struct SplayTree {
    ElemType elem;
    PSplayTree left;
    PSplayTree right;
};
 
static PSplayTree NullNode;
 
/* ��ʼ�� */
PSplayTree Initialize();
/* ���� */
PSplayTree Insert(PSplayTree T,ElemType Item);
/* ɾ�� */
PSplayTree Remove(PSplayTree T,ElemType Item);
/* ���� */
void Travel(PSplayTree T);
 
#endif /* SplayTree_h */
#include "SplayTree.h"
 
/* ���ݹؼ�ֵItemչ�� */
static PSplayTree Splay(PSplayTree T, ElemType Item);
/* ����ת */
static PSplayTree SingleRotateLeft(PSplayTree T);
/* ����ת */
static PSplayTree SingleRotateRight(PSplayTree T);
 
/* ���ݹؼ�ֵItemչ�� */
static PSplayTree Splay(PSplayTree X, ElemType Item){
    /* ��������ұ��� */
    static struct SplayTree header;
    /* ��������ֵ���ұ�����Сֵ */
    static PSplayTree LeftTreeMax,RightTreeMin;
    
    header.left = header.right = NullNode;
    LeftTreeMax = RightTreeMin = &header;
    
    /* NullNode��ֵΪItem�������ҵ�Itemֵ���߽���ֵ���ĵײ�ʱ��ֹѭ�� */
    NullNode->elem = Item;
   
    while (Item != X->elem) {
        if (Item < X->elem){
            if (Item < X->left->elem)
                X = SingleRotateLeft(X);
            /* ����ײ� */
            if (X->left == NullNode)
                break;
            /* �����ұ� */
            RightTreeMin->left = X;
            RightTreeMin = X;
            X = X->left;
        }else{
            if (Item > X->right->elem)
                X = SingleRotateRight(X);
            if (X->right == NullNode)
                break;
            /* ������� */
            LeftTreeMax->right = X;
            LeftTreeMax = X;
            X = X->right;
        }
    }
    
    /* ��װ */
    LeftTreeMax->right = X->left;
    RightTreeMin->left = X->right;
    X->left = header.right;
    X->right = header.left;
    
    
    return X;
}
 
/* ����ת */
static PSplayTree SingleRotateLeft(PSplayTree T){
    PSplayTree T2 = T->left;
    T->left = T2->right;
    T2->right = T;
    
    return T2;
}
/* ����ת */
static PSplayTree SingleRotateRight(PSplayTree T){
    PSplayTree T2 = T->right;
    T->right = T2->left;
    T2->left = T;
    return T2;
}
 
/* ��ʼ�� */
PSplayTree Initialize(){
    if (NullNode == NULL){
        NullNode = malloc(sizeof(struct SplayTree));
        if (NullNode == NULL)
            exit(EXIT_FAILURE);
        NullNode->left = NullNode->right = NullNode;
    }
    
    return NullNode;
}
/* ���� */
PSplayTree Insert(PSplayTree T,ElemType Item){
    PSplayTree NewNode;
    NewNode = malloc(sizeof(struct SplayTree));
    if (NewNode == NULL)
        exit(EXIT_FAILURE);
    NewNode->elem = Item;
    
    if (T == NullNode) {
        NewNode->left = NewNode->right = NullNode;
        T = NewNode;
    }else{
        T = Splay(T, Item);
        
        if (Item < T->elem){
            NewNode->left = T->left;
            NewNode->right = T;
            T->left = NullNode;
            T = NewNode;
        }else if (Item > T->elem){
            NewNode->right = T->right;
            NewNode->left = T;
            T->right = NullNode;
            T = NewNode;
        }else if(Item == T->elem){
            /* �ظ�ֵ�������� */
            free(NewNode);
        }
 
    }
    
    
    return T;
    
}
/* ɾ�� */
PSplayTree Remove(PSplayTree T,ElemType Item){
    PSplayTree NewTree;
    if (T != NullNode){
        T = Splay(T, Item);
        if (Item == T->elem){
            /* �ҵ����� */
            if (T->left == NullNode){
                /* �������ǿգ���������Ϊ���� */
                NewTree = T->right;
                
            }else{
                /* ��������Ϊ������ ������չ��������Item�����������κνڵ㡣����չ���Ĺ��̻�������·������ */
                /* һֱ�����ұߵ���Ҷ�ڵ㣬����չ��֮��õ����������������϶��ǿ��� */
                NewTree = T->left;
                NewTree = Splay(NewTree, Item);
                NewTree->right = T->right;
            }
            free(T);
            T = NewTree;
        }
    }
    
    return T;
}
 
 
void Travel(PSplayTree T){
    if (T != NullNode){
        Travel(T->left);
        printf("%d ",T->elem);
        Travel(T->right);
    }
}
#include <stdio.h>
#include "SplayTree.h"
int main(int argc, const char * argv[]) {
    
    PSplayTree T = Initialize();
    T = Insert(T, 1);
    T = Insert(T, 2);
    T = Insert(T, 3);
    T = Insert(T, 4);
    T = Insert(T, 5);
    T = Insert(T, 6);
    T = Remove(T, 1);
    T = Remove(T, 2);
    T = Remove(T, 1);
    Travel(T);
    return 0;
}
