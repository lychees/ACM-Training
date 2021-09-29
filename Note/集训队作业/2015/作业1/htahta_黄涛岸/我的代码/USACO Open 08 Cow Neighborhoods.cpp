#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <set>
#define mp make_pair
#define x first
#define y second
using namespace std;
typedef pair<int,int> pii;
typedef long long LL;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=100333,inf=2100000000;
int n,C,b[maxn],ans,mv=0,fa[maxn];
pii a[maxn];
set<pii>::iterator it,l,r;
set<pii> S;
inline int getfa(int x){return x==fa[x]?x:fa[x]=getfa(fa[x]);}
inline void Link(int x,int y)
{
	int fx=getfa(x),fy=getfa(y);
	if(fx!=fy)fa[fx]=fy,--ans;
}
int main()
{
	ans=n=get(),C=get();
	for(int i=1,x,y;i<=n;i++)x=get(),y=get(),a[i]=mp(x+y,x-y),fa[i]=i;
	sort(a+1,a+1+n);
	S.insert(mp(-inf,0)),S.insert(mp(inf,0));
	for(int i=1,j=1;i<=n;i++)
	{
		for(;a[i].x-a[j].x>C;j++)S.erase(mp(a[j].y,j));
		it=S.insert(mp(a[i].y,i)).x;
		l=r=it;--l,++r;
		if(LL(a[i].y)-LL(l->x)<=C)Link(i,l->y);
		if(LL(r->x)-LL(a[i].y)<=C)Link(i,r->y);
	}
	for(int i=1,f;i<=n;i++)
		b[f=getfa(i)]++,mv=max(mv,b[f]);
	printf("%d %d\n",ans,mv);
	return 0;
}
