#include <stack>
#include <iostream>
using namespace std;
int main()
{
	stack<int> mystack;
	int x,y,i;
	int len;
	char list[110]={0};
	gets(list);
	for(x=0;list[x];x++)	;
	len=x-1;
 
	for(i=len;i>=0;i--)
	{
		if(list[i]==' ')
			continue;
		else if(list[i]>='0'&&list[i]<='9')
		{
			if(list[i-1]>='0'&&list[i-1]<='9')
			{
				x=list[i-1]-'0';
				y=list[i]-'0';
				x=10*x+y;
				mystack.push(x);
				i--;
			}
			else
			{	x=list[i]-'0';mystack.push(x);}
		}
		else
		{
			x=mystack.top();mystack.pop();
			y=mystack.top();mystack.pop();
			if(list[i]=='+')	x=x+y;
			else if(list[i]=='-')	x=x-y;
			else if(list[i]=='*')	x=x*y;
			else	x=x/y;
			mystack.push(x);
		}
	}
	//print
	x=mystack.top();
	printf("%d",x);
	return 1;
 } 