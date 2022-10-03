    struct Node *cur = head;
    while (cur)
    {
        struct Node *copy = (struct Node*)malloc(sizeof(struct Node));
        copy->val = cur->val;  
        //将复制的结点与原来的结点链接
        copy->next = cur->next;
        cur->next = copy;
        //注意插入复制结点后继续遍历单链表的代码不是cur = cur->next;而是：
        cur = copy->next;
    }
 
 cur = head; 
    while (cur)
    {
        struct Node *copy = cur->next;//因为已经将复制的结点与对应的原结点相链接
        if (cur->random == NULL)
        {
            copy->random = NULL;
        }
        else
        {
            copy->random = cur->random->next//这里是一个易错点，因为题目要求random指针都应指向复制链表中的新节点
        }
       
        cur = copy->next;//使得遍历继续下去
    }
 
cur = head;
    struct Node *copyHead = NULL;//创造新链表的地址
    struct Node *copyTail = NULL;//用来执行尾插操作
    while (cur)
    {
        struct Node *copy = cur->next;//使得每一次循环都对应着这一次循环所对应的结点，即对复制的结点进行更新
        struct Node *Next = copy->next;//用来保存分离出新链表之前的复制结点指向的下一个结点
        //尾插操作
        if (copyTail == NULL)
        {
            copyHead = copyTail = copy;//此时是新链表的地址
        }
        else
        {
            copyTail->next = cur->next;//copyTail->next则是分离出来的新链表中真正的一个结点后的下一个结点
            copyTail = copyTail->next;
        }
 
        cur = copy->next;
        cur = Next;
    }
 
    return copyHead;
	
}
