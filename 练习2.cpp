int main()
{
    int x,t;//��¼ʱ�䣬λ�õı���
    int n;//��¼��������λ�����ı���
    printf("������ͣ��������λ������");
    cin >> n;//����������������λ����
    char a[7],b[7];//a�����¼ͣ�ų�����ȡ���Լ��˳�ϵͳ�ؼ��֣�b������Ϊ��¼�����ƺ���Ϣ������
    seq s;
    s.top=0;//��ʼ��ջ
    seqq ss;
    ss.topp=0;
    biandao.first=NULL;//��ʼ������ ��β�ÿ�
    biandao.rear =NULL;
    int num = 0;
    printf("����start����ͣ����,takeȡ��,quit�˳���");
	while (cin>>a)//��A���鸳ֵ
    {
		if(strcmp(a,"start")==0){//�ñȽ��ַ����Ƚ�A�����м�¼�Ĺؼ����Ƿ���start���
		printf("���복�ƺ���Ϣ��");
		cin>>b;//���복�ƺ�
		printf("����ͣ��λ�ã�1-%d��:",n);
        cin>>x;//����λ��
		printf("ԭ��ͣ��ʱ��:");
		cin>>t;//����ԤԼʱ��
        if ( s.top >= n )//���ͣ��������
           {
			  printf("����������ֻ�����ڸ����ˣ�����\n");
              Biandao *p;//һ���½��P
              p=(Biandao *)malloc(sizeof(Biandao));
              p->data=x;//��λ�ô����p����data����
              p->time=t;//��ʱ����Ϣ�����p���time����
			  strcpy(p->we,b);//���ַ������ƺ�����b��ŵ��ƺ���Ϣ���Ƶ�p����we��
              num++;  
              p->next=NULL;//��P����next���ÿ�
                if (biandao.rear != NULL){//��β��Ϊ��
                    biandao.rear->next=p;//��p������Ϣ��ֵ��β
                    biandao.rear=p;
				}
                if (biandao.first==NULL){//��ͷΪ��
                    biandao.first=p;//��p������Ϣ��ֵ����ͷ
				}
                printf("����Ϊ��");
				puts(biandao.first->we);//�����ͷָ��ָ���we����Ϣ
				printf("\n�ڱ���ĵ�%dλ�ã�ʱ��Ϊ%d\n",num,t);
 
            }
            else//ͣ����δ��
            {
			   s.top=0;//��top��Ϊ0
			   for(int i=0;i<x;i++){//�ҵ�Ҫ����ջ��λ��
                s.top++;
			   }
			    bus[s.top].num=x;//��λ����Ϣ�����num
                bus[s.top].intime=t;//��ʱ����Ϣ�����intime
				strcpy(bus[s.top].l,b);//��b��ŵĳ��ƺ���Ϣ���l
            }
			  printf("����Ϊ��");
			  puts(bus[s.top].l);//���topλ���ϵ�l
		      printf("ͣ�����ĵ�%dλ��,ͣ��ʱ��Ϊ%d\n",s.top,bus[s.top].intime);
		      printf("start����ͣ��,takeȡ��,quit�˳�:");
		}
		else if (strcmp(a,"take")==0)//���a��¼�Ĺؼ��ֵ���take
	      {    
		   memset(b,0,sizeof b);//��b�����ÿ�
		   printf("���복�ƺţ�1-%d��:",n);
           cin>>b;//��¼������Ϣ
           printf("����ͣ��ʱ�䣺");
		   cin>>t; //��¼ʱ��
            if (s.top == 0)//ջ��
            {
                printf("������� ��������\n");//�������
				printf("start����ͣ��,takeȡ��,quit�˳�:");
				continue;//����whlie ѭ�����¿�ʼ
            }
 
            else
            {
                int nu=0;//��¼λ�ñ���
                for (int i=0;i<=n;i++)//�������Ƿ���������
                {
					if (strcmp(bus[i].l, b)==0)//���������Ϣ���������ĳ�����Ϣ��ƥ���
                    {
                        nu=i;
					    if(t>bus[nu].intime){//ͣ��ʱ�����ԤԼʱ��
				        printf("���Գ�ʱ������ʱ�䰴ÿСʱ6���շ�,ԭ��5��"); 
                        printf("\nͣ��ʱ��%d, ���� %d \n", t ,bus[nu].intime*5+bus[nu].intime*6 );
                        }else{//ͣ��ʱ��С��ԤԼʱ��
                        printf("���Գ�ʱ������ʱ�䰴ÿСʱ6���շ�,ԭ��5��"); 
                        printf("\nͣ��ʱ��%d, ���� %d \n", t ,bus[nu].intime*5);
				       }
						for (int i=nu ;i<=s.top;i++)//��ͣ��վ
                      {
                         bus[i]=bus[i+1];
                       }
                        s.top--;
                    }
                }
				if(nu==0){//���������û�иó���
				  printf("���������������� �ȴ��������������ѳ�������ſ��Խ���ͣ������\n");
				  printf("start����ͣ��,takeȡ��,quit�˳�:");
				  continue;//�����ϲ�
				  
				}
                if (biandao.first!=NULL)//���������г�
                {
					s.top++;//top��һ
                    bus[s.top].num = biandao.first->data;
					bus[s.top].intime = biandao.first->time;
					strcpy(bus[s.top].l,biandao.first->we);
                    num--;
                    Biandao *q;
                    q=biandao.first;
                    biandao.first=biandao.first->next;
                    free(q);
					printf("����Ϊ��");
					puts(bus[s.top].l);
					printf("�Ѿ�����ͣ����������");
					printf("��ͣ�����ĵ�%dλ��,ͣ��ʱ��Ϊ%d\n",s.top,bus[s.top].intime);

                }
            }
			printf("start����ͣ��,takeȡ��,quit�˳�:");
          }
		else if(strcmp(a,"quit")==0){
			printf("��лʹ�ñ�ͣ����ϵͳ����");
		    exit(1);
          }
     }
}
	
;