#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 110
#define maxm 5010
#define eps 1e-7
using namespace std;
struct Edge
{
	int a,b,c;
}e[maxm];
int n,m;
double A[maxn][maxn];
void read()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		scanf("%d %d %d",&e[i].a,&e[i].b,&e[i].c);
		int x=e[i].a,y=e[i].b;
		++A[x][x],--A[x][y];
		++A[y][y],--A[y][x];
	}
	memset(A[1],0,sizeof(A[1]));
	A[1][1]=1,A[n][n+1]=1;
}
void Gauss()
{
	static int p[maxn];
	int tot=0;
	for(int j=1;j<=n;++j)
	{
		int id=-1;
		for(int i=tot+1;i<=n;++i)
			if(id==-1||abs(A[id][j])<abs(A[i][j]))
				id=j;
		if(abs(A[id][j])<eps)
			continue;
		p[++tot]=j;
		for(int k=j;k<=n+1;++k)
			swap(A[id][k],A[tot][k]);
		for(int i=tot+1;i<=n;++i)
		{
			double x=A[i][j]/A[tot][j];
			for(int k=j;k<=n+1;++k)
				A[i][k]-=A[tot][k]*x;
		}
	}
	static double x[maxn];
	double ans=1e100;
	if(abs(A[tot][n])>eps&&p[tot]==n)
		x[n]=A[tot][n+1]/A[tot][n];
	else
		ans=0;
	for(int j=tot-1;j>=1;--j)
	{
		int i=p[j];
		x[i]=A[j][n+1];
		for(int k=i+1;k<=n;++k)
			x[i]-=A[j][k]*x[k];
		x[i]/=A[j][i];
	}
	for(int i=1;i<=m;++i)
		if(abs(x[e[i].a]-x[e[i].b])>eps)
			ans=min(ans,e[i].c/abs(x[e[i].a]-x[e[i].b]));
	printf("%f\n",ans);
	for(int i=1;i<=m;++i)
		printf("%f\n",ans*(x[e[i].b]-x[e[i].a]));

}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	Gauss();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
