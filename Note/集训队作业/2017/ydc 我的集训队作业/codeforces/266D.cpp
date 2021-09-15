#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 210
#define maxm maxn*maxn
using namespace std;
int F[maxn][maxn];
int n,m,u[maxm],v[maxm],len[maxm];
void read()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(i!=j)
				F[i][j]=1<<29;
	for(int i=1;i<=m;++i)
	{
		scanf("%d %d %d",u+i,v+i,len+i);
		F[u[i]][v[i]]=F[v[i]][u[i]]=len[i];
	}
}
double work()
{
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				F[i][j]=min(F[i][j],F[i][k]+F[k][j]);
	int ans=1<<30;
	static pair<int,int> a[maxn];
	for(int i=1;i<=m;++i)
	{
		for(int j=1;j<=n;++j)
			a[j]=make_pair(F[j][u[i]],F[j][v[i]]);
		sort(a+1,a+n+1);
		int maxv=0;
		for(int j=n;j>=1;--j)
		{
			ans=min(ans,max(max(a[j].first,maxv)*2,a[j].first+maxv+len[i]));
			maxv=max(maxv,a[j].second);
		}
	}
	return ans/2.0;
}
int main()
{
	read();
	printf("%f\n",work());
	return 0;
}
