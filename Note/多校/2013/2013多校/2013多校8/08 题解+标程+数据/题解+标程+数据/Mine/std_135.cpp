#include <set>
#include <cmath>
#include <stack>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <assert.h>
#include <numeric>
#include <vector>
#include <ctime>
#include <queue>
#include <list>
#include <map>
#define pi acos(-1.0)
#define INF 0x3f3f3f3f
#define clr(x)  memset(x,0,sizeof(x));
#define clrto(x,siz,y)  for(int xx=0;xx<=siz;xx++)  x[xx]=y;
#define clrset(x,siz)  for(int xx=0;xx<=siz;xx++)  x[xx]=xx;
#define clr_1(x) memset(x,-1,sizeof(x));
#define clrmax(x) memset(x,0x3f,sizeof(x));
#define clrvec(x,siz) for(int xx=0;xx<=siz;xx++)  x[xx].clear();
#define fop2   freopen(".in","r",stdin); //freopen(".out","w",stdout);
#define fop   freopen("data.in","r",stdin);freopen("data.out","w",stdout);
#define fop3 freopen("in.txt","r",stdin);
#define myprogram By_135678942570
#define clrcpy(x,siz,y)  for(int xx=0;xx<siz;xx++)  x[xx]=y[xx];
#define pb push_back
using namespace std;
int mp[1011][1011]={0};
int dx[8]={0,0,-1,-1,-1,1,1,1};
int dy[8]={-1,1,-1,1,0,-1,1,0};
int Q[1000111];
int vis[1011][1011]={0};
int n,m,k;
pair<int,int> bfs(int x,int y)
{
	int front=0,rear=0;
	Q[++front]=x*m+y;
	vis[x][y]=1;
	int cnt1=0;
	int cnt2=0;
	while(rear<front)
	{
		cnt1++;
		int nx=Q[++rear]/m;
		int ny=Q[rear]%m;
		// printf("%d %d\n",nx,ny);
		for(int i=0;i<8;i++)
		{
			int nnx=nx+dx[i];
			int nny=ny+dy[i];
			if(nnx<0||nny<0||nnx>=n||nny>=m||vis[nnx][nny])
				continue;
			if(mp[nnx][nny]==1)
				vis[nnx][nny]=1,cnt2++;
			else if(mp[nnx][nny]==0)
				vis[nnx][nny]=1,Q[++front]=nnx*m+nny;
		}
	}
	return make_pair(cnt1,cnt2);
}
int main()
{
	int T,cas=0;
	fop;
	scanf("%d",&T);
	// T=0;
	while(T--)
	// while(scanf("%d%d%d",&n,&m,&k)>0)
	{
		scanf("%d%d%d",&n,&m,&k);
		clr(mp);
		clr(vis);
		int sum=k;
		while(k--)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			assert(x>=0&&x<n&&y>=0&&y<m);
			mp[x][y]=-1;
			for(int i=0;i<8;i++)
			{
				int nx=x+dx[i];
				int ny=y+dy[i];
				if(nx<0||ny<0||nx>=n||ny>=m)
					continue;
				if(mp[nx][ny]!=-1)
				mp[nx][ny]=1;
			}
		}
		int res=0;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(!vis[i][j]&&mp[i][j]==0)
				{
					pair<int,int> temp=bfs(i,j);
					sum+=temp.first+temp.second;
					// puts("fuck");
					// printf("%d %d\n",temp.first,temp.second);
					res^=((temp.second%2)?2:1);
				}
		// printf("%d\n",res);
		// for(int i=0;i<n;i++)
		// {
		// 	for(int j=0;j<m;j++)
		// 		printf("%d ",mp[i][j]==-1?2:mp[i][j]);
		// 	puts("");
		// }
		res^=(n*m-sum)%2;
		// printf("%d\n",sum);
		printf("Case #%d: ",++cas);
		puts(res?"Xiemao":"Fanglaoshi");
	}
	// printf("%d\n",T);
	if(scanf("%d%d%d",&n,&m,&k)>0)
		puts("FUCK");
}