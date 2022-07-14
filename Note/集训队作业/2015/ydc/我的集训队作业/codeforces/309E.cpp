#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<ctime>
#define maxn 2010
using namespace std;
struct Node
{
	int l,r,id;
	friend bool operator < (const Node &a,const Node &b)
	{
		return a.r<b.r;
	}
}seg[maxn];
int n;
int F[maxn],map[maxn][maxn];
bool isCross(const Node &a,const Node &b)
{
	if(a.l>=b.l&&a.l<=b.r)
		return true;
	if(a.r>=b.l&&a.r<=b.r)
		return true;
	if(b.l>=a.l&&b.l<=a.r)
		return true;
	if(b.r>=a.l&&b.r<=a.r)
		return true;
	return false;
}
void read()
{
	for(int i=1;i<=n;i++)
	{
		scanf("%d %d",&seg[i].l,&seg[i].r);
		seg[i].id=i;
	}
	sort(seg+1,seg+n+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(i!=j)
				map[i][j]=isCross(seg[i],seg[j]);
}
bool check(int len)
{
	static int Sum[maxn],limit[maxn];
	static bool can[maxn];
	for(int i=1;i<=n;i++)
		F[i]=0,limit[i]=n,can[i]=true;
	for(int i=1;i<=n;i++)
	{
		int ans;
		for(ans=1;!can[ans];ans++);
		limit[ans]=i,F[ans]=i;
		for(int j=1;j<=n;j++)
			Sum[j]=0;
		for(int j=1;j<=n;j++)
		{
			if(map[ans][j])
				limit[j]=min(limit[j],i+len);
			Sum[limit[j]]++;
		}
		for(int j=1;j<=n;j++)
		{
			Sum[j]+=Sum[j-1];
			if(Sum[j]>j)
				return false;
		}
		for(ans=i+1;ans<=n&&Sum[ans]!=ans;ans++);
		for(int j=1;j<=n;j++)
			can[j]=(limit[j]<=ans&&F[j]==0);
	}
	return true;
}
int Find(int l,int r)
{
	while(l<r)
	{
		int mid=(l+r)>>1;
		check(mid)?r=mid:l=mid+1;
	}
	check(l);
	return l;
}
void print()
{
	static int ans[maxn];
	for(int i=1;i<=n;i++)
		ans[F[i]]=seg[i].id;
	for(int i=1;i<=n;i++)
		printf("%d%c",ans[i],i<n?' ':'\n');
}
void work()
{
	read();
	Find(0,n);
	print();
}
int main()
{
	scanf("%d",&n);
	work();
	return 0;
}
