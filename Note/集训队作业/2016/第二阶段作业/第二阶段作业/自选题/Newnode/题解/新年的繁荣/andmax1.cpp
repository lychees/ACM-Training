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

const int N=100005,M=1<<20;

int n,m,X[N],fa[N],Min[M],Max[M],val[M],pos[M];

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
	scanf("%d%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&X[i]),fa[i]=i;
	for(int t=0;t<n-1;)
	{
		for(int i=0;i<M;i++)
			Min[i]=n+1,Max[i]=0,val[i]=-1,pos[i]=i;
		for(int i=1;i<=n;i++)
		{
			int t=getfa(i),w=(M-1)^X[i];
			Min[w]=min(Min[w],t);Max[w]=max(Max[w],t);
		}
		for(int i=0;i<20;i++)
			for(int j=0;j<M;j++)
				if(j&(1<<i))
					Min[j]=min(Min[j],Min[j^(1<<i)]),Max[j]=max(Max[j],Max[j^(1<<i)]);
		for(int i=1;i<=n;i++)
		{
			int f=getfa(i),w=M-1,L=0;
			for(int j=19;~j;j--)
				if(X[i]&(1<<j))
				{
					int p=w^(1<<j);
					if(Max[p]&&(Max[p]!=f||Min[p]!=f))
						w=p,L+=1<<j;
				}
			if(val[f]<L)
				val[f]=L,pos[f]=Max[w]!=f?Max[w]:Min[w];
		}
		for(int i=1;i<=n;i++)
		{
			if(val[i]!=-1)
			{
				int u=getfa(i),v=getfa(pos[i]);
				if(u!=v)
					t++,Ans+=val[i],fa[u]=v;
			}
		}
	}
	cout<<Ans<<endl;
	return 0;
}

