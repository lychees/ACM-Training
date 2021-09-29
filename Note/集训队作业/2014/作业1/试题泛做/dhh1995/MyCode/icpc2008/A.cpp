#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;i++)
#define now b[a[1]][a[2]][a[3]]
int n[5],s[5],t[5],ans; bool b[22][22][22]; char D[5];
int read(){scanf("%s",D); return (D[1]=='z'?3:D[1]=='y'?2:1)*(*D=='+'?1:-1);}
bool same(int *a,int *b){for (int i=0;i<4;i++) if (a[i]!=b[i]) return 0; return 1;}
bool vaild(int *a){rep(i,3) if (a[i]<1 || a[i]>n[i]) return 0; return 1;}
void dfs(int *a,int c,int m)
{
	if (!vaild(a) || m>=ans) return; if (same(a,t)){if (!c) ans=m; return;}
	int d=*a,e=abs(d);
	if (c!=1){
		a[e]+=d>0?1:-1;
		if (!now) now=1,dfs(a,c>1?c-1:c?0:3,m+!c),now=0;
		a[e]-=d>0?1:-1;
		}
	if (c==1 || c==2) rep(i,3) if (i!=e){
		*a=i,a[i]++;
		if (!now) now=1,dfs(a,c==1?0:-1,m),now=0;
		*a=d,a[i]--;
		
		*a=-i,a[i]--;
		if (!now) now=1,dfs(a,c==1?0:-1,m),now=0;
		*a=d,a[i]++;
		}
}
int main()
{
	int Case=0;
	while (scanf("%d",n+1),n[1]){
		rep(i,3) if (i>1) scanf("%d",n+i);
		rep(i,3) scanf("%d",s+i); *s=read();
		rep(i,3) scanf("%d",t+i); *t=read();
		memset(b,0,sizeof(b)),ans=7,dfs(s,3,1);
		printf("Case %d: ",++Case);
		if (ans>6) puts("Impossible"); else printf("%d\n",ans);
		}
	return 0;
}
