/* **********************************************
Author      : kuangbin
Created Time: 2013/8/13 16:39:35
File Name   : F:\2013ACM练习\2013多校7\1010.cpp
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

const int MOD = 1e9+7;
long long pow_m(long long a,long long n)
{
	long long ret = 1;
	long long tmp = a%MOD;
	while(n)
	{
		if(n&1)
		{
			ret *= tmp;
			ret %= MOD;
		}
		tmp *= tmp;
		tmp %= MOD;
		n >>= 1;
	}
	return ret;
}
long long C[300010];
//求ax = 1( mod m) 的x值，就是逆元(0<a<m)
long long inv(long long a,long long m)
{
    if(a == 1)return 1;
    return inv(m%a,m)*(m-m/a)%m;
}
long long ans[300010];
int a[300010];
int num[300010];
int b[300010];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int N,M,K;
	while(scanf("%d%d%d",&N,&M,&K) == 3)
	{
		memset(num,0,sizeof(num));
		for(int i = 1;i <= N;i++)
		{
			scanf("%d",&a[i]);
			num[a[i]]++;
		}
		C[N-K] = 1;
		for(int i = N-K+1;i <= N;i++)
		{
			C[i] = C[i-1]*i%MOD*inv(i-(N-K),MOD)%MOD;
		}
		for(int i = M;i>= 1;i--)
		{
			int cnt = 0;
			long long ss = 0;
			for(int j = 1; j*i <= M;j++)
			{
				cnt += num[i*j];
				if(j > 1)ss = (ss + ans[i*j])%MOD;
			}
			int t = M/i;
			if(t == 1)
			{
				if(cnt == N-K)ans[i] = 1;
				else ans[i] = 0;
				continue;
			}

			if(cnt < N-K)
			{
				ans[i] = 0;
				continue;
			}
			long long tmp = 1;
			//在cnt个中选N-K个为相同的
			tmp =(tmp*C[cnt])%MOD;
			//其余的cnt-(N-K)个有t-1个选择
			tmp = ( tmp * pow_m(t-1,cnt-(N-K)) )%MOD;
			//其余N-cnt个本来就不相同的，有t个选择
			tmp = (tmp * pow_m(t,N-cnt));
			ans[i] = (tmp - ss + MOD)%MOD;
				

		}
		for(int i = 1;i <= M;i++)
		{
			printf("%I64d",ans[i]);
			if(i < M)printf(" ");
			else printf("\n");
		}
		
	}
    return 0;
}
