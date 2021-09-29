#include<algorithm>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include  <stdio.h>
#include   <math.h>
#include   <vector>
#include    <deque>
#include    <queue>
#include      <set>
#include      <map>
using namespace std;

#define Pr pair<int,int>
#define x first
#define y second
const int N=400005;
typedef long long LL;

inline LL gcd(LL a,LL b)
{
	return b?gcd(b,a%b):a;
}

LL Ans,Orz;

inline void get(int& x)
{
	char ch;
	int f;
 	for(ch=getchar();(ch<'0'||ch>'9')&&ch!='-';ch=getchar());
 	if(ch=='-') f=-1,x=0;
 	else  f=1,x=ch^48;
 	for(ch=getchar();ch>='0'&&ch<='9';ch=getchar()) x=x*10+(ch^48);
 	x*=f;
}

int n,m1,m2,Now,id[N],P[N],r[N],p[N],c[N][2],v[N],M[N],val[N],m,val2[N];
Pr p1[N],p2[N];

inline int cmp1(const int& a,const int& b)
{
	return p1[a].y<p1[b].y;
}

inline int cmp2(const int& a,const int& b)
{
	return p2[a].y>p2[b].y;
}

#define Lc c[x][0]
#define Rc c[x][1]

inline bool ir(int x)
{
	return x&&(!p[x]||(c[p[x]][0]!=x&&c[p[x]][1]!=x));
}

inline void pd(int x)
{
	if(r[x])
		r[Lc]^=1,r[Rc]^=1,swap(Lc,Rc),r[x]=0;
}

inline void pu(int x)
{
	M[x]=x;
 	if(Lc&&v[M[Lc]]>v[M[x]])
	 	M[x]=M[Lc];
 	if(Rc&&v[M[Rc]]>v[M[x]])
	 	M[x]=M[Rc];
}

inline void apd(int x)
{
	if(!ir(x))
		apd(p[x]);
 	pd(x);
}

inline void Rot(int x)
{
	int y=p[x],w=ir(y),k=c[y][1]==x;
 	p[c[y][k]=c[x][!k]]=y;c[x][!k]=y;p[x]=p[y];p[y]=x;
 	if(!w) c[p[x]][c[p[x]][1]==y]=x;
 	pu(y);
}

inline void sp(int x)
{
	apd(x);
	while(!ir(x))
  		if(ir(p[x]))
		  	Rot(x);
  		else if((c[p[x]][0]==x)==(c[p[p[x]]][0]==p[x]))
		  	Rot(p[x]),Rot(x);
  		else
		  	Rot(x),Rot(x);
 	pu(x);
}

inline int Ac(int x)
{
	int y=0;
 	for(;x;x=p[x])
	 	sp(x),Rc=y,pu(y=x);
 	return y;
}

inline void Mr(int x)
{
	r[Ac(x)]^=1;sp(x);
}

inline int fr(int x)
{
	Ac(x);sp(x);
 	for(pd(x);Lc;pd(x=Lc));
 	return x;
}

inline void lk(int x,int y)
{
	if(fr(x)==fr(y))
		return;
	Mr(y);Ac(y);sp(y);
	p[y]=x;
}

#undef Lc
#undef Rc

vector<Pr> Lzz[N],Cjy[N],Edge[N];
int fa[N];

inline int gf(int u)
{
	return fa[u]==u?u:fa[u]=gf(fa[u]);
}

int main()
{
	freopen("connect.in","r",stdin);
	freopen("connect.out","w",stdout);
	get(n);m=n;get(m1);get(m2);
	static Pr Wlp1[N],Wlp2[N];
	for(int i=1;i<=m1;i++)
		get(p1[i].x),get(p1[i].y),id[i]=i;
	sort(id+1,id+m1+1,cmp1);
	for(int i=1;i<=m1;i++)
		P[id[i]]=i,Wlp1[i]=p1[id[i]];
	for(int i=1;i<n+m1;i++)
	{
		int f,a,b;get(f);get(a);get(b);
		if(f==1)
			Lzz[P[b]].push_back(Pr(1,a));
		else
		{
			int ia=P[a],ib=P[b];
			if(ia<ib)
				Lzz[ib].push_back(Pr(2,ia));
			else
				Lzz[ia].push_back(Pr(2,ib));
		}
	}
	for(int i=1;i<=m2;i++)
		get(p2[i].x),get(p2[i].y),id[i]=i;
	sort(id+1,id+m2+1,cmp2);
	for(int i=1;i<=m2;i++)
		P[id[i]]=i,Wlp2[i]=p2[id[i]];
	for(int i=1;i<n+m2;i++)
	{
		int f,a,b;get(f);get(a);get(b);
		if(f==1)
			Cjy[P[b]].push_back(Pr(1,a));
		else
		{
			int ia=P[a],ib=P[b];
			if(ia<ib)
				Cjy[ib].push_back(Pr(2,ia));
			else
				Cjy[ia].push_back(Pr(2,ib));
		}
	}
	for(int i=1;i<=m1;i++)
		fa[i]=i;
	for(int i=1;i<=m1;i++)
		for(int j=0;j<Lzz[i].size();j++)
		{
			int f=Lzz[i][j].x,x=Lzz[i][j].y;
			if(f==2)
				x=val[gf(x)];
			if(!x)
				fa[gf(Lzz[i][j].y)]=gf(i);
			if(x)
				if(val[i]==0)
					val[i]=x;
				else
				{
					if(fr(val[i])!=fr(x))
						v[++m]=Wlp1[i].y,pu(m),lk(m,val[i]),lk(m,x),Edge[i].push_back(Pr(val[i],x));
					val[i]=x;
				}
		}
	for(int i=1;i<=m2;i++)
		fa[i]=i;
	int Now=1;
	for(int i=m1,s=1;i&&Now<=m2;i--)
	{
		int Cut=1;
		for(int j=0;j<Edge[i].size();j++)
		{
			int x=Edge[i][j].x,y=Edge[i][j].y;
			Mr(x);Ac(y);sp(y);
			int pos=M[y];
			sp(pos);
			if(v[pos]==Wlp1[i].y)
				p[c[pos][0]]=p[c[pos][1]]=0,Cut++;
		}
		while((Cut!=1&&Now<=m2)||(Now!=1&&Wlp2[Now].y==Wlp2[Now-1].y))
		{
			val2[Now]=0;
			for(int j=0;j<Cjy[Now].size();j++)
			{
				int f=Cjy[Now][j].x,x=Cjy[Now][j].y;
				if(f==2)
					x=val2[gf(x)];
				if(!x)
					fa[gf(Cjy[Now][j].y)]=gf(Now);
				if(x)
					if(val2[Now]==0)
						val2[Now]=x;
					else
					{
						if(fr(val2[Now])!=fr(x))
							Cut--;
						else
						{
							Mr(x);Ac(val2[Now]);sp(val2[Now]);
							int pos=M[val2[Now]];
							sp(pos);p[c[pos][0]]=p[c[pos][1]]=0;
						}
						v[++m]=Wlp2[Now].y;pu(m);lk(m,val2[Now]),lk(m,x);val2[Now]=x;
					}
			}
			Now++;
		}
		if(Now<=m2&&(i==1||Wlp1[i].y!=Wlp1[i-1].y))
			Ans+=s*(m2-Now+1ll),s=1;
		else
			s++;
	}
	Orz=m1*(LL)m2;
	if(Ans==0)
		puts("0");
	else if(Ans==Orz)
		puts("1");
	else
	{
		LL r=gcd(Ans,Orz);printf("%lld/%lld",Ans/r,Orz/r);
	}
	return 0;
}
