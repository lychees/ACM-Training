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

const int N=1<<20,Mod=1e9+7;

int n,g[N],f[N];

int Pow(int x,int y)
{
	int k=1;
	while(y)
	{
		if(y&1)
			k=k*(LL)x%Mod;
		x=x*(LL)x%Mod;y>>=1;
	}
	return k;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("lcm.in","r",stdin);
	freopen("lcm.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1,t;i<=n;i++)
		scanf("%d",&t),g[t]=1;
	f[1]=1;
	for(int i=2;i<N;i++)
		f[i]=(f[i-1]+f[i-2])%Mod;
	for(int i=N-1;i;i--)
		for(int j=i+i;j<N&&!g[i];j+=i)
			g[i]|=g[j];
	int Ans=1;
	for(int i=N-1;i;i--)
	{
		for(int j=i+i;j<N;j+=i)
			g[i]=(g[i]-g[j]+Mod-1)%(Mod-1);
		Ans=Ans*(LL)Pow(f[i],g[i])%Mod;
	}
	cout<<Ans<<endl;
	return 0;
}

