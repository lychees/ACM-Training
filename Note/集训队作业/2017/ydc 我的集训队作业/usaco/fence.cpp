#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 260
using namespace std;
struct Point
{
	int x,y;
	Point() {}
	Point(int x,int y): x(x),y(y) {}
	friend Point operator - (const Point &a,const Point &b)
	{
		return Point(a.x-b.x,a.y-b.y);
	}
	void Read()
	{
		cin>>x>>y;
	}
}p[maxn];
typedef Point Vector;
int dp[maxn][maxn],nv,n;
struct Node
{
	Vector v;
	int x,y;
	friend bool operator < (const Node &a,const Node &b)
	{
		return a.v.x*b.v.y-a.v.y*b.v.x<0;
	}
}vec[maxn*maxn];
void update(int &a,int b)
{
	if(a<b)
		a=b;
}
void read()
{
	cin>>n;
	for(int i=1;i<=n;++i)
		p[i].Read();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(i!=j)
			{
				++nv;
				vec[nv].v=p[i]-p[j],vec[nv].x=i,vec[nv].y=j;
			}
	sort(vec+1,vec+nv+1);
}
int Dp()
{
	static int g[maxn];
	int ans=0;
	for(int i=1;i<=n;++i)
	{
		memset(dp,0,sizeof(dp));
		fill(g+1,g+n+1,-1<<30);
		g[i]=0;
		for(int j=1;j<=nv;++j)
		{
			update(dp[vec[j].x][vec[j].y],g[vec[j].x]+1);
			if(vec[j].y!=i)
				update(g[vec[j].y],g[vec[j].x]+1);
		}
		for(int j=1;j<=n;++j)
			update(ans,dp[j][i]);
	}
	return ans;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	printf("%d\n",Dp());
	fclose(stdin);
	fclose(stdout);
	return 0;
}
