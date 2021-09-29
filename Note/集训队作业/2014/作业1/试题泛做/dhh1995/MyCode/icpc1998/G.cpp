#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
#define tree int l,int r,int d,int u
#define M int x=l+r>>1,y=d+u>>1
#define NW l,x,d,y
#define NE l,x,y,u
#define SW x,r,d,y
#define SE x,r,y,u
int Case,n,m,t,a[10005]; char s[66][66];
void dfs(int t,tree)
{
	if (l+1==r){s[l][d]='*'; return;} M,z=t%5; t/=5;
	if (!z || z==1) dfs(t,NW);
	if (!z || z==2) dfs(t,NE);
	if (!z || z==3) dfs(t,SW);
	if (!z || z==4) dfs(t,SE);
}
int get(int t,int v,tree)
{
	if (l+1==r){if (s[l][d]=='1') return a[m++]=t,1; return 0;}
	M,c=get(t+v,v*5,NW)+get(t+v*2,v*5,NE)+get(t+v*3,v*5,SW)+get(t+v*4,v*5,SE);
	if (c==(r-l)*(u-d)) m-=4,a[m++]=t; return c;
}
int main()
{
	while (scanf("%d",&n),n){
		if (Case) puts(""); printf("Image %d\n",++Case);
		if (n<0){
			n=-n; rep(i,n) rep(j,n) s[i][j]='.';
			while (scanf("%d",&t),t>=0) dfs(t,0,n,0,n);
			rep(i,n){s[i][n]='\0'; puts(s[i]);}
		}else{
			rep(i,n) scanf("%s",s[i]); m=0,get(0,1,0,n,0,n),sort(a,a+m);
			rep(i,m) printf("%d%s",a[i],i+1<m && i%12<11?" ":"\n");
			printf("Total number of black nodes = %d\n",m);
		}
	}
	return 0;
}
