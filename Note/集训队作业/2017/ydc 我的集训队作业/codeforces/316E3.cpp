#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define it tree[root]
#define lson tree[root<<1]
#define rson tree[root<<1|1]
#define maxn 200010
#define mod 1000000000
using namespace std;
typedef long long LL;
struct Matrix
{
	int a[2][2];
	friend Matrix operator * (const Matrix &a,const Matrix &b)
	{
		Matrix c;
		c.a[0][0]=((LL)a.a[0][0]*b.a[0][0]+(LL)a.a[0][1]*b.a[1][0])%mod;
		c.a[0][1]=((LL)a.a[0][0]*b.a[0][1]+(LL)a.a[0][1]*b.a[1][1])%mod;
		c.a[1][0]=((LL)a.a[1][0]*b.a[0][0]+(LL)a.a[1][1]*b.a[1][0])%mod;
		c.a[1][1]=((LL)a.a[1][0]*b.a[0][1]+(LL)a.a[1][1]*b.a[1][1])%mod;
		return c;
	}
	friend Matrix operator * (const Matrix &a,int p)
	{
		Matrix c;
		c.a[0][0]=(LL)a.a[0][0]*p%mod;
		c.a[0][1]=(LL)a.a[0][1]*p%mod;
		c.a[1][0]=(LL)a.a[1][0]*p%mod;
		c.a[1][1]=(LL)a.a[1][1]*p%mod;
		return c;
	}
	friend Matrix operator + (const Matrix &a,const Matrix &b)
	{
		Matrix c;
		c.a[0][0]=a.a[0][0]+b.a[0][0];
		c.a[0][1]=a.a[0][1]+b.a[0][1];
		c.a[1][0]=a.a[1][0]+b.a[1][0];
		c.a[1][1]=a.a[1][1]+b.a[1][1];
		if(c.a[0][0]>=mod)
			c.a[0][0]-=mod;
		if(c.a[0][1]>=mod)
			c.a[0][1]-=mod;
		if(c.a[1][0]>=mod)
			c.a[1][0]-=mod;
		if(c.a[1][1]>=mod)
			c.a[1][1]-=mod;
		return c;
	}
}F[maxn],sum[maxn];
struct msgnode
{
	Matrix sum;
	int size;
	friend msgnode operator + (const msgnode &a,const msgnode &b)
	{
		msgnode c;
		c.sum=a.sum+b.sum*F[a.size];
		c.size=a.size+b.size;
		return c;
	}
};
struct SegTree
{
	msgnode msg;
	int add;
}tree[maxn<<2];
int n,m,a[maxn];
void Build(int root,int l,int r)
{
	if(l==r)
	{
		it.msg.size=1;
		it.msg.sum=F[1]*a[l];
		return ;
	}
	int mid=(l+r)>>1;
	Build(root<<1,l,mid),Build(root<<1|1,mid+1,r);
	it.msg=lson.msg+rson.msg;
}
void add(int root,int v)
{
	it.msg.sum=it.msg.sum+sum[it.msg.size]*v;
	it.add+=v;
	if(it.add>=mod)
		it.add-=mod;
}
void push_down(int root)
{
	if(it.add)
	{
		add(root<<1,it.add),add(root<<1|1,it.add);
		it.add=0;
	}
}
void Modify(int root,int l,int r,int x,int v)
{
	if(l==r)
	{
		it.msg.sum=F[1]*v;
		return ;
	}
	push_down(root);
	int mid=(l+r)>>1;
	if(x<=mid)
		Modify(root<<1,l,mid,x,v);
	else
		Modify(root<<1|1,mid+1,r,x,v);
	it.msg=lson.msg+rson.msg;
}
void add(int root,int l,int r,int x,int y,int d)
{
	if(l==x&&r==y)
	{
		add(root,d);
		return ;
	}
	push_down(root);
	int mid=(l+r)>>1;
	if(y<=mid)
		add(root<<1,l,mid,x,y,d);
	else if(mid<x)
		add(root<<1|1,mid+1,r,x,y,d);
	else
		add(root<<1,l,mid,x,mid,d),add(root<<1|1,mid+1,r,mid+1,y,d);
	it.msg=lson.msg+rson.msg;
}
msgnode Query(int root,int l,int r,int x,int y)
{
	if(l==x&&r==y)
		return it.msg;
	push_down(root);
	int mid=(l+r)>>1;
	if(y<=mid)
		return Query(root<<1,l,mid,x,y);
	else if(mid<x)
		return Query(root<<1|1,mid+1,r,x,y);
	else
		return Query(root<<1,l,mid,x,mid)+Query(root<<1|1,mid+1,r,mid+1,y);
}
void read()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",a+i);
	F[0].a[0][0]=F[0].a[1][1]=1;
	F[1].a[0][1]=F[1].a[1][0]=F[1].a[1][1]=1,sum[1]=F[1];
	for(int i=2;i<=n;++i)
		F[i]=F[i-1]*F[1],sum[i]=F[i]+sum[i-1];
	Build(1,1,n);
}
void Query()
{
	for(int i=1,t,l,r,d;i<=m;++i)
	{
		scanf("%d",&t);
		if(t==1)
		{
			scanf("%d %d",&l,&d);
			Modify(1,1,n,l,d);
		}
		else if(t==2)
		{
			scanf("%d %d",&l,&r);
			printf("%d\n",Query(1,1,n,l,r).sum.a[0][1]);
		}
		else
		{
			scanf("%d %d %d",&l,&r,&d);
			add(1,1,n,l,r,d);
		}
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
