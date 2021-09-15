#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 100010
using namespace std;
int cnta[maxn][30],cntb[maxn][30];
int n,m,S,a[maxn],b[maxn],fail[maxn];
void read()
{
	scanf("%d %d %d",&n,&m,&S);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",a+i);
		for(int j=1;j<=S;++j)
			cnta[i][j]=cnta[i-1][j];
		for(int j=a[i];j<=S;++j)
			++cnta[i][j];
	}
	for(int i=1;i<=m;++i)
	{
		scanf("%d",b+i);
		for(int j=1;j<=S;++j)
			cntb[i][j]=cntb[i-1][j];
		for(int j=b[i];j<=S;++j)
			++cntb[i][j];
	}
}
bool equal(int *sum1,int *sum2,int *sum3,int c1,int c2)
{
	return sum1[c1-1]==sum2[c2-1]-sum3[c2-1]&&sum1[c1]==sum2[c2]-sum3[c2];
}
void GetFail()
{
	for(int i=1,j;i<=m;++i)
	{
		for(j=fail[i];j&&!equal(cntb[j],cntb[i],cntb[i-j],b[j+1],b[i+1]);j=fail[j]);
		if(equal(cntb[j],cntb[i],cntb[i-j],b[j+1],b[i+1]))
			fail[i+1]=++j;
	}
}
void KMP()
{
	static int ans[maxn];
	int tot=0;
	for(int i=1,j=0;i<=n;++i)
	{
		for(;j&&!equal(cntb[j],cnta[i-1],cnta[i-j-1],b[j+1],a[i]);j=fail[j]);
		if(equal(cntb[j],cnta[i-1],cnta[i-j-1],b[j+1],a[i]))
			++j;
		if(j==m)
			ans[++tot]=i-m+1,j=fail[j];
	}
	printf("%d\n",tot);
	for(int i=1;i<=tot;++i)
		printf("%d\n",ans[i]);
}
int main()
{
	freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	read();
	GetFail();
	KMP();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
