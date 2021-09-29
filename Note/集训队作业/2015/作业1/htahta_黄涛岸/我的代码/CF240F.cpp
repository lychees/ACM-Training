#include <iostream>
#include <cstdio>
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
struct Ttree
{
	int tag,a[26];
}tree[262244];
int n,m,cnt[26];
inline void pushup(int p)
{
	for(int i=0;i<26;i++)tree[p].a[i]=tree[p*2].a[i]+tree[p*2+1].a[i];
}
inline void mark(int p,int c,int L)
{
	memset(tree[p].a,0,4*26);
	tree[p].tag=c;tree[p].a[c]=L;
}
inline void pushdown(int p,int L)
{
	if(tree[p].tag==-1)return;
	mark(p*2,tree[p].tag,(L+1)/2);
	mark(p*2+1,tree[p].tag,L/2);
	tree[p].tag=-1;
}
void build(int p,int l,int r)
{
	tree[p].tag=-1;
	if(l==r){tree[p].a[getchar()-'a']=1;return;}
	int mid=(l+r)/2;
	build(p*2,l,mid),build(p*2+1,mid+1,r);
	pushup(p);
}
void dfs(int p,int l,int r)
{
	if(l==r)
		for(int i=0;i<26;i++)
			if(tree[p].a[i]){putchar('a'+i);return;}
	pushdown(p,r-l+1);
	int mid=(l+r)/2;
	dfs(p*2,l,mid);dfs(p*2+1,mid+1,r);
}
void ask(int p,int l,int r,int a,int b)
{
	if(a<=l&&r<=b)
	{
		for(int i=0;i<26;i++)cnt[i]+=tree[p].a[i];
		return;
	}
	int mid=(l+r)/2;
	pushdown(p,r-l+1);
	if(a<=mid)ask(p*2,l,mid,a,b);
	if(b>mid)ask(p*2+1,mid+1,r,a,b);
}
void modify(int p,int l,int r,int a,int b,int v)
{
	if(a<=l&&r<=b){mark(p,v,r-l+1);return;}
	pushdown(p,r-l+1);
	int mid=(l+r)/2;
	if(a<=mid)modify(p*2,l,mid,a,b,v);
	if(b>mid)modify(p*2+1,mid+1,r,a,b,v);
	pushup(p);
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get(),m=get();
	build(1,1,n);
	while(m--)
	{
		int l=get(),r=get();
		memset(cnt,0,sizeof(cnt));
		ask(1,1,n,l,r);
		int c=0,d;
		for(int i=0;i<26;i++)
			if(cnt[i]&1)c++,d=i;
		if(c>1)continue;
		for(int i=0,j;i<26;i++)
		{
			if(cnt[i]<=1)continue;
			j=cnt[i]/2;
			modify(1,1,n,l,l+j-1,i);
			modify(1,1,n,r-j+1,r,i);
			l+=j,r-=j;
		}
		if(c)modify(1,1,n,l,l,d);
	}
	dfs(1,1,n);
	return 0;
}
