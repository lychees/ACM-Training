#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 100010
#define mod 1000000007
#define it tree[root]
#define lson tree[root<<1]
#define rson tree[root<<1|1]
using namespace std;
typedef long long LL;
int F[maxn][10],a[maxn],n,m,comb[10][10];
int getsum(int l,int r,int k)
{
	return (F[r][k]-F[l-1][k]+mod)%mod;
}
struct Node
{
	int sum[10],same,l,r;
}tree[maxn<<2];
void Build(int root,int l,int r)
{
	it.same=-1,it.l=l,it.r=r;
	if(l==r)
	{
		for(int i=0;i<=5;++i)
		{
			it.sum[i]=a[l];
			for(int j=1;j<=i;++j)
				it.sum[i]=(LL)it.sum[i]*(l+1)%mod;
		}
		return ;
	}
	int mid=(l+r)>>1;
	Build(root<<1,l,mid),Build(root<<1|1,mid+1,r);
	for(int i=0;i<=5;++i)
		it.sum[i]=(lson.sum[i]+rson.sum[i])%mod;
}
void update_set(int root,int v)
{
	it.same=v;
	for(int i=0;i<=5;++i)
		it.sum[i]=(LL)v*(F[it.r+1][i]-F[it.l][i]+mod)%mod;
}
void push_down(int root)
{
	if(it.same!=-1)
	{
		update_set(root<<1,it.same),update_set(root<<1|1,it.same);
		it.same=-1;
	}
}
void Modify(int root,int l,int r,int x,int y,int v)
{
	if(l==x&&r==y)
	{
		update_set(root,v);
		return ;
	}
	push_down(root);
	int mid=(l+r)>>1;
	if(y<=mid)
		Modify(root<<1,l,mid,x,y,v);
	else if(mid<x)
		Modify(root<<1|1,mid+1,r,x,y,v);
	else
		Modify(root<<1,l,mid,x,mid,v),Modify(root<<1|1,mid+1,r,mid+1,y,v);
	for(int i=0;i<=5;++i)
		it.sum[i]=(lson.sum[i]+rson.sum[i])%mod;
}
int Query(int root,int l,int r,int x,int y,int k,int p)
{
	if(l==x&&r==y)
	{
		int ans=0,v=1;
		for(int i=k;i>=0;--i)
			ans=(ans+(LL)it.sum[i]*comb[k][i]%mod*v)%mod,v=(LL)v*p%mod;
		return ans;
	}
	push_down(root);
	int mid=(l+r)>>1;
	if(y<=mid)
		return Query(root<<1,l,mid,x,y,k,p);
	else if(mid<x)
		return Query(root<<1|1,mid+1,r,x,y,k,p);
	else
		return (Query(root<<1,l,mid,x,mid,k,p)+Query(root<<1|1,mid+1,r,mid+1,y,k,p))%mod;
}
void read()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",a+i);
	Build(1,1,n);
	comb[0][0]=1;
	for(int i=1;i<=5;++i)
	{
		comb[i][0]=1;
		for(int j=1;j<=i;++j)
			comb[i][j]=comb[i-1][j]+comb[i-1][j-1];
	}
	for(int i=1;i<=n+1;++i)
		for(int j=0;j<=5;++j)
		{
			int s=1;
			for(int k=1;k<=j;++k)
				s=(LL)s*i%mod;
			F[i][j]=(F[i-1][j]+s)%mod;
		}
}
void Query()
{
	char c;
	for(int i=1,l,r,k;i<=m;++i)
	{
		for(c=getchar();c!='='&&c!='?';c=getchar());
		scanf("%d %d %d",&l,&r,&k);
		if(c=='?')
			printf("%d\n",Query(1,1,n,l,r,k,mod-l));
		else
			Modify(1,1,n,l,r,k);
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
