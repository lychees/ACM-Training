#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=1630;
int n,m,a[maxn][maxn],id[maxn][maxn],N=0,res[maxn],b[maxn][maxn],tp[maxn][maxn],sum;
bool ray[maxn][maxn];
void f(int x,int y)
{
	if(!a[x][y]||id[x][y])return;
	id[x][y]=N;
	f(x+1,y),f(x,y+1),f(x-1,y),f(x,y-1);
}
void g(int x,int y)
{
	if(!a[x][y]||ray[x][y]||b[x][y])return;
	ray[x][y]=1;sum++;
	g(x+1,y),g(x,y+1),g(x-1,y),g(x,y-1);
}
inline void make(int f)
{
	for(int i=2;i<n;i++)
		for(int j=2;j<m;j++)
			if(b[i][j]==f||b[i+1][j]==f||b[i][j+1]==f||b[i-1][j]==f||b[i][j-1]==f)tp[i][j]=f;else tp[i][j]=f^1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)b[i][j]=tp[i][j];
}
int main()
{
	freopen("9.in","r",stdin);
	freopen("9.out","w",stdout);
	n=get()+5,m=get()+5;
	for(int i=6;i<=n;i++)
		for(int j=6;j<=m;j++)a[i][j]=get();
	n+=5,m+=5;
	for(int i=6;i<=n-5;i++)
		for(int j=6;j<=m-5;j++)
			if(a[i][j]&&!id[i][j])N++,f(i,j);
	memcpy(b,a,sizeof(a));
	for(int i=1;i<=3;i++)make(0);
	for(int i=1;i<=4;i++)make(1);
	for(int i=6;i<=n-5;i++)
		for(int j=6;j<=m-5;j++)
			if(a[i][j]&&!ray[i][j]&&!b[i][j])
			{
				sum=0,g(i,j);
				if(sum>2)res[id[i][j]]++;
			}
	sort(res+1,res+1+N);
	printf("%d\n",N);
	for(int i=1;i<=N;i++)printf("%d%c",res[i],i==n?'\n':' ');
	return 0;
}
