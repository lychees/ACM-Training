#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define INF 1000000000000000000LL
#define maxn 1005000
#define it tree[root]
#define lson tree[root<<1]
#define rson tree[root<<1|1]
using namespace std;
typedef long long LL;
struct Node
{
	int minv,tag;
}tree[maxn<<2];
LL vx,vy;
int L[maxn],R[maxn],d[maxn],w[maxn],n;
void Read(int &digit)
{
	digit=0;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
}
bool cmp(int i,int j)
{
	return d[i]<d[j];
}
void update_set(int root,int v)
{
	it.minv=max(it.minv,v);
	it.tag=max(it.tag,v);
}
void push_down(int root)
{
	if(it.tag)
	{
		update_set(root<<1,it.tag),update_set(root<<1|1,it.tag);
		it.tag=0;
	}
}
int Query(int root,int l,int r,int x,int y)
{
	if(l==x&&r==y)
		return it.minv;
	push_down(root);
	int mid=(l+r)>>1;
	if(y<=mid)
		return Query(root<<1,l,mid,x,y);
	else if(mid<x)
		return Query(root<<1|1,mid+1,r,x,y);
	else
		return min(Query(root<<1,l,mid,x,mid),Query(root<<1|1,mid+1,r,mid+1,y));
}
void Insert(int root,int l,int r,int x,int y,int v)
{
	if(l==x&&r==y)
	{
		update_set(root,v);
		return ;
	}
	push_down(root);
	int mid=(l+r)>>1;
	if(y<=mid)
		Insert(root<<1,l,mid,x,y,v);
	else if(mid<x)
		Insert(root<<1|1,mid+1,r,x,y,v);
	else
		Insert(root<<1,l,mid,x,mid,v),Insert(root<<1|1,mid+1,r,mid+1,y,v);
	it.minv=min(lson.minv,rson.minv);
}
void add(int a,int b,int v)
{
	LL l=INF,r=-INF,dis=INF;
	for(int i=a-1;i<=a;++i)
		for(int j=b-1;j<=b;++j)
		{
			LL val=vx*j-vy*i;
			l=min(l,val),r=max(r,val),dis=min(dis,vx*i+vy*j);
		}
	++n,L[n]=l,R[n]=r,d[n]=dis,w[n]=v;
}
void read()
{
	int n;
	cin>>n>>vx>>vy;
	for(int i=1,x;i<=n;++i)
		for(int j=1;j<=n;++j)
		{
			Read(x);
			if(x)
				add(i,j,x);
		}
}
LL work()
{
	static int x[maxn<<1],id[maxn];
	int tot=0;
	for(int i=1;i<=n;++i)
		x[++tot]=L[i],x[++tot]=R[i],id[i]=i;
	sort(x+1,x+tot+1);
	tot=unique(x+1,x+tot+1)-x-1;
	for(int i=1;i<=n;++i)
	{
		L[i]=lower_bound(x+1,x+tot+1,L[i])-x;
		R[i]=lower_bound(x+1,x+tot+1,R[i])-x;
	}
	sort(id+1,id+n+1,cmp);
	LL ans=0;
	for(int j=1;j<=n;++j)
	{
		int i=id[j],h=Query(1,1,tot,L[i]+1,R[i]);
		ans+=max(0,w[i]-h),Insert(1,1,tot,L[i]+1,R[i],w[i]);
	}
	return ans;
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
