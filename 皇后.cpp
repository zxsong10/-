#include<stdio.h>
#include<stdlib.h>

#define max 1000000

int place[max];//�ʺ������С�
int uppertri[2*max-1];//ĳ���ʺ��Ӧ����б��Ϊ135�ȵĶԽ��ߣ�����ÿ���ʺ����ڵ���raw��ȥ���ڵ���col�ټ�������������1��n-1����ʾ�ʺ�������ǶԽ���
int lowtri[2*max-1];//ĳ���ʺ��Ӧ����б��Ϊ45�ȵĶԽ��ߣ�����ÿ���ʺ����ڵ���raw�������ڵ���col����ʾ�ʺ�������ǶԽ���
int flag[max];//��Ϊ��־��flag[i]==1��ʾ��row�еĵ�i�з����˻ʺ�flag[i]==0��ʾ��raw�еĵ�i�л�û�б����ûʺ�
int count=1;//����ʹ��
 
//���Ĳ��֣�n�ʺ������е�ĳһ��raw
void generate(int n,int raw){
    int col;//��
    for(col=0;col<n;col++){
        if(uppertri[raw-col+n-1]==0 && lowtri[raw+col]==0 && flag[col]==0){//if����������弴��ǰ�еĵ�col���Ƿ�����ڷŻʺ�
            //�Ե�raw�е�col�е�λ�ý��С�ռ�족
            flag[col]=1;
            place[raw]=col;
            uppertri[raw-col+n-1]=1;
            lowtri[raw+col]=1;
            //��raw�е�����ˣ��Ϳ�ʼ�ݹ��raw+1�е����
            if(raw<n-1){
                generate(n,raw+1);
            }
            //���ݹ鵽���һ�ж������һ��Ҳ�ҵ��˷��ûʺ��λ�ã���һ�ֻʺ�ڷ�����Ѿ��õ�ȷ���������
            else
            {
                printf("���ǵ�%d�����\n",count);
                for(int i=0;i<n;i++){
                    printf("��%d�У���%d�п���ʹ��\n",i+1,place[i]+1);
                }
                count++;
            }
            flag[col]=0;
            uppertri[raw-col+n-1]=0;
            lowtri[raw+col]=0;           
        }
    }
}

int main(){
    int n;
    printf("������������������");
    scanf("%d",&n);
    generate(n,0);
}
