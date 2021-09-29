#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
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
const int maxn=1003;
LL a[maxn][maxn],b[maxn][maxn],c[maxn][maxn];
int n,m,k;
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get(),m=get();k=get();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			a[i][j]=a[i-1][j]+a[i][j-1]+get()-a[i-1][j-1],
			b[i][j]=b[i-1][j+1]+a[i][j]-(i>k&&j+k<=m?a[i-k][j+k]:0),
			c[i][j]=c[i-1][j-1]+a[i][j]-(i>k&&j>k?a[i-k][j-k]:0);
		b[i][0]=b[i-1][1]-(i>k?a[i-k][k]:0);
	}
	LL v=-1,t;int x,y;
	for(int i=k;i<=n-k+1;i++)
		for(int j=k;j<=m-k+1;j++)
			if((t=b[i+k-1][j]+b[i-1][j-k]-c[i+k-1][j-1]-c[i-1][j+k-1])>v)v=t,x=i,y=j;
	printf("%d %d\n",x,y);
	return 0;
}
