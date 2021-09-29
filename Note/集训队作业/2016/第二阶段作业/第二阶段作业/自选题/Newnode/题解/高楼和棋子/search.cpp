#include<algorithm>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include  <stdio.h>
#include   <math.h>
#include   <time.h>
#include   <vector>
#include    <queue>
#include      <map>
#include      <set>
using namespace std;

typedef long long LL;

const LL oo=1ll<<60,Lim=200000;

LL N,M,f[Lim+4][65];

bool check(LL X)
{
	if(X<=Lim)
		return f[X][M]>=N;
	LL Now=X,S=X;
	for(int i=2;i<=M;i++)
	{
		if(Now*(long double)(X-i+1)/i>1e18)
			return 1;
		Now=Now*(X-i+1)/i;S=S+Now;
		if(S>=N)
			return 1;
	}
	return S>=N;
}

void solve()
{
	scanf("%lld%lld",&N,&M);
	LL L=1,R=N-1,Ans=N;
	if(f[Lim][M]>=N)
		R=Lim-1,Ans=Lim;
	while(L<=R)
	{
		LL Mid=L+R>>1;
		if(check(Mid))
			Ans=Mid,R=Mid-1;
		else
			L=Mid+1;
	}
	printf("%lld\n",Ans);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("search.in","r",stdin);
	freopen("search.out","w",stdout);
#endif
	for(int i=1;i<=Lim;i++)
		for(int j=1;j<=64;j++)
			f[i][j]=min(oo,f[i-1][j]+f[i-1][j-1]+1);
	int t;cin>>t;
	while(t--)
		solve();
	return 0;
}

