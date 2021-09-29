#pragma GCC optimize(3)
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#define f(x) ((x+ans)%n+1)
using namespace std;
typedef long long LL;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=1000003;
struct Ttree
{
	int ls,rs,sum;
}tree[maxn*21];
int a[maxn],n,ans=-1,root[maxn],tot=0;
void modify(int pre,int &x,int l,int r,int num)
{
	x=++tot,tree[x]=tree[pre],tree[x].sum++;
	if(l==r)return;
	int mid=(l+r)/2;
	if(num<=mid)modify(tree[pre].ls,tree[x].ls,l,mid,num);
	else modify(tree[pre].rs,tree[x].rs,mid+1,r,num);
}
int ask(int s,int t,int l,int r,int a,int b)
{
	if(a<=l&&r<=b)return tree[t].sum-tree[s].sum;
	int mid=(l+r)/2,res=0;
	if(a<=mid)res+=ask(tree[s].ls,tree[t].ls,l,mid,a,b);
	if(b>mid)res+=ask(tree[s].rs,tree[t].rs,mid+1,r,a,b);
	return res;
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get();
	for(int i=1;i<=n;i++)a[get()]=i;
	for(int i=1;i<=n;i++)modify(root[i-1],root[i],1,n,a[get()]);
	int T=get();
	while(T--)
	{
		int a=f(get()),b=f(get()),c=f(get()),d=f(get());
		if(a>b)a^=b^=a^=b;if(c>d)c^=d^=c^=d;
		printf("%d\n",ans=ask(root[c-1],root[d],1,n,a,b));
	}
	return 0;
}
