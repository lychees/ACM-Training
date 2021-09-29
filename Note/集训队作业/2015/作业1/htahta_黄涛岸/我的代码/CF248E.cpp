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
const int maxn=100003,maxk=103;
double p[maxn][maxk],ans=0;
int n,T,a[maxn],b[maxn];
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get();
	for(int i=1;i<=n;i++)p[i][b[i]=a[i]=get()]=1,ans+=(!a[i]);
	T=get();
	while(T--)
	{
		int x=get(),y=get(),k=get(),t=a[x];
		ans-=p[x][0];
		for(int j=1;j<=k;j++,t--)
			for(int i=0;i<=b[x];i++)
				p[x][i]=p[x][i]*(t-i)/t+p[x][i+1]*(i+1)/t;
		b[x]-=max(k-(a[x]-b[x]),0);
		a[x]-=k,a[y]+=k;
		printf("%.10lf\n",ans+=p[x][0]);
	}
	return 0;
}
