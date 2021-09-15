#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cctype>
#define maxn 2010
using namespace std;
typedef long long LL;
int n,m;
LL val[maxn][maxn];
bool mark[maxn][maxn];
int movex[]={1,0,0,-1};
int movey[]={0,1,-1,0};
void read()
{
	static LL px[maxn],py[maxn],vx[maxn],vy[maxn];
	int k,nowx=0,nowy=0;
	scanf("%d",&k);
	for(int i=2,d;i<=k+1;++i)
	{
		char c;
		for(c=getchar();!isalpha(c);c=getchar());
		scanf("%d",&d);
		if(c=='R')
			nowx+=d;
		if(c=='L')
			nowx-=d;
		if(c=='U')
			nowy+=d;
		if(c=='D')
			nowy-=d;
		px[i]=nowx,py[i]=nowy;
		vx[i]=nowx,vy[i]=nowy;
	}
	sort(px+1,px+k+2),sort(py+1,py+k+2);
	n=unique(px+1,px+k+2)-px-1,m=unique(py+1,py+k+2)-py-1;
	for(int i=1;i<=k+1;++i)
	{
		vx[i]=(lower_bound(px+1,px+n+1,vx[i])-px)*2-1;
		vy[i]=(lower_bound(py+1,py+m+1,vy[i])-py)*2-1;
		mark[vx[i]][vy[i]]=true;
		if(i==1)
			continue;
		LL lx=vx[i-1],ly=vy[i-1];
		if(vx[i]==lx)
			for(int k=min(ly,vy[i]);k<=max(ly,vy[i]);++k)
				mark[vx[i]][k]=true;
		else
			for(int k=min(lx,vx[i]);k<=max(lx,vx[i]);++k)
				mark[k][vy[i]]=true;
	}
	n=n*2-1,m=m*2-1;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		{
			int vi=i&1,vj=j&1;
			if(vi&&vj)
				val[i][j]=1;
			if(vi&&!vj)
				val[i][j]=py[(j+3)>>1]-py[(j+1)>>1]-1;
			if(!vi&&vj)
				val[i][j]=px[(i+3)>>1]-px[(i+1)>>1]-1;
			if(!vi&&!vj)
				val[i][j]=(px[(i+3)>>1]-px[(i+1)>>1]-1)*(py[(j+3)>>1]-py[(j+1)>>1]-1);
		}
}
LL BFS(int x,int y)
{
	static pair<int,int> queue[maxn*maxn];
	static bool use[maxn][maxn];
	LL ans=0;
	int front=0,rear=1;
	queue[rear]=make_pair(x,y),use[x][y]=true;
	for(int i=0;i<=m;++i)
		val[0][i]=val[n+1][i]=1;
	for(int i=0;i<=n;++i)
		val[i][0]=val[i][m+1]=1;
	while(front<rear)
	{
		pair<int,int> p=queue[++front];
		for(int i=0;i<4;++i)
		{
			pair<int,int> q=make_pair(p.first+movex[i],p.second+movey[i]);
			if(q.first>=0&&q.first<=n+1&&q.second>=0&&q.second<=m+1&&!use[q.first][q.second]&&!mark[q.first][q.second])
			{
				if(!val[q.first][q.second]&&p.first%2==0&&p.second%2==0)
					continue;
				queue[++rear]=q;
				use[q.first][q.second]=true;
			}
		}
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(!use[i][j]&&val[i][j])
				ans+=val[i][j];
	return ans;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	cout<<BFS(0,0)<<endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
