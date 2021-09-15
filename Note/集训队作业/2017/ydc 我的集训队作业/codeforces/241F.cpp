#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cctype>
#include<vector>
#define maxn 110
#define each(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
using namespace std;
char map[maxn][maxn];
int nRow,nCol,Time;
int movex[]={1,0,0,-1};
int movey[]={0,1,-1,0};
int cost[maxn][maxn];
char s[1010];
int x[maxn],y[maxn],nowx,nowy;
void read()
{
	scanf("%d %d %d",&nRow,&nCol,&Time);
	for(int i=1;i<=nRow;++i)
	{
		scanf("%s",map[i]+1);
		for(int j=1;j<=nCol;++j)
		{
			if(isalpha(map[i][j]))
				cost[i][j]=1;
			else if(isdigit(map[i][j]))
				cost[i][j]=map[i][j]-'0';
		}
	}

	int sx,sy,ex,ey;
	scanf("%d %d %s %d %d",&sx,&sy,s+1,&ex,&ey);
	map[sx][sy]=isalpha(map[sx][sy])?map[sx][sy]:'a'+27;
	map[ex][ey]=isalpha(map[ex][ey])?map[ex][ey]:'a'+28;
	nowx=sx,nowy=sy;
	s[0]=map[sx][sy],s[strlen(s)]=map[ex][ey];
	for(int i=1;i<=nRow;++i)
		for(int j=1;j<=nCol;++j)
			if(map[i][j]-'a'<=28&&map[i][j]>='a')
				x[map[i][j]-'a']=i,y[map[i][j]-'a']=j;
}
void Print()
{
	printf("%d %d\n",nowx,nowy);
	exit(0);
}
void work()
{
	for(int i=1;s[i];++i)
	{
		int a=s[i-1]-'a',b=s[i]-'a',dir;
		if(x[a]==x[b])
			dir=y[a]<y[b]?1:2;
		else
			dir=x[a]<x[b]?0:3;
		while(nowx!=x[b]||nowy!=y[b])
		{
			if(Time<cost[nowx][nowy])
				Print();
			Time-=cost[nowx][nowy],nowx+=movex[dir],nowy+=movey[dir];
		}
	}
	Print();
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	work();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
