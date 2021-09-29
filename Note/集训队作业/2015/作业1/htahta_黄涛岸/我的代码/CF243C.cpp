#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long LL;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=3033;
int px[maxn],py[maxn],n,x[maxn],y[maxn],Tx=0,Ty=0;
char a[maxn][maxn];
void init()
{
	n=get();
	for(int cx=0,cy=0,i=0;i<=n;i++)
	{
		for(int j=-1;j<2;j++)x[++Tx]=cx+j,y[++Ty]=cy+j;
		px[i]=cx,py[i]=cy;
		if(i==n)break;
		char ch;scanf(" %c",&ch);
		int l=get();
		if(ch=='R')cy+=l;
		if(ch=='L')cy-=l;
		if(ch=='U')cx-=l;
		if(ch=='D')cx+=l;
	}
	sort(x+1,x+1+Tx);Tx=unique(x+1,x+1+Tx)-x-1;
	sort(y+1,y+1+Ty);Ty=unique(y+1,y+1+Ty)-y-1;
	for(int i=0;i<=n;i++)
		px[i]=lower_bound(x+1,x+1+Tx,px[i])-x,
		py[i]=lower_bound(y+1,y+1+Ty,py[i])-y;
	for(int i=1;i<=n;i++)
	{
		int sx=px[i-1],tx=px[i],sy=py[i-1],ty=py[i];
		if(sx>tx)swap(sx,tx);
		if(sy>ty)swap(sy,ty);
		for(int j=sx;j<=tx;j++)
			for(int k=sy;k<=ty;k++)a[j][k]=2;
	}
}
void dfs(int x,int y)
{
	if(!(1<=x&&x<=Tx&&1<=y&&y<=Ty))return;
	if(a[x][y])return;else a[x][y]=1;
	dfs(x+1,y),dfs(x,y+1),dfs(x-1,y),dfs(x,y-1);
}
void work()
{
	dfs(1,1);
	LL ans=0;
	for(int i=2;i<=Tx;++i)
		for(int j=2;j<=Ty;++j)
			if(a[i][j]!=1)ans+=LL(x[i]-x[i-1])*(y[j]-y[j-1]);
	cout<<ans<<endl;
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	init();
	work();
	return 0;
}
