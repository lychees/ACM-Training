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
const int maxn=203;
int e[maxn][maxn],f[maxn][maxn],n,m,ans=1000000000,a[maxn],T,d1[maxn],d2[maxn];
inline bool cmp(int a,int b){return f[T][a]>f[T][b];}
inline void gmin(int &a,int b){if(b<a)a=b;}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get(),m=get();
	memset(f,60,sizeof(f));
	for(int i=1;i<=n;i++)f[i][i]=0,a[i]=i;
	for(int i=1;i<=m;i++)
	{
		int x=get(),y=get(),z=get();
		f[x][y]=f[y][x]=e[x][y]=e[y][x]=z;
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)f[i][j]=min(f[i][k]+f[k][j],f[i][j]);
	for(int i=1;i<=n;i++)
	{
		T=i,sort(a+1,a+1+n,cmp);
		for(int j=i+1,x;j<=n;j++)
		{
			if(!e[i][j])continue;
			for(int k=1;k<=n;k++)d1[k]=f[i][a[k]],d2[k]=f[j][a[k]];
			gmin(ans,d1[1]*2);x=d2[1];
			for(int k=2;k<=n;k++)
				if(x<d2[k])gmin(ans,d1[k]+x+e[i][j]),x=d2[k];
			gmin(ans,x*2);
		}
	}
	printf("%.1lf\n",ans*0.5);
	return 0;
}

