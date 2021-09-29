#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
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
const int maxn=1<<17,mod=1000000007;
struct Ttree
{
	LL val[6];
	int tag;
}tree[maxn*2];
LL sum[maxn][6],C[6][6],ans[6];
int n,m;
inline void add(LL &x,LL y)
{
	x+=y;
	if(x>=mod)x-=mod;
}
inline void pushup(int p)
{
	for(int i=0;i<=5;i++)
		tree[p].val[i]=tree[p*2].val[i],add(tree[p].val[i],tree[p*2+1].val[i]);
}
inline void mark(int p,int v,int l,int r)
{
	tree[p].tag=v;
	for(int i=0;i<=5;i++)tree[p].val[i]=(sum[r][i]-sum[l-1][i]+mod)*v%mod;
}
inline void pushdown(int p,int l,int mid,int r)
{
	if(tree[p].tag>=0)
	{
		mark(p*2,tree[p].tag,l,mid);
		mark(p*2+1,tree[p].tag,mid+1,r);
		tree[p].tag=-1;
	}
}
void build(int p,int l,int r)
{
	tree[p].tag=-1;
	if(l==r)
	{
		tree[p].val[0]=get();
		for(int i=1;i<=5;i++)tree[p].val[i]=tree[p].val[i-1]*l%mod;
		return;
	}
	int mid=(l+r)/2;
	build(p*2,l,mid),build(p*2+1,mid+1,r);
	pushup(p);
}
void modify(int p,int l,int r,int a,int b,int v)
{
	if(a<=l&&r<=b){mark(p,v,l,r);return;}
	int mid=(l+r)/2;
	pushdown(p,l,mid,r);
	if(a<=mid)modify(p*2,l,mid,a,b,v);
	if(b>mid)modify(p*2+1,mid+1,r,a,b,v);
	pushup(p);
}
void ask(int p,int l,int r,int a,int b,int k)
{
	if(a<=l&&r<=b)
	{
		for(int i=0;i<=k;i++)add(ans[i],tree[p].val[i]);
		return;
	}
	int mid=(l+r)/2;
	pushdown(p,l,mid,r);
	if(a<=mid)ask(p*2,l,mid,a,b,k);
	if(b>mid)ask(p*2+1,mid+1,r,a,b,k);
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get(),m=get();
	build(1,1,n);
	for(int i=0,j;i<=5;i++)
		for(C[i][0]=j=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	for(int i=1;i<=n;i++)
	{
		sum[i][0]=1;
		for(int j=1;j<=5;j++)sum[i][j]=sum[i][j-1]*i%mod;
		for(int j=0;j<=5;j++)add(sum[i][j],sum[i-1][j]);
	}
	while(m--)
	{
		char op=getchar();
		while(op!='='&&op!='?')op=getchar();
		int l=get(),r=get(),x=get();
		if(op=='?')
		{
			for(int i=0;i<=x;i++)ans[i]=0;
			ask(1,1,n,l,r,x);
			LL tp=1,res=0;
			for(int i=0;i<=x;i++,tp=tp*(1-l)%mod)res+=tp*ans[x-i]%mod*C[x][i]%mod;
			res=(res%mod+mod)%mod;
			printf("%d\n",int(res));
		}else modify(1,1,n,l,r,x);
	}
	return 0;
}
