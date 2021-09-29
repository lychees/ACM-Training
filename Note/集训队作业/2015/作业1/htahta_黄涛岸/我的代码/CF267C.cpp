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
const int maxn=133,maxm=5003;
const double eps=1e-11;
int X[maxm],Y[maxm],C[maxm],n,m;
double a[maxn][maxn],x[maxn];
int main()
{
	n=get(),m=get();
	for(int i=1;i<=m;i++)
	{
		X[i]=get(),Y[i]=get(),C[i]=get();
		a[X[i]][X[i]]++,a[X[i]][Y[i]]--;
		a[Y[i]][Y[i]]++,a[Y[i]][X[i]]--;
	}
	for(int i=2;i<=n;i++)a[1][i]=0;
	a[1][1]=a[n][n+1]=1;
	for(int i=1;i<=n;i++)
	{
		int master=i;
		for(int j=i+1;j<=n;j++)
			if(fabs(a[master][i])<fabs(a[j][i]))master=i;
		for(int j=i;j<=n+1;j++)swap(a[master][j],a[i][j]);
		if(fabs(a[i][i])<eps)continue;
		for(int j=i+1;j<=n;j++)
		{
			double tp=a[j][i]/a[i][i];
			for(int k=i;k<=n+1;k++)a[j][k]-=a[i][k]*tp;
		}
	}
	for(int i=n;i;i--)
	{
		if(fabs(a[i][i])<eps)continue;
		for(int j=i+1;j<=n;j++)a[i][n+1]-=a[i][j]*x[j];
		x[i]=a[i][n+1]/a[i][i];
	}
	double c=fabs(x[n])<eps?0:1e100;
	for(int i=1;i<=m;i++)
	{
		double tp=abs(x[X[i]]-x[Y[i]]);
		if(fabs(tp)>eps)c=min(c,C[i]/tp);
	}
	printf("%.10lf\n",c);
	for(int i=1;i<=m;i++)printf("%.10lf\n",c*(x[Y[i]]-x[X[i]]));
	return 0;
}
