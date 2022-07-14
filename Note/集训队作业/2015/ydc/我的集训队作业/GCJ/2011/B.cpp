#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxc 25
#define maxn maxc*maxc
#define maxm maxn*6
#define INF 1000000000000000LL
using namespace std;
typedef long long LL;
int nRow,nCol,N,S;
LL map[maxc][maxc],M;
int nEdge,to[maxm],next[maxm],start[maxn];
LL len[maxm];
int movex[]={1,0,0,-1};
int movey[]={0,1,-1,0};
void make(int a,int b,LL c)
{
	++nEdge,to[nEdge]=b,next[nEdge]=start[a],start[a]=nEdge,len[nEdge]=c;
}
int ID(int i,int j)
{
	return (i-1)*nCol+j;
}
void read()
{
	scanf("%d %d %I64d",&nRow,&nCol,&M);
	for(int i=1;i<=nRow;++i)
		for(int j=1;j<=nCol;++j)
			scanf("%I64d",&map[i][j]);
	for(int i=1;i<=nRow;++i)
		map[i][0]=map[i][nCol+1]=-INF;
	for(int i=1;i<=nCol;++i)
		map[0][i]=map[nRow+1][i]=-INF;
}
bool check()
{
	for(int i=1;i<=nRow;++i)
		for(int j=1;j<=nCol;++j)
			if(map[i][j]>0)
				return false;
	return true;
}
LL work()
{
	static LL ori[maxc][maxc];
	static bool ok[maxc][maxc];
	LL day=0;
	if(check())
		return 0;
	while(++day)
	{
		memset(start,0,sizeof(start));
		nEdge=1,N=nRow*nCol,S=++N;
		for(int i=1;i<=nRow;++i)
			for(int j=1;j<=nCol;++j)
				if(map[i][j]>=0)
				{
					ori[i][j]=map[i][j];
					for(int k=0;k<4;++k)
					{
						int px=i+movex[k],py=j+movey[k];
						if(map[px][py]>=0)
							make(ID(px,py),ID(i,j),map[i][j]);
						else
							make(S,ID(i,j),map[i][j]);
					}
				}
		static int queue[maxn];
		static bool use[maxn];
		static LL dis[maxn];
		fill(dis+1,dis+N+1,INF);
		int front=0,rear=1;
		queue[rear]=S,dis[S]=0;
		while(front!=rear)
		{
			int p=queue[front=front%N+1];
			use[p]=false;
			for(int i=start[p];i;i=next[i])
				if(dis[to[i]]>max(dis[p],len[i]))
				{
					dis[to[i]]=max(dis[p],len[i]);
					if(!use[to[i]])
						use[queue[rear=rear%N+1]=to[i]]=true;
				}
		}
		for(int i=1;i<=nRow;++i)
			for(int j=1;j<=nCol;++j)
				if(map[i][j]>=0)
				{
					map[i][j]=dis[ID(i,j)];
					if(!map[i][j])
						map[i][j]=-INF;
				}
		LL minv1=M,minv2=INF;
		for(int i=1;i<=nRow;++i)
			for(int j=1;j<=nCol;++j)
			{
				LL h=0;
				for(int k=0;k<4;++k)
					h=max(h,map[i][j]-map[i+movex[k]][j+movey[k]]);
				ok[i][j]=map[i][j]==ori[i][j];
				if(map[i][j]==ori[i][j]&&ori[i][j]>0)
					minv1=min(minv1,h),minv2=min(minv2,max(0LL,ori[i][j]/M-1));
				else if(ori[i][j]>0)
					minv1=min(minv1,map[i][j]-ori[i][j]),minv2=min(minv2,max(0LL,(map[i][j]-ori[i][j])/M-1));
				ori[i][j]=max(ori[i][j]-min(h,M),-INF);
			}
		if(minv1==M&&minv2)
		{
			for(int i=1;i<=nRow;++i)
				for(int j=1;j<=nCol;++j)
					if(ok[i][j])
						ori[i][j]-=M*minv2;
			day+=minv2;
		}
		for(int i=1;i<=nRow;++i)
			for(int j=1;j<=nCol;++j)
				map[i][j]=ori[i][j];
		if(check())
			break;
	}
	return day;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int T;
	scanf("%d",&T);
	for(int i=1;i<=T;++i)
	{
		read();
		printf("Case #%d: %I64d\n",i,work());
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
