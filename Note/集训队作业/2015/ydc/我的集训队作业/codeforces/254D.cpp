#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 1010
using namespace std;
int nRow,nCol,D,nRat;
char map[maxn][maxn];
pair<int,int> rat[maxn*maxn];
int movex[]={1,0,0,-1};
int movey[]={0,1,-1,0};
void print(int a,int b,int c,int d)
{
	printf("%d %d %d %d\n",a,b,c,d);
	exit(0);
}
void read()
{
	scanf("%d %d %d",&nRow,&nCol,&D);
	for(int i=1;i<=nRow;++i)
	{
		scanf("%s",map[i]+1);
		for(int j=1;j<=nCol;++j)
			if(map[i][j]=='R')
				rat[++nRat]=make_pair(i,j);
	}
}
void work1(pair<int,int> a,pair<int,int> b)
{
	static pair<int,int> queue[maxn];
	static int use[maxn][maxn],id;
	static int dis[maxn][maxn];
	int front=0,rear=0,s=0;
	++id;
	queue[++rear]=a,use[a.first][a.second]=id,dis[a.first][a.second]=0;
	queue[++rear]=b,use[b.first][b.second]=id,dis[b.first][b.second]=0;
	while(front<rear)
	{
		pair<int,int> p=queue[++front];
		s+=map[p.first][p.second]=='R';
		if(dis[p.first][p.second]==D)
			continue;
		for(int i=0;i<4;++i)
		{
			pair<int,int> q=make_pair(p.first+movex[i],p.second+movey[i]);
			if(q.first>=1&&q.first<=nRow&&q.second>=1&&q.second<=nCol&&map[q.first][q.second]!='X'&&use[q.first][q.second]!=id)
			{
				queue[++rear]=q;
				use[q.first][q.second]=id;
				dis[q.first][q.second]=dis[p.first][p.second]+1;
			}
		}
	}
	if(s==nRat)
		print(a.first,a.second,b.first,b.second);
}
void BFS1(pair<int,int> p,pair<int,int> x)
{
	static pair<int,int> queue[maxn];
	static int use[maxn][maxn],id;
	static int dis[maxn][maxn];
	int front=0,rear=1;
	queue[rear]=p,use[p.first][p.second]=++id,dis[p.first][p.second]=0;
	while(front<rear)
	{
		pair<int,int> p=queue[++front];
		work1(x,p);
		if(dis[p.first][p.second]==D)
			continue;
		for(int i=0;i<4;++i)
		{
			pair<int,int> q=make_pair(p.first+movex[i],p.second+movey[i]);
			if(q.first>=1&&q.first<=nRow&&q.second>=1&&q.second<=nCol&&map[q.first][q.second]!='X'&&use[q.first][q.second]!=id)
			{
				queue[++rear]=q;
				use[q.first][q.second]=id;
				dis[q.first][q.second]=dis[p.first][p.second]+1;
			}
		}
	}
}
void work(pair<int,int> p)
{
	static pair<int,int> queue[maxn];
	static int use[maxn][maxn],id;
	static int dis[maxn][maxn];
	int front=0,rear=1;
	queue[rear]=p,use[p.first][p.second]=++id,dis[p.first][p.second]=0;
	while(front<rear)
	{
		pair<int,int> p=queue[++front];
		if(dis[p.first][p.second]==D)
			continue;
		for(int i=0;i<4;++i)
		{
			pair<int,int> q=make_pair(p.first+movex[i],p.second+movey[i]);
			if(q.first>=1&&q.first<=nRow&&q.second>=1&&q.second<=nCol&&map[q.first][q.second]!='X'&&use[q.first][q.second]!=id)
			{
				queue[++rear]=q;
				use[q.first][q.second]=id;
				dis[q.first][q.second]=dis[p.first][p.second]+1;
			}
		}
	}
	for(int i=1;i<=nRat;++i)
		if(use[rat[i].first][rat[i].second]!=id)
		{
			BFS1(rat[i],p);
			return ;
		}
	for(int i=1;i<=nRow;++i)
		for(int j=1;j<=nCol;++j)
			if(map[i][j]!='X'&&(i!=p.first||j!=p.second))
				print(i,j,p.first,p.second);
}
void BFS(pair<int,int> p)
{
	static bool use[maxn][maxn];
	static pair<int,int> queue[maxn*maxn];
	static int dis[maxn][maxn];
	int front=0,rear=1;
	queue[rear]=p;
	while(front<rear)
	{
		pair<int,int> p=queue[++front];
		work(p);
		if(dis[p.first][p.second]==D)
			continue;
		for(int i=0;i<4;++i)
		{
			pair<int,int> q=make_pair(p.first+movex[i],p.second+movey[i]);
			if(q.first>=1&&q.first<=nRow&&q.second>=1&&q.second<=nCol&&map[q.first][q.second]!='X'&&!use[q.first][q.second])
			{
				queue[++rear]=q;
				use[q.first][q.second]=true;
				dis[q.first][q.second]=dis[p.first][p.second]+1;
			}
		}
	}
	printf("-1\n");
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	BFS(rat[1]);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
