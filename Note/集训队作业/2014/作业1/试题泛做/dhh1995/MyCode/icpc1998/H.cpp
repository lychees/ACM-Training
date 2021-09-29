#include<cstdio>
typedef unsigned long long ll;
#define rep(i,n) for (int i=0;i<n;++i)
ll n,m,b,flag=1,C,L,Lim; char a[25][2005];
void prt(int h,ll n){if (h+1==m) ++m; if (n) prt(h,n/10),a[h][L++]=char(n%10+48);}
void dfs(ll n,int t,int h)
{
	if (!n) return;
	if (n<b){
		if (!t) prt(h,n); else if (n>1) prt(h,n),a[h][L++]='*';
		if (t) prt(h,b); if (t>1) dfs(t,0,h+1); return;
	}
	dfs(n/b,t+1,h); if (n%b) a[h][L++]='+'; dfs(n%b,t,h);
}
void out(int l,int r)
{
	for (int i=m-1;i>=0;--i){
		int flag=0;
		for (int j=r-1;j>=l;--j)
			if (a[i][j]!=' ') flag=1; else if (!flag) a[i][j]='?';
		if (flag && l) rep(j,C) putchar(' ');
		for (int j=l;j<r;++j) if (a[i][j]!='?') putchar(a[i][j]);
		puts("");
	}
}
int main()
{
	rep(i,20) rep(j,2000) a[i][j]=' ';
	while (scanf("%llu%llu",&n,&b) && (n || b)){
		if (flag) flag=0; else {rep(i,80) putchar('-'); puts("");}
		printf("%llu in complete base %llu:\n",n,b);
		C=L=sprintf(a[0],"%llu = ",n),Lim=80-L,m=1,dfs(n,0,0);
		int st=0,ed;
		rep(i,L+1){
			if (i-st>(st?Lim:80)) out(st,ed),st=ed;
			if (a[0][i]=='+') ed=i;
		}
		out(st,L); rep(i,m) rep(j,1000) a[i][j]=' ';
	}
}
