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
typedef long long LL;
const int maxn=100003;
struct Tpoint
{
	LL x,y;
	inline bool operator <(const Tpoint &b)const{return b.x==x?y>b.y:x<b.x;}
}p[maxn];
LL s[maxn],a,b,c,d;
int n,tot=0;
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get(),a=get(),b=get(),c=get(),d=get();
	for(int i=1;i<=n;i++)
	{
		LL x=get(),y=get();
		p[i].x=c*x-d*y;p[i].y=b*y-a*x;
	}
	sort(p+1,p+1+n);
	for(int k,i=1;i<=n;i++)
		if(p[i].x>0&&p[i].y>0)
		{
			s[k=lower_bound(s,s+1+tot,p[i].y)-s]=p[i].y;
			if(k==tot+1)tot=k;
		}
	printf("%d\n",tot);
	return 0;
}
