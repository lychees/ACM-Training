#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 100010
using namespace std;
struct Node
{
	Node *lc,*rc;
	int size,maxv;
}*Root[maxn],*Null;
int n,a[maxn],R[maxn],last[maxn];
int Log[maxn],maxv[20][maxn];
pair<int,int> operator + (const pair<int,int> &a,const pair<int,int> &b)
{
	return make_pair(a.first+b.first,max(a.second,b.second));
}
Node* Insert(Node *now,int l,int r,int x,int v)
{
	Node *p=new Node;
	*p=*now;
	++p->size,p->maxv=max(p->maxv,v);
	if(l==r)
		return p;
	int mid=(l+r)>>1;
	if(x<=mid)
		p->lc=Insert(p->lc,l,mid,x,v);
	else
		p->rc=Insert(p->rc,mid+1,r,x,v);
	return p;
}
pair<int,int> Query(Node *p,int l,int r,int x,int y)
{
	if(l==x&&r==y)
		return make_pair(p->size,p->maxv);
	int mid=(l+r)>>1;
	if(y<=mid)
		return Query(p->lc,l,mid,x,y);
	else if(mid<x)
		return Query(p->rc,mid+1,r,x,y);
	else
		return Query(p->lc,l,mid,x,mid)+Query(p->rc,mid+1,r,mid+1,y);
}
void read()
{
	static pair<int,int> sorted[maxn];
	static int now[maxn],next[maxn];
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",a+i);
	for(int i=n;i>=1;--i)
		next[i]=now[a[i]],now[a[i]]=i;
	for(int i=n;i>=1;--i)
	{
		int x=next[i],y=next[x];
		if(y==0)
			R[i]=n+1;
		else
			R[i]=y-x==x-i?R[x]:y;
		last[x]=i;
	}
	for(int i=1;i<=n;++i)
		sorted[i]=make_pair(last[i],i);
	sort(sorted+1,sorted+n+1);
	Null=new Node;
	Null->lc=Null,Null->rc=Null,Null->size=Null->maxv=0;
	Root[0]=Null;
	int j=1;
	while(sorted[j].first==0&&j<=n)
		Root[0]=Insert(Root[0],1,n,sorted[j].second,R[sorted[j].second]),++j;
	for(int i=1;i<=n+1;++i)
	{
		Root[i]=Root[i-1];
		while(sorted[j].first==i)
			Root[i]=Insert(Root[i],1,n,sorted[j].second,R[sorted[j].second]),++j;
	}
}
void Query()
{
	int m;
	scanf("%d",&m);
	for(int i=1,l,r;i<=m;++i)
	{
		scanf("%d %d",&l,&r);
		pair<int,int> ans=Query(Root[l-1],1,n,l,r);
		printf("%d\n",ans.first+(ans.second<=r));
	}
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	Query();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
