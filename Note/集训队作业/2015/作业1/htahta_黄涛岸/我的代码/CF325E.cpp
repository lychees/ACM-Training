#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int maxn=100003;
int fa[maxn],p[maxn],n;
bool vis[maxn];
int getfa(int x){return fa[x]==x?x:fa[x]=getfa(fa[x]);}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	cin>>n;
	if(n&1)return puts("-1"),0;
	for(int i=0,x;i<n;vis[p[i++]]=1)
		if(!vis[x=i*2%n])p[i]=x;else p[i]=(x+1)%n;
	for(int i=0;i<n;i++)fa[i]=i,vis[i]=0;
	for(int i=0;i<n;i++)
		for(int x=i;!vis[x];x=p[x])vis[x]=1,fa[getfa(x)]=getfa(i);
	for(int i=0,t;i<n/2;i++)
	{
		int x=(i+n/2)%n,fx=getfa(i),fy=getfa(x);
		if(fx!=fy)t=p[x],p[x]=p[i],p[i]=t,fa[fx]=fy;
	}
	putchar('0');
	for(int i=p[0];i;i=p[i])printf(" %d",i);
	puts(" 0");
	return 0;
}
