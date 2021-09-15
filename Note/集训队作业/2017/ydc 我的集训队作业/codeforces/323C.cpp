#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 1000010
using namespace std;
struct Node
{
	Node *son[2];
	int s;
}*Root[maxn],*Null;
Node* Insert(Node *root,int l,int r,int x)
{
	Node *p=new Node;
	p->son[0]=root->son[0],p->son[1]=root->son[1],p->s=root->s+1;
	if(l==r)
		return p;
	int mid=(l+r)>>1;
	if(x<=mid)
		p->son[0]=Insert(p->son[0],l,mid,x);
	else
		p->son[1]=Insert(p->son[1],mid+1,r,x);
	return p;
}
int getsum(Node *p,int l,int r,int x,int y)
{
	if((!p->s)||(l==x&&r==y))
		return p->s;
	int mid=(l+r)>>1;
	if(y<=mid)
		return getsum(p->son[0],l,mid,x,y);
	else if(mid<x)
		return getsum(p->son[1],mid+1,r,x,y);
	else
		return getsum(p->son[0],l,mid,x,mid)+getsum(p->son[1],mid+1,r,mid+1,y);
}
int n,m;
void read()
{
	static int pos[maxn],a[maxn];
	Null=new Node;
	Null->son[0]=Null->son[1]=Null,Null->s=0;
	scanf("%d",&n);
	for(int i=1,x;i<=n;++i)
	{
		scanf("%d",&x);
		pos[x]=i;
	}
	for(int i=1,x;i<=n;++i)
	{
		scanf("%d",&x);
		a[pos[x]]=i;
	}
	Root[0]=Null;
	for(int i=1;i<=n;++i)
		Root[i]=Insert(Root[i-1],1,n,a[i]);
}
int f(int p,int x)
{
	return (p-1+x)%n+1;
}
void Query()
{
	int lastans=0;
	scanf("%d",&m);
	for(int i=1,a,b,c,d,l1,r1,l2,r2;i<=m;++i)
	{
		scanf("%d %d %d %d",&a,&b,&c,&d);
		l1=min(f(a,lastans),f(b,lastans)),r1=max(f(a,lastans),f(b,lastans)),l2=min(f(c,lastans),f(d,lastans)),r2=max(f(c,lastans),f(d,lastans));
		lastans=getsum(Root[r1],1,n,l2,r2)-getsum(Root[l1-1],1,n,l2,r2);
		printf("%d\n",lastans++);
	}
}
int main()
{
	read();
	Query();
	return 0;
}
