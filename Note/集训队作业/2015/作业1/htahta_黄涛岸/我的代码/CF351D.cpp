#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <ctime>
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
const int maxn=100333;
int n,p1[maxn],p2[maxn],pos[maxn],m,ans[maxn];
struct data
{
	int l,r,id;
	inline bool operator <(const data &b)const{return r<b.r;}
}a[maxn];
struct BIT
{
	int c[maxn];
	inline int ask(int x)
	{
		int res=0;
		for(;x<=n;x+=x&-x)res+=c[x];
		return res;
	}
	inline void add(int x,int v)
	{
		for(;x;x-=x&-x)c[x]+=v;
	}
}A,B;
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get();
	for(int i=1;i<=n;i++)
	{
		int x=get();
		p1[i]=pos[x],pos[x]=i;
		p2[i]=i-p1[i]==p1[i]-p1[p1[i]]?p2[p1[i]]:p1[p1[i]];
	}
	m=get();
	for(int i=1;i<=m;i++)a[i].l=get(),a[i].r=get(),a[i].id=i;
	sort(a+1,a+1+m);
	for(int i=1,j=1;i<=n&&j<=m;i++)
	{
		A.add(i,1),A.add(p1[i],-1);
		B.add(p2[i],1),B.add(p2[p1[i]],-1);
		for(int x;j<=m&&a[j].r==i;j++)
			x=A.ask(a[j].l),ans[a[j].id]=x+(x==B.ask(a[j].l));
	}
	for(int i=1;i<=m;i++)printf("%d\n",ans[i]);
	return 0;
}

