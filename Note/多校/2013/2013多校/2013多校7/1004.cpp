/* **********************************************
Author      : kuangbin
Created Time: 2013/8/13 15:10:49
File Name   : F:\2013ACM练习\2013多校7\1004.cpp
*********************************************** */

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


using namespace std;

const int MAXN = 50010;
int a[MAXN]; //第i个数
int end[MAXN];//end[i]表示第i个数...一直连接到第n个数对k取模后的值

int len[MAXN];//第i个数的长度

int b[2][220]; //滚动数组，预处理以第i个数结尾的，所有连接成的对k取模得到值的个数

int getlen(int n)//得到n有多少位
{
	int ret = 0;
	while(n)
	{
		ret++;
		n/=10;
	}
	return ret;
}
int Ten[10];//10^i  预处理，本来预处理了很大10^i的，结果发现一预处理这个就超时,T_T



int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,k;
	while(scanf("%d%d",&n,&k) == 2)
	{
		for(int i = 1;i <= n;i++)
		{
		    scanf("%d",&a[i]);
			len[i] = getlen(a[i]);
		}
		Ten[0] = 1;
		for(int i = 1;i < 5;i++)
			Ten[i] = Ten[i-1]*10%k;
		int now = 0;
		memset(b,0,sizeof(b));
		b[now][a[1]%k] = 1;
		long long ans = 0;
		ans += b[now][0];
		for(int i = 2;i <= n;i++)
		{
			memset(b[now^1],0,sizeof(b[now^1]));
			b[now^1][a[i]%k] = 1;
			for(int j = 0;j < k;j++)
			{
				if(b[now][j] == 0)continue;
				int ttt = j*Ten[len[i]]%k+a[i];
				ttt%=k;
				b[now^1][ttt] += b[now][j];
			}
			now^=1;
			ans += b[now][0];

		}
		//前面累加的结果是没有a[n]和a[1]连接的。
		//后面的是a[n]和a[1]连接的计数
		end[n] = a[n]%k;
		int tmp = len[n];
		int SSSS = Ten[len[n]];
		for(int i = n-1;i>= 1;i--)
		{
			end[i] = a[i]*SSSS%k + end[i+1];
			end[i]%=k;
			tmp += len[i];
			SSSS = SSSS*Ten[len[i]]%k;
		}
		tmp = len[1];
		SSSS = Ten[len[1]];
		int tt = a[1]%k;
		for(int i = 1;i < n;i++)
		{
			b[now][end[i]]--;
			for(int j = 0;j < k;j++)
			{
				int ppp = (j*SSSS%k+tt)%k;
				if(ppp == 0)ans += b[now][j];
			}
			tt = tt*Ten[len[i+1]]+a[i+1];
			tt%=k;
			tmp+=len[i+1];
			SSSS = SSSS*Ten[len[i+1]]%k;
		}
		printf("%I64d\n",ans);//T_T 一定要long long,这题貌似是刚好超int~~

	}
    return 0;
}
