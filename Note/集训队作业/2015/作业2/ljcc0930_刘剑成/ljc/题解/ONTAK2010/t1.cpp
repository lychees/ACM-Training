#include<cstdio>
#include<algorithm>
#define LL long long
using namespace std;
const int d[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
const char ch[5]="||--";
int n,m,ans,ma,tot,cnt;
char s[75][75],a[75][75];
bool cc[300];
bool dfs(int x,int y,int fa,int cost)
{
	bool flag=0;
	if(cc[s[x][y]])
		++cnt,flag=1,
		ma=max(ma,cost);
	for(int i=0;i<4;++i)
		if(i!=fa)
		{
			int nx=x+d[i][0],ny=y+d[i][1],
				mx=nx+d[i][0],my=ny+d[i][1];
			if(mx>0&&mx<=n&&my>0&&my<=m)
				if(a[nx][ny]==ch[i]&&a[mx][my]==ch[i])
					if(dfs(mx,my,i^1,cost+1))
						ans+=2,flag=1;
		}
	return flag;
}
int main()
{
	cc['a']=cc['e']=cc['i']=cc['o']=cc['u']=cc['y']=1;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		scanf("%s",s[i]+1);
		for(int j=1;j<=m;++j)
			tot+=cc[s[i][j]];
	}
	for(int i=1;i<=n;++i)
		scanf("%s",a[i]+1);
	dfs(1,1,-1,0);
	if(cnt!=tot)
		puts("NIE");
	else
		printf("%d\n",ans-ma);
	return 0;
}
