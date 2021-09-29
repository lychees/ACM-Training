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
const int maxn=300003*2;
const int dx[]={-1,-1,-1,0,0,1,1,1};
const int dy[]={-1,0,1,-1,1,-1,0,1};
int n,m,num[3003][6003],M,T,fa[maxn],vis[maxn],ans=0,tot=0;
inline int getfa(int x){return x==fa[x]?x:fa[x]=getfa(fa[x]);}
inline int find(int x,int y)
{
	if(y<0)y=M-1;
	else if(y==M)y=0;
	return !num[x][y]?0:getfa(num[x][y]);
}

inline void mark(int x,int y)
{
	num[x][y]=++tot;
	for(int i=0,z;i<8;i++)
		if(z=find(x+dx[i],y+dy[i]))fa[z]=tot;
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get(),m=get();T=get();M=2*m;
	if(m==1)return puts("0"),0;
	for(int i=1;i<=T+T;i++)fa[i]=i;
	for(;T;T--)
	{
		int x=get(),y=get()-1,ok=1,z;
		for(int i=0;i<8;i++)
			if(z=find(x+dx[i],y+dy[i]))vis[z]=T;
		for(int i=0;i<8&&ok;i++)
			if(vis[find(x+dx[i],y+dy[i]+m)]==T)ok=0;
		if(!ok)continue;else ans++;
		mark(x,y),mark(x,y+m);
	}
	printf("%d\n",ans);
	return 0;
}
