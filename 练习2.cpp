int main()
{
    int x,t;//记录时间，位置的变量
    int n;//记录主车道车位数量的变量
    printf("请输入停车场主车位数量：");
    cin >> n;//键盘输入主车道车位数量
    char a[7],b[7];//a数组记录停放车辆和取车以及退出系统关键字，b数组作为记录车辆牌号信息的数组
    seq s;
    s.top=0;//初始化栈
    seqq ss;
    ss.topp=0;
    biandao.first=NULL;//初始化链队 首尾置空
    biandao.rear =NULL;
    int num = 0;
    printf("输入start进入停车厂,take取车,quit退出：");
	while (cin>>a)//给A数组赋值
    {
		if(strcmp(a,"start")==0){//用比较字符串比较A数组中记录的关键字是否与start相等
		printf("输入车牌号信息：");
		cin>>b;//输入车牌号
		printf("输入停车位置（1-%d）:",n);
        cin>>x;//输入位置
		printf("原定停车时间:");
		cin>>t;//输入预约时间
        if ( s.top >= n )//如果停车场已满
           {
			  printf("主道已满，只能听在辅道了！！！\n");
              Biandao *p;//一个新结点P
              p=(Biandao *)malloc(sizeof(Biandao));
              p->data=x;//把位置存放在p结点的data域中
              p->time=t;//把时间信息存放在p结点time域中
			  strcpy(p->we,b);//用字符串复制函数把b存放的牌号信息复制到p结点的we域
              num++;  
              p->next=NULL;//将P结点的next域置空
                if (biandao.rear != NULL){//队尾不为空
                    biandao.rear->next=p;//将p结点的信息赋值队尾
                    biandao.rear=p;
				}
                if (biandao.first==NULL){//队头为空
                    biandao.first=p;//将p结点的信息赋值到队头
				}
                printf("车牌为：");
				puts(biandao.first->we);//输出队头指针指向的we的信息
				printf("\n在便道的第%d位置，时间为%d\n",num,t);
 
            }
            else//停车场未满
            {
			   s.top=0;//将top置为0
			   for(int i=0;i<x;i++){//找到要存入栈的位置
                s.top++;
			   }
			    bus[s.top].num=x;//将位置信息存放在num
                bus[s.top].intime=t;//将时间信息存放在intime
				strcpy(bus[s.top].l,b);//将b存放的车牌号信息存放l
            }
			  printf("车牌为：");
			  puts(bus[s.top].l);//输出top位置上的l
		      printf("停车场的第%d位置,停车时间为%d\n",s.top,bus[s.top].intime);
		      printf("start继续停车,take取车,quit退出:");
		}
		else if (strcmp(a,"take")==0)//如果a记录的关键字等于take
	      {    
		   memset(b,0,sizeof b);//将b数组置空
		   printf("输入车牌号（1-%d）:",n);
           cin>>b;//记录车牌信息
           printf("输入停留时间：");
		   cin>>t; //记录时间
            if (s.top == 0)//栈空
            {
                printf("输入错误 重新输入\n");//输出错误
				printf("start继续停车,take取车,quit退出:");
				continue;//返回whlie 循环重新开始
            }
 
            else
            {
                int nu=0;//记录位置变量
                for (int i=0;i<=n;i++)//看车辆是否在主车道
                {
					if (strcmp(bus[i].l, b)==0)//如果车辆信息与主车道的车辆信息有匹配的
                    {
                        nu=i;
					    if(t>bus[nu].intime){//停留时间大于预约时间
				        printf("你以超时，超过时间按每小时6块收费,原价5块"); 
                        printf("\n停留时间%d, 费用 %d \n", t ,bus[nu].intime*5+bus[nu].intime*6 );
                        }else{//停留时间小于预约时间
                        printf("你以超时，超过时间按每小时6块收费,原价5块"); 
                        printf("\n停留时间%d, 费用 %d \n", t ,bus[nu].intime*5);
				       }
						for (int i=nu ;i<=s.top;i++)//出停车站
                      {
                         bus[i]=bus[i+1];
                       }
                        s.top--;
                    }
                }
				if(nu==0){//如果主车道没有该车辆
				  printf("车量不在主车道！ 等待主车道的主车把车开走你才可以进入停车场！\n");
				  printf("start继续停车,take取车,quit退出:");
				  continue;//返回上层
				  
				}
                if (biandao.first!=NULL)//如果便道上有车
                {
					s.top++;//top加一
                    bus[s.top].num = biandao.first->data;
					bus[s.top].intime = biandao.first->time;
					strcpy(bus[s.top].l,biandao.first->we);
                    num--;
                    Biandao *q;
                    q=biandao.first;
                    biandao.first=biandao.first->next;
                    free(q);
					printf("车牌为：");
					puts(bus[s.top].l);
					printf("已经进入停车主车道！");
					printf("在停车场的第%d位置,停车时间为%d\n",s.top,bus[s.top].intime);

                }
            }
			printf("start继续停车,take取车,quit退出:");
          }
		else if(strcmp(a,"quit")==0){
			printf("感谢使用本停车场系统！！");
		    exit(1);
          }
     }
}
	
;