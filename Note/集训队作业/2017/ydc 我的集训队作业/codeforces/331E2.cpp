#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#include<ctime>
#define each(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
#define maxn 110
#define mod 1000000007
using namespace std;
typedef long long LL;
struct Edge
{
	int a,b;
	vector<int> p;
}e[2000];
vector<int> g[maxn][maxn],h[maxn][maxn],go[maxn];
int dp[maxn][maxn][maxn],f[maxn][maxn],sum[maxn][maxn][maxn];
int n,m,map[maxn][maxn];
void Read(int &digit)
{
	digit=0;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
}
void add(int &a,int b)
{
	a+=b;
	if(a>=mod)
		a-=mod;
}
void read()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		int tot;
		scanf("%d %d %d",&e[i].a,&e[i].b,&tot);
		if(!tot)
			go[e[i].a].push_back(e[i].b);
		for(int j=1,x;j<=tot;++j)
		{
			scanf("%d",&x);
			e[i].p.push_back(x);
		}
		map[e[i].a][e[i].b]=i;
	}
}
void findpath(int ide,int id1,int id2)
{
	static int q1[maxn*2],q2[maxn*2];
	int rear1=0,rear2=0;
	for(int i=id1;i>=0;--i)
		q1[++rear1]=e[ide].p[i];
	int front1=1,front2=1;
	while(rear1<=2*n&&front1<rear1)
	{
		int p=q1[front1],q=q1[++front1],id=map[q][p];
		if(id==0)
			return ;
		for(int i=(int)e[id].p.size()-1;i>=0&&rear1<=2*n;--i)
			q1[++rear1]=e[id].p[i];
	}
	for(int i=id2;i<(int)e[ide].p.size();++i)
		q2[++rear2]=e[ide].p[i];
	while(rear2<=2*n&&front2<rear2)
	{
		int p=q2[front2],q=q2[++front2],id=map[p][q];
		if(id==0)
			return ;
		for(int i=0;i<(int)e[id].p.size()&&rear2<=2*n;++i)
			q2[++rear2]=e[id].p[i];
	}
	if(rear1+rear2>2*n)
		return ;
	++dp[rear1+rear2-1][q1[rear1]][q2[rear2]];
}
void findpath1(int ide,int p)
{
	static int queue[maxn*2];
	int rear=0;
	for(int i=0;i<(int)e[ide].p.size();++i)
		queue[++rear]=e[ide].p[i];
	int front=1;
	while(rear<=n*2&&front<rear)
	{
		int p=queue[front],q=queue[++front],id=map[p][q];
		if(id==0)
			return ;
		for(int i=0;i<(int)e[id].p.size()&&rear<=2*n;++i)
			queue[++rear]=e[id].p[i];
	}
	if(rear>n*2)
		return ;
	g[p][queue[rear]].push_back(rear);
}
void findpath2(int ide,int p)
{
	static int queue[maxn*2];
	int rear=0;
	for(int i=(int)e[ide].p.size()-1;i>=0;--i)
		queue[++rear]=e[ide].p[i];
	int front=1;
	while(rear<=n*2&&front<rear)
	{
		int p=queue[front],q=queue[++front],id=map[q][p];
		if(id==0)
			return ;
		for(int i=(int)e[id].p.size()-1;i>=0&&rear<=2*n;--i)
			queue[++rear]=e[id].p[i];
	}
	if(rear>2*n)
		return ;
	h[queue[rear]][p].push_back(rear);
}
void work()
{
	for(int i=1;i<=m;++i)
		for(int j=1;j<(int)e[i].p.size();++j)
			if((int)e[i].p.size()<=2*n&&e[i].p[j]==e[i].b&&e[i].p[j-1]==e[i].a)
				findpath(i,j-1,j);
	for(int i=1;i<=m;++i)
		if(e[i].p.size()&&e[i].p[0]==e[i].b)
			findpath1(i,e[i].a);
	for(int i=1;i<=m;++i)
		if(e[i].p.size()&&e[i].p[(int)e[i].p.size()-1]==e[i].a)
			findpath2(i,e[i].b);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
		{
			sort(g[i][j].begin(),g[i][j].end());
			sort(h[i][j].begin(),h[i][j].end());
		}
	for(int i=1;i<=2*n;++i)
		for(int a=1;a<=n;++a)
			for(int b=1;b<=n;++b)
				for(int c=1;c<=n;++c)
					each(p,g[b][c])
					{
						if(*p>=i)
							break;
						add(dp[i][a][c],dp[i-*p][a][b]);
					}
	for(int i=1;i<=2*n;++i)
		for(int a=1;a<=n;++a)
			for(int b=1;b<=n;++b)	
				for(int c=1;c<=n;++c)
					each(p,h[a][b])
					{
						if(*p>=i)
							break;
						add(dp[i][a][c],dp[i-*p][b][c]);
					}
	for(int i=1;i<=2*n;++i)
		for(int j=1;j<=n;++j)
			for(int k=1;k<=n;++k)
			{
				add(f[i][k],dp[i][j][k]);
				each(c,go[j])
					add(sum[j][i][k],dp[i-1][*c][k]);
			}
	for(int i=1;i<=2*n;++i)
		for(int b=1;b<=n;++b)
			if(f[i][b])
				for(int e1=1;e1+i<=2*n;++e1)
					for(int d=1;d<=n;++d)
						add(f[i+e1][d],(LL)f[i][b]*sum[b][e1][d]%mod);
	for(int i=1;i<=2*n;++i)
	{
		int ans=0;
		for(int k=1;k<=n;++k)
			add(ans,f[i][k]);
		printf("%d\n",ans);
	}
}
int main()
{
	freopen("311E2.in","r",stdin);
	freopen("311E2.out","w",stdout);
	read();
	work();
	printf("%f\n",(double)clock()/CLOCKS_PER_SEC);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
