#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int Case,n,m,x,h,t,ans,f[55],a[1<<21]; char s[25]; bool c[1<<21][2];
void dfs(int i,int x)
{
	if (x<=0) return; if (i>t){++ans; return;} int fa=a[f[i]>>1];
	for (int j=x;j+j>=fa;--j) a[f[i]]=j,a[f[i+1]]=fa-j,dfs(i+2,fa-j);
}
int main()
{
	while (scanf("%d",&n),n){
		rep(i,n){
			scanf("%s",s),m=strlen(s),x=1;
			rep(j,m) c[x][s[j]-48]=1,x=x*2+s[j]-48;
		}
		h=ans=0,f[t=1]=1;
		while (h<t){
			int x=f[++h];
			if (c[x][1]) f[++t]=x*2+1;
			if (c[x][0]) f[++t]=x*2;
			}
		a[1]=100,dfs(2,100); printf("Case %d: %d\n",++Case,ans);
		while (h) c[f[h]][0]=c[f[h]][1]=0,--h;
	}
	return 0;
}
