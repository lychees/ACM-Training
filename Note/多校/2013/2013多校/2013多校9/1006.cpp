/* ***********************************************
Author        :kuangbin
Created Time  :2013/8/20 13:40:03
File Name     :F:\2013ACM练习\2013多校9\1006.cpp
************************************************ */

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
const int MAXN=100010;
int t1[MAXN],t2[MAXN],c[MAXN];//求SA数组需要的中间变量，不需要赋值
//待排序的字符串放在s数组中，从s[0]到s[n-1],长度为n,且最大值小于m,
//除s[n-1]外的所有s[i]都大于0，r[n-1]=0
//函数结束以后结果放在sa数组中
bool cmp(int *r,int a,int b,int l)
{
	return r[a] == r[b] && r[a+l] == r[b+l];
}
void da(int str[],int sa[],int rank[],int height[],int n,int m)
{
    n++;
    int i, j, p, *x = t1, *y = t2;
    //第一轮基数排序，如果s的最大值很大，可改为快速排序
    for(i = 0;i < m;i++)c[i] = 0;
    for(i = 0;i < n;i++)c[x[i] = str[i]]++;
    for(i = 1;i < m;i++)c[i] += c[i-1];
    for(i = n-1;i >= 0;i--)sa[--c[x[i]]] = i;
    for(j = 1;j <= n; j <<= 1)
    {
        p = 0;
        //直接利用sa数组排序第二关键字
        for(i = n-j; i < n; i++)y[p++] = i;//后面的j个数第二关键字为空的最小
        for(i = 0; i < n; i++)if(sa[i] >= j)y[p++] = sa[i] - j;
        //这样数组y保存的就是按照第二关键字排序的结果
        //基数排序第一关键字
        for(i = 0; i < m; i++)c[i] = 0;
        for(i = 0; i < n; i++)c[x[y[i]]]++;
        for(i = 1; i < m;i++)c[i] += c[i-1];
        for(i = n-1; i >= 0;i--)sa[--c[x[y[i]]]] = y[i];
        //根据sa和x数组计算新的x数组
        swap(x,y);
        p = 1; x[sa[0]] = 0;
        for(i = 1;i < n;i++)
            x[sa[i]] = cmp(y,sa[i-1],sa[i],j)?p-1:p++;
        if(p >= n)break;
        m = p;//下次基数排序的最大值
    }
    int k = 0;
    n--;
	for(i = 0;i <= n;i++)rank[sa[i]] = i;
    for(i = 0;i < n;i++)
    {
        if(k)k--;
        j = sa[rank[i]-1];
        while(str[i+k] == str[j+k])k++;
        height[rank[i]] = k;
    }
}
int rank[MAXN],height[MAXN];
int RMQ[MAXN];
int mm[MAXN];
int best[20][MAXN];
void initRMQ(int n)
{
    mm[0]=-1;
    for(int i=1;i<=n;i++)
        mm[i]=((i&(i-1))==0)?mm[i-1]+1:mm[i-1];
    for(int i=1;i<=n;i++)best[0][i]=i;
    for(int i=1;i<=mm[n];i++)
        for(int j=1;j+(1<<i)-1<=n;j++)
        {
            int a=best[i-1][j];
            int b=best[i-1][j+(1<<(i-1))];
            if(RMQ[a]<RMQ[b])best[i][j]=a;
            else best[i][j]=b;
        }
}
int askRMQ(int a,int b)
{
    int t;
    t=mm[b-a+1];
    b-=(1<<t)-1;
    a=best[t][a];b=best[t][b];
    return RMQ[a]<RMQ[b]?a:b;
}
int lcp(int a,int b)
{
    a=rank[a];b=rank[b];
    if(a>b)swap(a,b);
    return height[askRMQ(a+1,b)];
}
char str[MAXN];
int r[MAXN];
int sa[MAXN];
int A[MAXN],B[MAXN];
int calc(int n)
{
	if(n == 0)return 1;
	int ret = 0;
	while(n)
	{
		ret++;
		n /= 10;
	}
	return ret;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(scanf("%s",str)==1)
	{
		int n = strlen(str);
		for(int i = 0;i < n;i++)
			r[i] = str[i];
		r[n] = 0;
		da(r,sa,rank,height,n,128);
		for(int i = 1;i <= n;i++)
			RMQ[i] = height[i];
		initRMQ(n);
		int k,u,v;
		long long ans1 = 0, ans2 = 0;
		scanf("%d",&k);
		for(int i = 0;i < k;i++)
		{
			scanf("%d%d",&A[i],&B[i]);
			if(i == 0)
			{
				ans1 += B[i] - A[i] + 1;
				ans2 += B[i] - A[i] + 3;
				continue;
			}
			int tmp ;
			if(A[i]!= A[i-1])tmp = lcp(A[i],A[i-1]);
			else tmp = 10000000;
			tmp = min(tmp,B[i]-A[i]);
			tmp = min(tmp,B[i-1]-A[i-1]);
			ans1 += B[i] - A[i] + 1;
			ans2 += B[i] - A[i] - tmp + 1;
			ans2 += 1;
			ans2 += calc(tmp);
		}
		printf("%I64d %I64d\n",ans1,ans2);
	}
    return 0;
}
