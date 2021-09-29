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
const int maxn=1003;
double p[maxn][maxn],s=0;
int a[maxn],n,T;
int main()
{
	n=get();T=get();
	for(int i=1;i<=n;i++)a[i]=get();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)p[i][j]=a[i]>a[j]?1:0;
	while(T--)
	{
		int x=get(),y=get();
		p[x][y]=p[y][x]=0.5;
		for(int i=1;i<=n;i++)
			if(i!=x&&i!=y)p[i][x]=p[i][y]=(p[i][x]+p[i][y])/2,p[x][i]=p[y][i]=1-p[i][x];
	}
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)s+=p[i][j];
	printf("%.9lf\n",s);
	return 0;
}
