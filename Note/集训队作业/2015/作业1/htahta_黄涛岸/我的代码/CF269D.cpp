#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <set>
#define x first
#define y second
#define mp make_pair
using namespace std;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=100005,inf=1000000000;
typedef pair<int,int> pii;
struct data
{
	int h,l,r;
	data(){}
	data(int _h,int _l,int _r){h=_h,l=_l,r=_r;}
	inline bool operator <(const data &b)const{return h<b.h;}
}a[maxn];
int n,H,f[maxn],g[maxn];
set<pii> S;
inline int calc(int x,int y){return max(min(a[x].r,a[y].r)-max(a[x].l,a[y].l),0);}
inline bool Link(int x,int y){return a[x].h>a[y].h&&calc(x,y);}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get();H=get();
	for(int i=1;i<=n;i++)a[i].h=get(),a[i].l=get(),a[i].r=get();
	a[++n]=data(0,-inf,inf),a[++n]=data(H,-inf,inf);
	sort(a+1,a+1+n);
	f[1]=2*inf;S.insert(mp(-inf,1));S.insert(mp(inf,1));
	set<pii>::iterator it,tp;
	for(int i=2,m;i<=n;i++)
	{
		tp=it=--S.lower_bound(mp(a[i].l,inf));
		for(m=0;it->x<a[i].r;++it)g[++m]=it->y;
		if(tp->x!=a[i].l)++tp;
		S.erase(tp,it);
		S.insert(mp(a[i].l,i));
		if(it->x!=a[i].r)S.insert(mp(a[i].r,g[m]));
		for(int j=1;j<=m;j++)
			if((j==1||!(Link(i,g[j-1])&&Link(g[j-1],g[j])))&&(j==n||!(Link(i,g[j+1])&&Link(g[j+1],g[j]))))
				f[i]=max(f[i],min(f[g[j]],calc(g[j],i)));
	}
	cout<<f[n]<<endl;
	return 0;
}
