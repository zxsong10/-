#include<stdio.h>
 
int max, mi, mj;//定义为全局变量不用来回传
 
//复杂度为O(n^3)
void maxSum_1(int a[], int n) {
	for (int i = 0;i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			int sum = 0;
			//求和的
			for (int k = i; k <= j; k++)
				sum += a[k];
 
			if (sum > max)
			{
				max = sum;
				mi = i;
				mj = j;
			}
 
		}
	}
}
 
 
//O(n^2+n)
void maxSum_2(int a[],int s[],int n) {
	int sum;
	int i=1;
	//初始化s[8]的值
	for (i ; i <= n; i++)
		s[i] = s[i - 1] + a[i - 1];
	
	for ( i ; i <= n; i++)
	{
		for (int j = i; j <= n; j++)
		{
			sum = s[j] - s[i - 1];
			if (sum > max)
			{
				max = sum;
				mi = i - 1;
				mj = j;
			}
		}
	}
}
 
 
//分治法 O(log2^n)
int maxSum_3(int a[], int left, int right) {
 
	int  sum = 0, i;
	int leftMaxSum,rightMaxSum;
	if (left == right)
		return a[left];
	
	else 
	{
		int mid = (left + right) / 2;
		//递归 因为用到中间值所以区间为( ]
		leftMaxSum = maxSum_3(a, left,mid);
		rightMaxSum = maxSum_3(a, mid + 1, right);
		
		//中间部分，从右边开始--
		int m1 = 0,leftSum = 0;
		for (i = mid; i >= left; i--)
		{
			leftSum = leftSum + a[i];
			if (leftSum > m1)
			{
				m1 = leftSum;
				mi = i;
			}
		}
 
		//中间部分，从左边开始++
		int m2 = 0, rightSum = 0;
		for (i = mid + 1; i <= right; i++)
		{
			rightSum = rightSum + a[i];
			if (rightSum > m2)
			{
				m2 = rightSum;
				mj = i;
			}
		}
		sum = m1 + m2;
 
		if (sum < leftMaxSum)
			sum = leftMaxSum;
		if (sum < rightMaxSum)
			sum = rightMaxSum;
 
	}
	return sum;
}
 
 
//O(n^)
int main(void) {
 
	int a[7] = { 3,-2,5,-3,4,7,-6 };
	int s[8] = { 0 };
	max = a[0];
	mi = mj = 0;
 
//	maxSum_1(a, 7);
	
//	maxSum_2(a, s, 7);
 
	max=maxSum_3(a,0,6);
	
	printf(" mi=%d,mj=%d,max=%5d",mi,mj,max);
	return 0;
	 
}
 