#include <iostream>
#include <cstdio>
using namespace std;
const int maxn=100033;
bool f[4][maxn];
int n,m,dx,dy,x,y,cnt=0;
long long ans=1;
char s[5];
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	scanf("%d%d%d%d%s",&n,&m,&x,&y,s);
	dx=s[0]=='D'?1:-1;dy=s[1]=='R'?1:-1;
	for(int i=1,a,b;i<=2*(n+m-2);i++)
	{
		if(x==1)a=0,b=y;
		else if(x==n)a=1,b=y;
		else if(y==1)a=2,b=x;
		else a=3,b=x;
		if(!f[a][b])f[a][b]=1,cnt++;
		if(x==1)dx=1;
		if(x==n)dx=-1;
		if(y==1)dy=1;
		else if(y==m)dy=-1;
		if(cnt==n+m-2)return printf("%I64d\n",ans),0;
		int v=min(dx>0?n-x:x-1,dy>0?m-y:y-1);
		ans+=v,x+=v*dx,y+=v*dy;
	}
	return puts("-1"),0;
}
