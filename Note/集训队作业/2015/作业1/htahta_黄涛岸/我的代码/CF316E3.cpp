#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
typedef long long LL;
const int maxn=200033,mod=1000000000;
int n,m,T;
LL F[maxn],S[maxn];
struct data
{
	int x,y,L,tag;
	data(){}
	data(int _x,int _y,int _L,int _t){x=_x,y=_y,L=_L,tag=_t;}
}tree[524388];
inline data merge(const data &a,const data &b)
{
	return data((F[a.L+1]*b.x+F[a.L]*b.y+a.x)%mod,(F[a.L]*b.x+F[a.L-1]*b.y+a.y)%mod,a.L+b.L,0);
}
inline void pushup(int p)
{
	tree[p]=merge(tree[p*2],tree[p*2+1]);
}
void build(int p,int l,int r)
{
	if(l==r){tree[p]=data(get(),0,1,0);return;}
	int mid=(l+r)/2;
	build(p*2,l,mid),build(p*2+1,mid+1,r);
	pushup(p);
}
inline void mark(int p,int v)
{
	(tree[p].tag+=v)%=mod;
	tree[p].x=(S[tree[p].L]*v+tree[p].x)%mod;
	tree[p].y=(S[tree[p].L-1]*v+tree[p].y)%mod;
}
inline void pushdown(int p)
{
	if(tree[p].tag)mark(p*2,tree[p].tag),mark(p*2+1,tree[p].tag);
	tree[p].tag=0;
}
void modify(int p,int l,int r,int x,int v)
{
	if(l==r){tree[p]=data(v,0,1,0);return;}
	pushdown(p);
	int mid=(l+r)/2;
	if(x<=mid)modify(p*2,l,mid,x,v);
	else modify(p*2+1,mid+1,r,x,v);
	pushup(p);
}
data ask(int p,int l,int r,int a,int b)
{
	if(a<=l&&r<=b)return tree[p];
	pushdown(p);
	int mid=(l+r)/2;
	if(b<=mid)return ask(p*2,l,mid,a,b);
	else if(a>mid)return ask(p*2+1,mid+1,r,a,b);
	return merge(ask(p*2,l,mid,a,b),ask(p*2+1,mid+1,r,a,b));
}
void add(int p,int l,int r,int a,int b,int v)
{
	if(a<=l&&r<=b){mark(p,v);return;}
	pushdown(p);
	int mid=(l+r)/2;
	if(a<=mid)add(p*2,l,mid,a,b,v);
	if(b>mid)add(p*2+1,mid+1,r,a,b,v);
	pushup(p);
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get();T=get();
	F[1]=S[1]=1;
	for(int i=2;i<=n;i++)F[i]=(F[i-1]+F[i-2])%mod,S[i]=(S[i-1]+F[i])%mod;
	build(1,1,n);
	while(T--)
	{
		int op=get(),x=get(),y=get();
		if(op==1)modify(1,1,n,x,y);
		if(op==2)printf("%d\n",ask(1,1,n,x,y).x);
		if(op==3)add(1,1,n,x,y,get());
	}
	return 0;
}
