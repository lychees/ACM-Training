#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 100010
using namespace std;
struct Point
{
	int x,y;
	friend bool operator < (const Point &a,const Point &b)
	{
		return a.x<b.x;
	}
}p[maxn];
int l[15][4][maxn],r[15][4][maxn];
int n,a[15],px[maxn],nx,py[maxn],ny;
int row[maxn][2],col[maxn][2];
void read()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d %d",&p[i].x,&p[i].y);
		px[i]=p[i].x,py[i]=p[i].y;
	}
	sort(px+1,px+n+1),nx=unique(px+1,px+n+1)-px-1;
	sort(py+1,py+n+1),ny=unique(py+1,py+n+1)-py-1;
	for(int i=1;i<=n;++i)
	{
		p[i].x=lower_bound(px+1,px+nx+1,p[i].x)-px;
		p[i].y=lower_bound(py+1,py+ny+1,p[i].y)-py;
	}
	for(int i=1;i<=9;++i)
		scanf("%d",a+i);
	sort(p+1,p+n+1);
	static int sum[maxn];
	for(int i=1;i<=n;++i)
		++sum[p[i].x];
	for(int i=2;i<=nx;++i)
		sum[i]+=sum[i-1];
	for(int i=1;i<=nx;++i)
		row[sum[i]][0]=i,row[n-sum[i-1]][1]=i;
	memset(sum,0,sizeof(sum));
	for(int i=1;i<=n;++i)
		++sum[p[i].y];
	for(int i=2;i<=ny;++i)
		sum[i]+=sum[i-1];
	for(int i=1;i<=ny;++i)
		col[sum[i]][0]=i,col[n-sum[i-1]][1]=i;
}
void Prepare()
{
	static int sum[maxn];
	for(int k=1,tot1,tot2,tot3,tot4;k<=9;++k)
	{
		tot1=0,tot2=0,tot3=0,tot4=0;
		l[k][0][0]=r[k][0][0]=ny;
		l[k][1][0]=r[k][1][0]=0;
		memset(sum,0,sizeof(sum));
		for(int i=1,j=1;i<=nx;++i)
		{
			int &l0=l[k][0][i],&l1=l[k][1][i];
			int &r0=r[k][0][i],&r1=r[k][1][i];
			l0=l[k][0][i-1],l1=l[k][1][i-1],r0=r[k][0][i-1],r1=r[k][1][i-1];
			while(p[j].x==i)
			{
				tot1+=p[j].y<=l0;
				tot2+=p[j].y<=r0;
				tot3+=p[j].y>=l1;
				tot4+=p[j].y>=r1;
				++sum[p[j++].y];
			}
			while(tot1>=a[k])
				tot1-=sum[l0--];
			while(tot2>a[k])
				tot2-=sum[r0--];
			while(tot3>a[k])
				tot3-=sum[l1++];
			while(tot4>=a[k])
				tot4-=sum[r1++];
		}
		tot1=0,tot2=0,tot3=0,tot4=0;
		l[k][2][nx+1]=r[k][2][nx+1]=ny;
		l[k][3][nx+1]=r[k][3][nx+1]=0;
		memset(sum,0,sizeof(sum));
		for(int i=nx,j=n;i>=1;--i)
		{
			int &l0=l[k][2][i],&l1=l[k][3][i];
			int &r0=r[k][2][i],&r1=r[k][3][i];
			l0=l[k][2][i+1],l1=l[k][3][i+1],r0=r[k][2][i+1],r1=r[k][3][i+1];
			while(p[j].x==i)
			{
				tot1+=p[j].y<=l0;
				tot2+=p[j].y<=r0;
				tot3+=p[j].y>=l1;
				tot4+=p[j].y>=r1;
				++sum[p[j--].y];
			}
			while(tot1>=a[k])
				tot1-=sum[l0--];
			while(tot2>a[k])
				tot2-=sum[r0--];
			while(tot3>a[k])
				tot3-=sum[l1++];
			while(tot4>=a[k])
				tot4-=sum[r1++];
		}
	}
}
void DFS(int p)
{
	static bool use[15];
	static int F[15],f[15];
	if(p>9)
	{
		int a=row[F[1]+F[2]+F[3]][1],b=row[F[7]+F[8]+F[9]][0];
		int c=col[F[1]+F[4]+F[7]][0],d=col[F[3]+F[6]+F[9]][1];
		if(!a||!b||!c||!d)
			return ;
		if(l[f[1]][2][a]>=c||r[f[1]][2][a]<c)
			return ;
		if(l[f[3]][3][a]>d||r[f[3]][3][a]<=d)
			return ;
		if(l[f[7]][0][b]>=c||r[f[7]][0][b]<c)
			return ;
		if(l[f[9]][1][b]>d||r[f[9]][1][b]<=d)
			return ;
		printf("%f %f\n",px[a]-0.5,px[b]+0.5);
		printf("%f %f\n",py[c]+0.5,py[d]-0.5);
		exit(0);
	}
	for(int i=1;i<=9;++i)
		if(!use[i])
		{
			use[i]=true,F[p]=a[i],f[p]=i;
			DFS(p+1);
			use[i]=false;
		}
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	Prepare();
	DFS(1);
	printf("-1\n");
	fclose(stdin);
	fclose(stdout);
	return 0;
}
