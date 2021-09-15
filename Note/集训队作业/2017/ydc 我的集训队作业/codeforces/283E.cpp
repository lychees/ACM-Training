#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#define it tree[root]
#define lson tree[root<<1]
#define rson tree[root<<1|1]
#define each(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
#define maxn 100010
using namespace std;
typedef long long LL;
struct Seg_Tree
{
	int sum[2];
	bool rev;
}tree[maxn<<2];
vector<int> toL[maxn],toR[maxn];
int n,m;
void read()
{
	static int a[maxn];
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",a+i);
	sort(a+1,a+n+1);
	for(int i=1,l,r;i<=m;++i)
	{
		scanf("%d %d",&l,&r);
		l=lower_bound(a+1,a+n+1,l)-a,r=upper_bound(a+1,a+n+1,r)-a-1;
		if(l<r)
		{
			toL[l].push_back(r);
			toR[r].push_back(l);
		}
	}
}
void rev(int root)
{
	swap(it.sum[0],it.sum[1]);
	it.rev^=1;
}
void push_down(int root)
{
	if(it.rev)
	{
		rev(root<<1),rev(root<<1|1);
		it.rev=false;
	}
}
void Rev(int root,int l,int r,int x,int y)
{
	if(l==x&&r==y)
	{
		rev(root);
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
	it.sum[0]=lson.sum[0]+rson.sum[0];
	it.sum[1]=lson.sum[1]+rson.sum[1];
}
int Query(int root,int l,int r,int x,int y,int c)
{
	if(l==x&&r==y)
		return it.sum[c];
	push_down(root);
	int mid=(l+r)>>1;
	if(y<=mid)
		return Query(root<<1,l,mid,x,y,c);
	else if(mid<x)
		return Query(root<<1|1,mid+1,r,x,y,c);
	else
		return Query(root<<1,l,mid,x,mid,c)+Query(root<<1|1,mid+1,r,mid+1,y,c);
}
void Build(int root,int l,int r)
{
	it.sum[0]=r-l+1;
	if(l==r)
		return ;
	int mid=(l+r)>>1;
	Build(root<<1,l,mid),Build(root<<1|1,mid+1,r);
}
LL work()
{
	LL sum=(LL)n*(n-1)*(n-2)/3;
	Build(1,1,n);
	for(int i=1;i<=n;++i)
	{
		each(x,toL[i])
			Rev(1,1,n,i,*x);
		LL d=0;
		if(i>1)
			d+=Query(1,1,n,1,i-1,0);
		if(i<n)
			d+=Query(1,1,n,i+1,n,1);
		sum-=d*(d-1);
		each(x,toR[i])
			Rev(1,1,n,*x,i);
	}
	return sum/2;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	cout<<work()<<endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
