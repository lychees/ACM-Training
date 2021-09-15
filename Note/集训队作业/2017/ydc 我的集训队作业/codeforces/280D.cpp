#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 100010
#define it tree[root]
#define lson tree[root<<1]
#define rson tree[root<<1|1]
using namespace std;
struct msgnode
{
	int minpre,minsuf,minsub,minrpre,minlsuf,minlsub,minrsub;
	int maxpre,maxsuf,maxsub,maxrpre,maxlsuf,maxlsub,maxrsub;
	int sum;
	friend msgnode operator + (const msgnode &a,const msgnode &b)
	{
		msgnode c;
		c.sum=a.sum+b.sum;
		if(a.sum+b.minpre<a.minpre)
			c.minpre=a.sum+b.minpre,c.minrpre=b.minrpre;
		else
			c.minpre=a.minpre,c.minrpre=a.minrpre;
		if(a.minsuf+b.sum<b.minsuf)
			c.minsuf=a.minsuf+b.sum,c.minlsuf=a.minlsuf;
		else
			c.minsuf=b.minsuf,c.minlsuf=b.minlsuf;
		c.minsub=a.minsub,c.minlsub=a.minlsub,c.minrsub=a.minrsub;
		if(c.minsub>b.minsub)
			c.minsub=b.minsub,c.minlsub=b.minlsub,c.minrsub=b.minrsub;
		if(c.minsub>a.minsuf+b.minpre)
			c.minsub=a.minsuf+b.minpre,c.minlsub=a.minlsuf,c.minrsub=b.minrpre;
		if(a.sum+b.maxpre>a.maxpre)
			c.maxpre=a.sum+b.maxpre,c.maxrpre=b.maxrpre;
		else
			c.maxpre=a.maxpre,c.maxrpre=a.maxrpre;
		if(a.maxsuf+b.sum>b.maxsuf)
			c.maxsuf=a.maxsuf+b.sum,c.maxlsuf=a.maxlsuf;
		else
			c.maxsuf=b.maxsuf,c.maxlsuf=b.maxlsuf;
		c.maxsub=a.maxsub,c.maxlsub=a.maxlsub,c.maxrsub=a.maxrsub;
		if(c.maxsub<b.maxsub)
			c.maxsub=b.maxsub,c.maxlsub=b.maxlsub,c.maxrsub=b.maxrsub;
		if(c.maxsub<a.maxsuf+b.maxpre)
			c.maxsub=a.maxsuf+b.maxpre,c.maxlsub=a.maxlsuf,c.maxrsub=b.maxrpre;
		return c;
	}
};
struct Seg_Tree
{
	bool tag;
	msgnode msg;
}tree[maxn<<2];
int n,a[maxn];
void update_Rev(int root)
{
	it.tag^=1;
	it.msg.sum*=-1;
	it.msg.minpre*=-1,it.msg.minsuf*=-1,it.msg.minsub*=-1;
	it.msg.maxpre*=-1,it.msg.maxsuf*=-1,it.msg.maxsub*=-1;
	swap(it.msg.minpre,it.msg.maxpre),swap(it.msg.minsuf,it.msg.maxsuf),swap(it.msg.minsub,it.msg.maxsub);
	swap(it.msg.minrpre,it.msg.maxrpre),swap(it.msg.minlsuf,it.msg.maxlsuf);
	swap(it.msg.minlsub,it.msg.maxlsub),swap(it.msg.minrsub,it.msg.maxrsub);
}
void push_down(int root)
{
	if(it.tag)
	{
		update_Rev(root<<1),update_Rev(root<<1|1);
		it.tag=0;
	}
}
void Build(int root,int l,int r)
{
	if(l==r)
	{
		it.msg.sum=a[l];
		it.msg.minpre=it.msg.minsuf=it.msg.minsub=a[l];
		it.msg.minrpre=it.msg.minlsuf=it.msg.minlsub=it.msg.minrsub=l;
		it.msg.maxpre=it.msg.maxsuf=it.msg.maxsub=a[l];
		it.msg.maxrpre=it.msg.maxlsuf=it.msg.maxlsub=it.msg.maxrsub=l;
		return ;
	}
	int mid=(l+r)>>1;
	Build(root<<1,l,mid),Build(root<<1|1,mid+1,r);
	it.msg=lson.msg+rson.msg;
}
void Modify(int root,int l,int r,int x,int v)
{
	if(l==r)
	{
		it.msg.sum=v;
		it.msg.minpre=it.msg.minsuf=it.msg.minsub=v;
		it.msg.minrpre=it.msg.minlsuf=it.msg.minlsub=it.msg.minrsub=l;
		it.msg.maxpre=it.msg.maxsuf=it.msg.maxsub=v;
		it.msg.maxrpre=it.msg.maxlsuf=it.msg.maxlsub=it.msg.maxrsub=l;
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
void Rev(int root,int l,int r,int x,int y)
{
	if(l==x&&r==y)
	{
		update_Rev(root);
		return ;
	}
	push_down(root);
	int mid=(l+r)>>1;
	if(y<=mid)
		Rev(root<<1,l,mid,x,y);
	else if(mid<x)
		Rev(root<<1|1,mid+1,r,x,y);
	else
		Rev(root<<1,l,mid,x,mid),Rev(root<<1|1,mid+1,r,mid+1,y);
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
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",a+i);
	Build(1,1,n);
}
void Query()
{
	static int L[30],R[30];
	int m;
	scanf("%d",&m);
	for(int i=1,t,l,r,v;i<=m;++i)
	{
		scanf("%d",&t);
		if(t==0)
		{
			scanf("%d %d",&l,&v);
			Modify(1,1,n,l,v);
		}
		else
		{
			scanf("%d %d %d",&l,&r,&v);
			int ans=0,tot=0;
			for(int j=1;j<=v;++j)
			{
				msgnode p=Query(1,1,n,l,r);
				if(p.maxsub<=0)
					break;
				ans+=p.maxsub,Rev(1,1,n,p.maxlsub,p.maxrsub),++tot,L[tot]=p.maxlsub,R[tot]=p.maxrsub;
			}
			printf("%d\n",ans);
			for(int j=1;j<=tot;++j)
				Rev(1,1,n,L[j],R[j]);
		}
	}
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	Query();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
