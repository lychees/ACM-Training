#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 200010
#define lowbit(x) (x&-x)
using namespace std;
int Tree[maxn<<2],nTree;
int n,m,L[maxn],R[maxn];
void Modify(int i,int x)
{
	Tree[i+=nTree]=x;
	for(i>>=1;i;i>>=1)
		Tree[i]=max(Tree[i<<1],Tree[i<<1|1]);
}
int Query(int l,int r)
{
	int ans=-1<<30;
	for(l=l+nTree-1,r=r+nTree+1;l^r^1;l>>=1,r>>=1)
	{
		if(~l&1)
			ans=max(ans,Tree[l^1]);
		if(r&1)
			ans=max(ans,Tree[r^1]);
	}
	return ans;
}
void read()
{
	scanf("%d %d",&n,&m);
	++n;
	for(int i=1;i<=n;++i)
		R[i]=i-1;
	for(int i=1,x,y;i<=m;++i)
	{
		scanf("%d %d",&x,&y);
		L[y+1]=max(L[y+1],x),R[y]=min(R[y],x-1);
	}
	for(int i=2;i<=n;++i)
		L[i]=max(L[i-1],L[i]);
	for(int i=n-1;i>=1;--i)
		R[i]=min(R[i+1],R[i]);
	for(nTree=1;nTree-2<n;nTree<<=1);
}
int work()
{
	for(int i=1;i<n;++i)
		Modify(i,L[i]<=R[i]?Query(L[i],R[i])+1:-1<<30);
	return max(-1,Query(L[n],R[n]));
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	printf("%d\n",work());
	fclose(stdin);
	fclose(stdout);
	return 0;
}
