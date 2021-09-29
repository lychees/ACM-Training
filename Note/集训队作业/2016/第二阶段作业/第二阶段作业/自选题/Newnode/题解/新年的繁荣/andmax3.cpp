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

const int N=1000005,M=100000005;

int n,m,rt[N],lc[M],rc[M],tot,w,mx;

LL Ans;

inline void Ins(int &x,int y,LL t)
{
	x=++tot;w++;
	if(y>=0)
		if(t&(1ll<<y))
			Ins(rc[x],y-1,t);
		else
			Ins(lc[x],y-1,t);
}

inline int Merge(int x,int y)
{
	w++;
	if(!x||!y)
		return x+y;
	int z=++tot;
	lc[z]=Merge(lc[x],lc[y]);rc[z]=Merge(rc[x],rc[y]);
	return z; 
}

inline void solve(const vector<int>& V,int t)
{
	if(V.size()<2)
		return;
	if(t<0)
		return;
	vector<int> A,B;int rt=0,totnow=tot;
	for(int i=0;i<V.size();i++)
		if(rc[V[i]])
			A.push_back(rc[V[i]]),rt=Merge(Merge(rt,rc[V[i]]),lc[V[i]]);
		else
			B.push_back(lc[V[i]]);
	if(A.size())
		Ans+=(1ll<<t)*(A.size()-1),solve(A,t-1),B.push_back(rt);
	solve(B,t-1);tot=totnow;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("andmax.in","r",stdin);
	freopen("andmax.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	vector<int> V;LL t;
	for(int i=1;i<=n;i++)
		scanf("%lld",&t),Ins(rt[i],17,t),V.push_back(rt[i]);
	solve(V,17);
	cout<<Ans<<endl;
	return 0;
}

