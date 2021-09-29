#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#define x first
#define y second
#define pb push_back
#define mp make_pair
using namespace std;
typedef pair<int,int> pii;
const int maxn=1003,maxr=300;
const int dx[]={0,0,1,-1},dy[]={1,-1,0,0};
char a[maxn][maxn];
int vis[maxn][maxn],dis[maxn][maxn],mark[maxr],mark2[maxr];
int n,m,d,id[maxn][maxn],N=0,T=1;
vector<pii> S,A,B,C,rat;
pii st,s[maxr];
void bfs(pii st,vector<pii> &A)
{
	int front=0,rear=1;
	s[front]=st;A.clear();
	vis[st.x][st.y]=++T;dis[st.x][st.y]=0;
	while(front!=rear)
	{
		int x=s[front].x,y=s[front].y;
		A.pb(s[front]);front++;
		if(dis[x][y]>=d)continue;
		for(int i=0;i<4;i++)
		{
			int xx=x+dx[i],yy=y+dy[i];
			if(1<=xx&&xx<=n&&1<=yy&&yy<=m&&vis[xx][yy]!=T&&a[xx][yy]!='X')
				vis[xx][yy]=T,dis[xx][yy]=dis[x][y]+1,s[rear++]=mp(xx,yy);
		}
	}
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	scanf("%d%d%d",&n,&m,&d);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",a[i]+1);
		for(int j=1;j<=m;j++)
			if(a[i][j]=='R')
			{
				id[i][j]=++N;rat.pb(mp(i,j));
				if(N==1)st=mp(i,j);
			}
	}
	bfs(st,A);
	for(int i=0,T=1,T2;i<A.size();i++)
	{
		bfs(A[i],B);
		++T;
		for(int j=0;j<B.size();j++)mark[id[B[j].x][B[j].y]]=T;
		st=mp(0,0);
		for(int j=1;j<=N;j++)
			if(mark[j]!=T){st=rat[j-1];break;}
		if(!st.x)
		{
			for(int j=1;j<=n;j++)
				for(int k=1;k<=m;k++)
					if(a[j][k]!='X'&&!(j==A[i].x&&k==A[i].y))
						return printf("%d %d %d %d\n",A[i].x,A[i].y,j,k),0;
		}
		bfs(st,B);T2=T;
		for(int j=0;j<B.size();j++)
		{
			bfs(B[j],C);++T;
			for(int k=0;k<C.size();k++)mark2[id[C[k].x][C[k].y]]=T;
			bool ok=1;
			for(int k=1;k<=N&&ok;k++)ok&=(mark[k]==T2||mark2[k]==T);
			if(!ok)continue;
			return printf("%d %d %d %d\n",A[i].x,A[i].y,B[j].x,B[j].y),0;
		}
	}
	puts("-1");
	return 0;
}
