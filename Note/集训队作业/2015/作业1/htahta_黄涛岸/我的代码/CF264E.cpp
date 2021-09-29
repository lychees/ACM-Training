#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
using namespace std;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=262144;
int n,m,leaf[maxn],h[maxn],p[maxn],tp[100];
priority_queue<int,vector<int>,greater<int> > Q;
struct segtree
{
	int a[maxn*2];
	void modify(int p,int v)
	{
		for(p=leaf[p],a[p]=v;p>1;p>>=1)a[p>>1]=max(a[p],a[p^1]);
	}
	int ask(int p)
	{
		p=leaf[p];
		int res=a[p];
		for(;p>1;p>>=1)
			if(!(p&1))res=max(res,a[p^1]);
		return res;
	}
}T1,T2;
void build(int p,int l,int r)
{
	if(l==r){leaf[l]=p;return;}
	int mid=(l+r)/2;
	build(p*2,l,mid),build(p*2+1,mid+1,r);
}

int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get(),m=get();
	build(1,1,max(m+20,n));
	for(int i=1,x,y;i<=m;printf("%d\n",T1.a[1]),i++)
		if(get()==1)
		{
			x=get(),y=get()+m-i;
			p[x]=y,Q.push(h[y]=x);
			for(int j=m-i;j<y;j++)
				if(h[j])T1.modify(h[j],0);
			for(int j=y;j>=m-i;j--)
			{
				if(!h[j])continue;
				int res=T1.ask(h[j])+1;
				T1.modify(h[j],res),T2.modify(j,res);
			}
		}else
		{
			x=get();
			for(int j=1;j<x;j++)
			{
				tp[j]=Q.top(),Q.pop();
				T2.modify(p[tp[j]],0);
			}
			y=Q.top(),Q.pop();
			T1.modify(y,0),T2.modify(p[y],0);
			h[p[y]]=0,p[y]=0;
			for(x--;x;x--)
			{
				int res=T2.ask(p[tp[x]])+1;
				T1.modify(tp[x],res),T2.modify(p[tp[x]],res);
				Q.push(tp[x]);
			}
		}
	return 0;
}
