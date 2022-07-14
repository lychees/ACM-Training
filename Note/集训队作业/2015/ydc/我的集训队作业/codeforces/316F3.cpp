#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 1800
using namespace std;
bool use[maxn][maxn];
int nRow,nCol,map[maxn][maxn];
int movex[]={1,0,0,-1};
int movey[]={0,1,-1,0};
void Read(int &digit)
{
	digit=0;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
}
void read()
{
	Read(nRow),Read(nCol);
	for(int i=1;i<=nRow;++i)
		for(int j=1;j<=nCol;++j)
			Read(map[i][j]);
}
bool check(int x1,int y1,int x2,int y2)
{
	if(x1==x2&&y1==y2)
		return true;
	if(x1<x2&&map[x1+1][y1])
		return check(x1+1,y1,x2,y2);
	if(x1>x2&&map[x1-1][y1])
		return check(x1-1,y1,x2,y2);
	if(y1<y2&&map[x1][y1+1])
		return check(x1,y1+1,x2,y2);
	if(y1>y2&&map[x1][y1-1])
		return check(x1,y1-1,x2,y2);
	return false;
}
int BFS(int x,int y)
{
	static int px[maxn*maxn],py[maxn*maxn],mayx[maxn*maxn],mayy[maxn*maxn];
	int front=0,rear=1,tot=0;
	px[rear]=x,py[rear]=y,use[x][y]=true;
	while(front<rear)
	{
		++front;
		x=px[front],y=py[front];
		int c=0;
		for(int i=-5;i<=5;++i)
			if(x+i>=1&&x+i<=nRow)
				for(int j=-5;j<=5;++j)
					if(y+j>=1&&y+j<=nCol)
						c+=map[i+x][j+y];
		if(c<=45)
			++tot,mayx[tot]=x,mayy[tot]=y;
		for(int i=0;i<4;++i)
		{
			int qx=x+movex[i],qy=y+movey[i];
			if(map[qx][qy]&&!use[qx][qy])
			{
				use[qx][qy]=true;
				++rear,px[rear]=qx,py[rear]=qy;
			}
		}
	}
	static int can[maxn*maxn],id;
	++id;
	for(int i=1;i<=tot;++i)
		for(int j=1;j<=tot;++j)
			if(mayx[i]<mayx[j]||(mayx[i]==mayx[j]&&mayy[i]<mayy[j]))
				if(abs(mayx[i]-mayx[j])+abs(mayy[i]-mayy[j])<=30&&check(mayx[i],mayy[i],mayx[j],mayy[j]))
					can[j]=id;
	int ans=0;
	for(int i=1;i<=tot;++i)
		if(can[i]!=id)
			++ans;
	return ans;
}
void work()
{
	static int out[100000];
	int nC=0;
	for(int i=1;i<=nRow;++i)
		for(int j=1;j<=nCol;++j)
			if(map[i][j]&&!use[i][j])
				out[++nC]=BFS(i,j);
	sort(out+1,out+nC+1);
	printf("%d\n",nC);
	for(int i=1;i<=nC;++i)
		printf("%d%c",out[i],i<nC?' ':'\n');
}
int main()
{
	freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	read();
	work();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
