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
const int maxn=100003;
struct Tpoint
{
	int x,y;
	inline bool operator <(const Tpoint &b)const{return x<b.x;}
}p[maxn];
struct Ttree
{
	int ls,rs,sum;
}tree[maxn*18];
int X[maxn],Y[maxn],n,num[maxn],Tnum=0,a[20],b[20],tot=0,root[maxn];
void modify(int pre,int &x,int l,int r,int num)
{
	x=++tot,tree[x]=tree[pre],tree[x].sum++;
	if(l==r)return;
	int mid=(l+r)/2;
	if(num<=mid)modify(tree[pre].ls,tree[x].ls,l,mid,num);
	else modify(tree[pre].rs,tree[x].rs,mid+1,r,num);
}
int ask(int t,int l,int r,int b)
{
	if(r<=b)return tree[t].sum;
	int mid=(l+r)/2;
	int res=ask(tree[t].ls,l,mid,b);
	if(b>mid)res+=ask(tree[t].rs,mid+1,r,b);
	return res;
}
inline int find(int x){return lower_bound(num+1,num+1+Tnum,x)-num;}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=Tnum=get();
	for(int i=1;i<=n;i++)p[i].x=X[i]=get(),p[i].y=Y[i]=get();
	sort(X+1,X+1+n),sort(Y+1,Y+1+n),sort(p+1,p+1+n);
	memcpy(num+1,Y+1,4*n);Tnum=unique(num+1,num+1+Tnum)-num-1;
	for(int i=1;i<=n;i++)
		modify(root[i-1],root[i],1,Tnum,p[i].y=find(p[i].y));
	for(int i=1;i<=9;i++)a[i]=get();
	sort(a+1,a+10);
	do
	{
		int x1=a[1]+a[2]+a[3],x2=x1+a[4]+a[5]+a[6];
		int y1=a[1]+a[4]+a[7],y2=y1+a[2]+a[5]+a[8];
		if(X[x1]==X[x1+1]||X[x2]==X[x2+1]||Y[y1]==Y[y1+1]||Y[y2]==Y[y2+1])continue;
		int z1=find(Y[y1]),z2=find(Y[y2]);
		if(ask(root[x1],1,Tnum,z1)!=a[1])continue;
		if(ask(root[x1],1,Tnum,z2)!=a[1]+a[2])continue;
		if(ask(root[x2],1,Tnum,z1)!=a[1]+a[4])continue;
		if(ask(root[x2],1,Tnum,z2)!=a[1]+a[2]+a[4]+a[5])continue;
		return printf("%lf %lf\n%lf %lf\n",X[x1]+.5,X[x2]+.5,Y[y1]+.5,Y[y2]+.5),0;
	}while(next_permutation(a+1,a+10));
	puts("-1");
	return 0;
}
