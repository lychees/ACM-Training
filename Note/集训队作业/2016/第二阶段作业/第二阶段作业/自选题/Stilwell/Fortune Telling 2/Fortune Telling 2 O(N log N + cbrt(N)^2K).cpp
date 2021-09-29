#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
using namespace std;

int n,m,p,S,i,j,k,l,r,u,v;
int a[200005],b[200005],c[200005],d[1005];
int da[200005],db[200005];
bool rev[200005],w[205][205],re;
long long ans;

struct node
{
	int a,id;
}A[200005],B[200005];
inline bool cmp(const node &a,const node &b){return a.a>b.a;}

int main()
{
	scanf("%d%d",&n,&m);S=(int)(pow(n,1.0/3)*1.25);
	for(i=1;i<=n;++i)
	{
		scanf("%d%d",&a[i],&b[i]);
		A[i].a=a[i];A[i].id=i;
		B[i].a=b[i];B[i].id=i;
	}
	sort(A+1,A+n+1,cmp);
	sort(B+1,B+n+1,cmp);
	for(i=1;i<=m;++i)scanf("%d",&c[i]);
	for(l=1;l<=m;l=r+1)
	{
		r=l+S;if(r>n)r=n;
		for(i=l,p=0;i<=r;++i)d[++p]=c[i];
		sort(d+1,d+p+1);
		d[++p]=1000000005;
		for(i=1;i<=p;++i)
		for(j=1;j<=p;++j)
		{
			u=d[i];v=d[j];re=false;
			for(k=l;k<=r;++k)if(u<=c[k])swap(u,v),re^=1;
			w[i][j]=re;
		}
		for(i=1,k=p;i<=n;++i)
		{
			for(;k>1&&A[i].a<=d[k-1];--k);
			da[A[i].id]=k;
		}
		for(i=1,k=p;i<=n;++i)
		{
			for(;k>1&&B[i].a<=d[k-1];--k);
			db[B[i].id]=k;
		}
		for(i=1;i<=n;++i)
		if(rev[i])rev[i]^=w[db[i]][da[i]];
		else rev[i]^=w[da[i]][db[i]];
	}
	for(i=1;i<=n;++i)if(rev[i])ans+=b[i];else ans+=a[i];
	printf("%I64d\n",ans);
}
