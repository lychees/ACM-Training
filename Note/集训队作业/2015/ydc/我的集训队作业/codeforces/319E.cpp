#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#define each(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
#define maxn 100010
using namespace std;
struct Event
{
	int t,a,b;
}e[maxn];
vector<int>tree[maxn<<2];
int n,m,L[maxn],R[maxn],cnt,father[maxn];
int Find(int p)
{
	if(father[p]!=p)
		father[p]=Find(father[p]);
	return father[p];
}
void update(int root,int l,int r,int x)
{
	each(e,tree[root])
	{
		int x=Find(*e);
		L[cnt]=min(L[cnt],L[x]);
		R[cnt]=max(R[cnt],R[x]);
		father[x]=cnt;
	}
	tree[root].clear();
	if(l==r)
		return ;
	int mid=(l+r)>>1;
	if(x<=mid)
		update(root<<1,l,mid,x);
	else
		update(root<<1|1,mid+1,r,x);
}
void Insert(int root,int l,int r,int x,int y)
{
	if(l==x&&r==y)
	{
		tree[root].push_back(cnt);
		return ;
	}
	int mid=(l+r)>>1;
	if(y<=mid)
		Insert(root<<1,l,mid,x,y);
	else if(mid<x)
		Insert(root<<1|1,mid+1,r,x,y);
	else
		Insert(root<<1,l,mid,x,mid),Insert(root<<1|1,mid+1,r,mid+1,y);
}
void read()
{
	static int sorted[maxn<<1];
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d %d %d",&e[i].t,&e[i].a,&e[i].b);
		if(e[i].t==1)
			sorted[++m]=e[i].a,sorted[++m]=e[i].b;
	}
	sort(sorted+1,sorted+m+1);
	m=unique(sorted+1,sorted+m+1)-sorted-1;
	for(int i=1;i<=n;++i)
		if(e[i].t==1)
		{
			e[i].a=lower_bound(sorted+1,sorted+m+1,e[i].a)-sorted;
			e[i].b=lower_bound(sorted+1,sorted+m+1,e[i].b)-sorted;
		}
}
void Query()
{
	static int l[maxn],r[maxn];
	for(int i=1;i<=n;++i)
	{
		if(e[i].t==1)
		{
			father[++cnt]=cnt;
			l[cnt]=e[i].a,r[cnt]=e[i].b;
			L[cnt]=e[i].a,R[cnt]=e[i].b;
			update(1,1,m,e[i].a);
			update(1,1,m,e[i].b);
			if(L[cnt]+1<=R[cnt]-1)
				Insert(1,1,m,L[cnt]+1,R[cnt]-1);
		}
		else
		{
			int a=e[i].a,b=Find(e[i].b);
			printf("%s\n",Find(a)==b||(l[a]>L[b]&&l[a]<R[b])||(r[a]>L[b]&&r[a]<R[b])?"YES":"NO");
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
