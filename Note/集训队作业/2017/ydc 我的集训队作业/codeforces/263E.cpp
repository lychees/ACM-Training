#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<assert.h>
#define maxn 1010
using namespace std;
typedef long long LL;
int nRow,nCol,m,a[maxn][maxn];
LL val[maxn][maxn];
void read()
{
	scanf("%d %d %d",&nRow,&nCol,&m);
	for(int i=1;i<=nRow;++i)
		for(int j=1;j<=nCol;++j)
			scanf("%d",&a[i][j]);
}
LL getsum(int a,int b,int c,int d,LL (*sum)[maxn])
{
	return sum[c][d]-sum[a-1][d]-sum[c][b-1]+sum[a-1][b-1];
}
void calc()
{
	static LL sum1[maxn][maxn],sum2[maxn][maxn],sum3[maxn*2][maxn],sum4[maxn*2][maxn],sum5[maxn*2][maxn],sum6[maxn*2][maxn];
	memset(sum3,0,sizeof(sum3));
	memset(sum4,0,sizeof(sum4));
	memset(sum5,0,sizeof(sum5));
	memset(sum6,0,sizeof(sum6));
	for(int i=1;i<=nRow;++i)
		for(int j=1;j<=nCol;++j)
		{
			sum1[i][j]=sum1[i-1][j]+sum1[i][j-1]-sum1[i-1][j-1]+(i+j+m)*a[i][j];
			sum2[i][j]=sum2[i-1][j]+sum2[i][j-1]-sum2[i-1][j-1]+a[i][j];
			sum3[i+j][i]=sum5[i+j][j]=(i+j+m)*a[i][j];
			sum4[i+j][i]=sum6[i+j][j]=a[i][j];
		}
	for(int i=2;i<=nRow+nCol;++i)
		for(int j=1;j<=nRow;++j)
		{
			sum3[i][j]=sum3[i][j]+sum3[i-1][j]+sum3[i][j-1]-sum3[i-1][j-1];
			sum4[i][j]=sum4[i][j]+sum4[i-1][j]+sum4[i][j-1]-sum4[i-1][j-1];
		}
	for(int i=2;i<=nRow+nCol;++i)
		for(int j=1;j<=nCol;++j)
		{
			sum5[i][j]=sum5[i][j]+sum5[i-1][j]+sum5[i][j-1]-sum5[i-1][j-1];
			sum6[i][j]=sum6[i][j]+sum6[i-1][j]+sum6[i][j-1]-sum6[i-1][j-1];
		}
	for(int i=m;i<=nRow-m+1;++i)
		for(int j=m;j<=nCol-m+1;++j)
		{
			LL v1=(sum3[nRow+nCol][nRow]-sum3[i+j-m-1][nRow])-(i+j)*(sum4[nRow+nCol][nRow]-sum4[i+j-m-1][nRow]);
			LL v2=getsum(i+j-m,i,nRow+nCol,nRow,sum3)-(i+j)*getsum(i+j-m,i,nRow+nCol,nRow,sum4);
			LL v3=getsum(i+j-m,j,nRow+nCol,nCol,sum5)-(i+j)*getsum(i+j-m,j,nRow+nCol,nCol,sum6);
			LL v4=getsum(i,j,nRow,nCol,sum1)-(i+j)*getsum(i,j,nRow,nCol,sum2);
			val[i][j]=v1-v2-v3+v4;
		}
}
void work()
{
	static LL ans[maxn][maxn],sum1[maxn],sum2[maxn];
	for(int i=1;i<=nRow;++i)
		for(int j=1;j<=nCol;++j)
			ans[i][j]=a[i][j]*m;
	for(int i=m;i<=nRow-m+1;++i)
	{
		for(int j=1;j<=nCol;++j)
			sum1[j]=sum1[j-1]+a[i][j]*(j+m),sum2[j]=sum2[j-1]+a[i][j];
		for(int j=m;j<=nCol-m+1;++j)
			ans[i][j]+=(sum1[j-1]-sum1[j-m])-j*(sum2[j-1]-sum2[j-m]);
		for(int j=nCol;j>=1;--j)
			sum1[j]=sum1[j+1]+a[i][j]*(m-j),sum2[j]=sum2[j+1]+a[i][j];
		for(int j=m;j<=nCol-m+1;++j)
			ans[i][j]+=(sum1[j+1]-sum1[j+m])+j*(sum2[j+1]-sum2[j+m]);
	}
	sum1[nRow+1]=sum2[nRow+1]=0;
	for(int j=m;j<=nCol-m+1;++j)
	{
		for(int i=1;i<=nRow;++i)
			sum1[i]=sum1[i-1]+a[i][j]*(i+m),sum2[i]=sum2[i-1]+a[i][j];
		for(int i=m;i<=nRow-m+1;++i)
			ans[i][j]+=(sum1[i-1]-sum1[i-m])-i*(sum2[i-1]-sum2[i-m]);
		for(int i=nRow;i>=1;--i)
			sum1[i]=sum1[i+1]+a[i][j]*(m-i),sum2[i]=sum2[i+1]+a[i][j];
		for(int i=m;i<=nRow-m+1;++i)
			ans[i][j]+=(sum1[i+1]-sum1[i+m])+i*(sum2[i+1]-sum2[i+m]);
	}
	calc();
	for(int i=m;i<=nRow-m+1;++i)
		for(int j=m;j<=nCol-m+1;++j)
			ans[i][j]+=val[i][j];
	for(int i=1;i*2<=nRow;++i)
		for(int j=1;j<=nCol;++j)
			swap(a[i][j],a[nRow-i+1][j]);
	calc();
	for(int i=m;i<=nRow-m+1;++i)
		for(int j=m;j<=nCol-m+1;++j)
			ans[nRow-i+1][j]+=val[i][j];
	for(int i=1;i<=nRow;++i)
		for(int j=1;j*2<=nCol;++j)
			swap(a[i][j],a[i][nCol-j+1]);
	calc();
	for(int i=m;i<=nRow-m+1;++i)
		for(int j=m;j<=nCol-m+1;++j)
			ans[nRow-i+1][nCol-j+1]+=val[i][j];
	for(int i=1;i*2<=nRow;++i)
		for(int j=1;j<=nCol;++j)
			swap(a[i][j],a[nRow-i+1][j]);
	calc();
	for(int i=m;i<=nRow-m+1;++i)
		for(int j=m;j<=nCol-m+1;++j)
			ans[i][nCol-j+1]+=val[i][j];
	int x,y;
	LL maxv=-1000000000000000000LL;
	for(int i=m;i<=nRow-m+1;++i)
		for(int j=m;j<=nCol-m+1;++j)
			if(maxv<ans[i][j])
				maxv=ans[i][j],x=i,y=j;
	printf("%d %d\n",x,y);
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	work();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
