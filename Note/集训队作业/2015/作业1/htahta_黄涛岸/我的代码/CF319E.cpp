#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
using namespace std;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=100003,inf=1000000000;
struct Ttree
{
	int ls,rs;
	vector<int> a;
}tree[maxn*35];
int n=0,fa[maxn],L[maxn],R[maxn],T,l[maxn],r[maxn],root=0,tot=0;
int getfa(int x){return x==fa[x]?x:fa[x]=getfa(fa[x]);}
void find(int x,int l,int r,int v)
{
	if(!x)return;
	for(int i=0,y;i<int(tree[x].a.size());i++)
	{
		y=getfa(tree[x].a[i]);fa[y]=n;
		L[n]=min(L[n],L[y]),R[n]=max(R[n],R[y]);
	}
	tree[x].a.clear();
	if(l==r)return;
	int mid=(l+r)>>1;
	if(v<=mid)find(tree[x].ls,l,mid,v);else find(tree[x].rs,mid+1,r,v);
}
void modify(int &x,int l,int r,int a,int b)
{
	if(!x)x=++tot;
	if(a<=l&&r<=b){tree[x].a.push_back(n);return;}
	int mid=(l+r)>>1;
	if(a<=mid)modify(tree[x].ls,l,mid,a,b);
	if(b>mid)modify(tree[x].rs,mid+1,r,a,b);
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	T=get();
	while(T--)
	{
		int op=get(),x=get(),y=get();
		if(op==1)
		{
			++n,fa[n]=n,L[n]=l[n]=x,R[n]=r[n]=y;
			find(root,-inf,inf,x),find(root,-inf,inf,y);
			if(L[n]<R[n]-1)modify(root,-inf,inf,L[n]+1,R[n]-1);
			
		}else
		{
			x=getfa(x),y=getfa(y);
			puts(x==y||(L[y]<l[x]&&l[x]<R[y])||(L[y]<r[x]&&r[x]<R[y])?"YES":"NO");
		}
	}
	return 0;
}
