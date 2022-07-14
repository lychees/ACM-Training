#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxm 18000010
#define maxn 3010 
using namespace std;
void Read(int &digit)
{
	digit=0;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
}
int father[maxm],nRow,nCol;
bool col[maxn][maxn*2];
int movex[]={1,1,1,0,0,-1,-1,-1};
int movey[]={-1,0,1,1,-1,-1,0,1};
int Find(int p)
{
	if(father[p]!=p)
		father[p]=Find(father[p]);
	return father[p];
}
void read()
{
	Read(nRow),Read(nCol);
	nCol*=2;
	for(int i=1;i<=nRow*nCol;++i)
		father[i]=i;
}
bool check(int x1,int y1,int x2,int y2)
{
	static int use[maxm],id;
	++id;
	col[x1][y1]=col[x2][y2]=1;
	int pa=Find((x1-1)*nCol+y1),pb=Find((x2-1)*nCol+y2);
	use[pa]=id;
	for(int j=0,x,y;j<8;++j)
	{
		x=x1+movex[j],y=y1+movey[j];
		if(y==0)
			y=nCol;
		if(y==nCol+1)
			y=1;
		if(x>=1&&x<=nRow&&y>=1&&y<=nCol&&col[x][y])
		{
			int p=Find((x-1)*nCol+y);
			use[p]=id;
		}
	}
	if(use[pb]==id)
	{
		col[x1][y1]=col[x2][y2]=false;
		return false;
	}
	for(int j=0,x,y;j<8;++j)
	{
		x=x2+movex[j],y=y2+movey[j];
		if(y==0)
			y=nCol;
		if(y==nCol+1)
			y=1;
		if(x>=1&&x<=nRow&&y>=1&&y<=nCol&&col[x][y])
		{
			int p=Find((x-1)*nCol+y);
			if(use[p]==id)
			{
				col[x1][y1]=col[x2][y2]=false;
				return false;
			}
		}
	}
	return true;
}
void work(int a,int b)
{
	int pa=Find((a-1)*nCol+b);
	for(int j=0;j<8;++j)
	{
		int x=a+movex[j],y=b+movey[j];
		if(x<1||x>nRow)
			continue;
		if(y==0)
			y=nCol;
		if(y==nCol+1)
			y=1;
		if(x>=1&&x<=nRow&&y>=1&&y<=nCol&&col[x][y])
			father[Find((x-1)*nCol+y)]=pa;
	}
}
void Query()
{
	int cnt=0,m;
	Read(m);
	for(int i=1,a,b;i<=m;++i)
	{
		Read(a),Read(b);
		if(check(a,b,a,b+nCol/2))
			++cnt,work(a,b),work(a,b+nCol/2);
	}
	printf("%d\n",cnt);
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	Query();
	return 0;
}
