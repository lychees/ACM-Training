#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f==1)return -v;else return v;
}
const int maxn=50003;
typedef long long LL;
LL dp[maxn];
int n,tot=1,Q[maxn],f,r;
struct Tpoint
{
	LL x,y;
	inline bool operator <(const Tpoint &b)const{return x==b.x?y>b.y:x>b.x;}
}p[maxn];
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get();
	for(int i=1;i<=n;i++)p[i].x=get(),p[i].y=get();
	sort(p+1,p+1+n);
	for(int i=2;i<=n;i++)
		if(p[i].y>p[tot].y)p[++tot]=p[i];
	n=tot;f=r=1;
	for(int i=1;i<=tot;i++)p[i-1].x=p[i].x;
	for(int i=1;i<=n;i++)
	{
		while(f<r&&dp[Q[f+1]]-dp[Q[f]]<p[i].y*(p[Q[f]].x-p[Q[f+1]].x))f++;
		dp[i]=dp[Q[f]]+p[i].y*p[Q[f]].x;
		while(f<r&&(dp[Q[r]]-dp[Q[r-1]])*(p[Q[r]].x-p[i].x)>(dp[i]-dp[Q[r]])*(p[Q[r-1]].x-p[Q[r]].x))r--;
		Q[++r]=i;
	}
	cout<<dp[n]<<endl;
	return 0;
}
