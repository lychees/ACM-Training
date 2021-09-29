#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <ctime>
using namespace std;
typedef long long LL;
inline int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f==1)return -v;else return v;
}
const int inf=1000000000,maxn=1000*1003;
struct data
{
	int d,l,r,v;
	data(){}
	data(int _d,int _l,int _r,int _v){d=_d,l=_l,r=_r,v=_v;}
	inline bool operator <(const data &b)const{return d<b.d;}
}a[maxn];
inline void gmin(int &x,int y){if(x>y)x=y;}
inline void gmax(int &x,int y){if(x<y)x=y;}
struct Ttree
{
	int tag,val;
}tree[1<<22];
int n,vx,vy,N=0,num[maxn*2],Tnum=0;
LL ans=0;
inline void mark(int p,int v)
{
	gmax(tree[p].tag,v),gmax(tree[p].val,v);
}
inline void pushdown(int p)
{
	if(!tree[p].tag)return;
	mark(p*2,tree[p].tag),mark(p*2+1,tree[p].tag);
	tree[p].tag=0;
}
inline void pushup(int p)
{
	tree[p].val=min(tree[p*2].val,tree[p*2+1].val);
}
inline int ask(int p,int l,int r,int a,int b)
{
	if(a<=l&&r<=b)return tree[p].val;
	pushdown(p);
	int mid=(l+r)/2,res=inf;
	if(a<=mid)gmin(res,ask(p*2,l,mid,a,b));
	if(b>mid)gmin(res,ask(p*2+1,mid+1,r,a,b));
	pushup(p);
	return res;
}
inline void modify(int p,int l,int r,int a,int b,int v)
{
	if(a<=l&&r<=b){mark(p,v);return;}
	pushdown(p);
	int mid=(l+r)/2;
	if(a<=mid)modify(p*2,l,mid,a,b,v);
	if(b>mid)modify(p*2+1,mid+1,r,a,b,v);
	pushup(p);
}
int main()
{
	freopen("20.in","r",stdin);
	//freopen("20.out","w",stdout);
	n=get(),vx=get(),vy=get();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
		{
			int d=inf,l=inf,r=-inf,s,x,y;
			for(int dx=-1;dx<1;++dx)
				for(int dy=-1;dy<1;++dy)
				{
					x=i+dx,y=j+dy;
					s=-x*vy+y*vx;
					gmin(l,s),gmax(r,s);
					gmin(d,x*vx+y*vy);
				}
			a[++N]=data(d,l,r,get());
			num[++Tnum]=l;num[++Tnum]=r;
		}
	sort(a+1,a+1+N);
	sort(num+1,num+1+Tnum),Tnum=unique(num+1,num+1+Tnum)-num-1;
	for(int i=1;i<=N;i++)
	{
		int l=lower_bound(num+1,num+1+Tnum,a[i].l)-num;
		int r=lower_bound(num+1,num+1+Tnum,a[i].r)-num-1;
		//cout<<l<<" "<<r<<" "<<a[i].v<<" "<<a[i].d<<endl;
		int v=ask(1,1,Tnum,l,r);
		if(a[i].v<=v)continue;
		ans+=a[i].v-v;
		modify(1,1,Tnum,l,r,a[i].v);
	}
	printf("%I64d\n",ans);
	cerr<<Tnum<<endl;
	return 0;
}
