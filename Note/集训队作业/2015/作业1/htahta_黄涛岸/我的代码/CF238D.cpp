#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#define pb push_back
using namespace std;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=100003;
int d[maxn][2],n,m,vis[maxn],sum[10],f[maxn*10][10],timestamp=0,p[maxn];
char s[maxn];
vector<int> g[maxn];
inline void add(int x)
{
	g[x].pb(++timestamp);
	for(int i=0;i<=9;i++)f[timestamp][i]=sum[i];
}
inline void del(int x)
{
	d[d[x][0]][1]=d[x][1],d[d[x][1]][0]=d[x][0];
}
void run()
{
	for(int cur,pre,dir,i=1;i<=n;i++)
	{
		if(vis[i])continue;
		cur=i;pre=0;dir=1;
		while(i<=cur&&cur<=n)
		{
			if(!isdigit(s[cur]))
			{
				dir=(s[cur]=='<'?0:1);
				if(pre)del(pre);
				pre=cur;
			}else
			{
				sum[s[cur]-'0']++,s[cur]--,pre=0;
				if(!isdigit(s[cur]))del(cur);
			}
			if(!vis[cur])p[cur]=d[cur][0],vis[cur]=1;
			add(cur);cur=d[cur][dir];
		}
		add(cur);
	}
}
inline int ask(int x,int v)
{
	int p=lower_bound(g[x].begin(),g[x].end(),v)-g[x].begin();
	return p==g[x].size()?1e9:g[x][p];
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	scanf("%d%d\n",&n,&m);
	for(int i=1;i<=n;i++)s[i]=getchar(),d[i][0]=i-1,d[i][1]=i+1;
	run();
	while(m--)
	{
		int x=get(),y=get();
		int t1=g[x][0],t2=min(ask(p[x],t1),ask(y+1,t1))-1;
		for(int i=0;i<=9;i++)printf("%d%c",f[t2][i]-f[t1-1][i],i<9?' ':'\n');
	}
	return 0;
}
