#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<bitset>
#define maxn 100010
using namespace std;
typedef long long LL;
int n;
LL a[maxn],b[maxn];
int x[maxn];
bitset<maxn> A[70];
void read()
{
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i];
}
bool Gauss(LL X)
{
	static int p[maxn];
	int tot=0,m=0;
	for(int i=60;i>=1;--i)
		if(X>>(i-1)&1)
		{
			++tot;
			for(int j=1;j<=n;++j)
				A[tot][j]=a[j]>>(i-1)&1;
			A[tot][n+1]=1;
		}
	for(int j=1,i=1;j<=n&&i<=tot;++j)
	{
		int k;
		for(k=i;k<=tot&&!A[k][j];++k);
		if(k>tot)
			continue;
		swap(A[i],A[k]);
		for(int k=i+1;k<=tot;++k)
			if(A[k][j])
				A[k]^=A[i];
		p[++m]=j,++i;
	}
	if(m<tot)
	{
		for(int i=m+1;i<=tot;++i)
			if(A[i][n+1])
				return false;
	}
	memset(x,0,sizeof(x));
	x[p[m]]=A[m][n+1];
	for(int i=m-1;i>=1;--i)
	{
		x[p[i]]=A[i][n+1];
		for(int j=i+1;j<=m;++j)
			if(A[i][p[j]])
				x[p[i]]^=x[p[j]];
	}
	return true;
}
void work()
{
	LL all=0,x2=0;
	for(int i=1;i<=n;++i)
		all^=a[i];
	for(int i=60;i>=1;--i)
		if(!(all>>(i-1)&1)&&Gauss(x2|(1LL<<(i-1))))
			x2|=1LL<<(i-1);
	for(int i=60;i>=1;--i)
		if((all>>(i-1)&1)&&Gauss(x2|(1LL<<(i-1))))
			x2|=1LL<<(i-1);
	Gauss(x2);
	for(int i=1;i<=n;++i)
		printf("%d ",x[i]?2:1);
	printf("\n");
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	work();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
