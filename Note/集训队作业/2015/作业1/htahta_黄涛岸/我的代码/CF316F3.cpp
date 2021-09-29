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
int s[maxn][maxn],n,m,a[maxn][maxn],id[maxn][maxn],N=0,res[maxn];
bool ray[maxn][maxn];
inline int calc(int x,int y){return s[x+3][y+3]-s[x-4][y+3]-s[x+3][y-4]+s[x-4][y-4];}
void f(int x,int y)
{
	if(!a[x][y]||id[x][y])return;
	id[x][y]=N;
	f(x+1,y),f(x,y+1),f(x-1,y),f(x,y-1);
}
void g(int x,int y)
{
	if(!a[x][y]||ray[x][y]||calc(x,y)>15)return;
	ray[x][y]=1;
	g(x+1,y),g(x,y+1),g(x-1,y),g(x,y-1);
}
int main()
{
	freopen("01.in.txt","r",stdin);
	freopen("01.out","w",stdout);
	n=get()+5,m=get()+5;
	for(int i=6;i<=n;i++)
		for(int j=6;j<=m;j++)a[i][j]=get();
	n+=5,m+=5;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];
	for(int i=6;i<=n-5;i++)
		for(int j=6;j<=m-5;j++)
			if(a[i][j]&&!id[i][j])N++,f(i,j);
	for(int i=6;i<=n-5;i++)
		for(int j=6;j<=m-5;j++)
			if(calc(i,j)<=15&&a[i][j]&&!ray[i][j])res[id[i][j]]++,g(i,j);
	sort(res+1,res+1+N);
	printf("%d\n",N);
	for(int i=1;i<=N;i++)printf("%d%c",res[i],i==n?'\n':' ');
	return 0;
}
