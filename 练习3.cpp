    struct Node *cur = head;
    while (cur)
    {
        struct Node *copy = (struct Node*)malloc(sizeof(struct Node));
        copy->val = cur->val;  
        //�����ƵĽ����ԭ���Ľ������
        copy->next = cur->next;
        cur->next = copy;
        //ע����븴�ƽ����������������Ĵ��벻��cur = cur->next;���ǣ�
        cur = copy->next;
    }
 
 cur = head; 
    while (cur)
    {
        struct Node *copy = cur->next;//��Ϊ�Ѿ������ƵĽ�����Ӧ��ԭ���������
        if (cur->random == NULL)
        {
            copy->random = NULL;
        }
        else
        {
            copy->random = cur->random->next//������һ���״�㣬��Ϊ��ĿҪ��randomָ�붼Ӧָ���������е��½ڵ�
        }
       
        cur = copy->next;//ʹ�ñ���������ȥ
    }
 
cur = head;
    struct Node *copyHead = NULL;//����������ĵ�ַ
    struct Node *copyTail = NULL;//����ִ��β�����
    while (cur)
    {
        struct Node *copy = cur->next;//ʹ��ÿһ��ѭ������Ӧ����һ��ѭ������Ӧ�Ľ�㣬���Ը��ƵĽ����и���
        struct Node *Next = copy->next;//������������������֮ǰ�ĸ��ƽ��ָ�����һ�����
        //β�����
        if (copyTail == NULL)
        {
            copyHead = copyTail = copy;//��ʱ��������ĵ�ַ
        }
        else
        {
            copyTail->next = cur->next;//copyTail->next���Ƿ����������������������һ���������һ�����
            copyTail = copyTail->next;
        }
 
        cur = copy->next;
        cur = Next;
    }
 
    return copyHead;
	
}
