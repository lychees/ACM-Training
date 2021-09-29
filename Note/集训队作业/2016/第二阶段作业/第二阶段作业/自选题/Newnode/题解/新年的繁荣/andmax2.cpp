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

const int N=100005,M=1<<18;

int n,m,a[M],fa[M];

LL Ans;

inline int getfa(int u)
{
	return fa[u]==u?u:fa[u]=getfa(fa[u]);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("andmax.in","r",stdin);
	freopen("andmax.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1,t;i<=n;i++)
	{
		scanf("%d",&t);
		if(!a[t])
			a[t]=t;
		else
			Ans+=t;
	}
	for(int p=(1<<m)-1;p;p--)
	{
		fa[p]=p;
		for(int i=0;i<m&&!a[p];i++)
			a[p]=a[p|(1<<i)];
		for(int i=0;i<m;i++)
			if(a[p|(1<<i)]&&getfa(a[p])!=getfa(a[p|(1<<i)]))
				Ans+=p,fa[getfa(a[p|(1<<i)])]=getfa(a[p]);
	}
	cout<<Ans<<endl;
	return 0;
}

