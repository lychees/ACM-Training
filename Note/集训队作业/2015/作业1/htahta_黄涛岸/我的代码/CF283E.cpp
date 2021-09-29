#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <ctime>
#include <vector>
#define pb push_back
#define mp make_pair
#define x first
#define y second
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
inline int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f==1)return -v;else return v;
}
const int maxn=100005;
int a[maxn],n,m;
vector<pii> g[maxn];
struct Ttree
{
	int sum,tag;
}tree[maxn*4];
inline void pushup(int p)
{
	tree[p].sum=tree[p*2].sum+tree[p*2+1].sum;
}
inline void mark(int p,int l)
{
	tree[p].tag^=1;tree[p].sum=l-tree[p].sum;
}
inline void pushdown(int p,int l1,int l2)
{
	if(!tree[p].tag)return;
	mark(p*2,l1),mark(p*2+1,l2);
	tree[p].tag=0;
}
inline void modify(int p,int l,int r,int a,int b)
{
	if(a<=l&&r<=b){mark(p,r-l+1);return;}
	int mid=(l+r)/2;
	pushdown(p,mid-l+1,r-mid);
	if(a<=mid)modify(p*2,l,mid,a,b);
	if(b>mid)modify(p*2+1,mid+1,r,a,b);
	pushup(p);
}
inline int ask(int p,int l,int r,int a,int b)
{
	if(a<=l&&r<=b)return tree[p].sum;
	int mid=(l+r)/2,res=0;
	pushdown(p,mid-l+1,r-mid);
	if(a<=mid)res+=ask(p*2,l,mid,a,b);
	if(b>mid)res+=ask(p*2+1,mid+1,r,a,b);
	pushup(p);
	return res;
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get(),m=get();
	for(int i=1;i<=n;i++)a[i]=get();
	sort(a+1,a+1+n);
	while(m--)
	{
		int x=lower_bound(a+1,a+1+n,get())-a;
		int y=upper_bound(a+1,a+1+n,get())-a;
		if(x<y)g[x].pb(mp(x,y-1)),g[y].pb(mp(x,y-1));
	}
	LL ans=LL(n)*(n-1)*(n-2)/6;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<int(g[i].size());j++)modify(1,1,n,g[i][j].x,g[i][j].y);
		LL sum=i-1-(i>1?ask(1,1,n,1,i-1):0)+(i<n?ask(1,1,n,i+1,n):0);
		ans-=sum*(sum-1)/2;
	}
	printf("%I64d\n",ans);
	return 0;
}

