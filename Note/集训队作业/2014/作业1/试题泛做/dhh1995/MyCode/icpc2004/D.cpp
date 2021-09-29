#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int Case,n,m,cnt,Debug,a[45][45][25],c[35],d[35]; bool b[45]; char s[45],t[25],res[25],ans[25];
bool check(int n,int i,int u){rep(j,m) if (t[(a[n][i][j]+u)%n]!=res[j]) return 0; return 1;}
bool same(char *a,char *b){rep(i,m) if (a[i]!=b[i]) return 0; return 1;}
int work()
{
	int cnt=0;
	rep(i,n) rep(u,n){
		rep(j,n) b[j]=1; int L=0,x; rep(j,26) d[j]=0;
		rep(j,m) x=(a[n][i][j]+u)%n,b[x]=0,res[j]=s[x],++d[s[x]-65];
		rep(j,26) if (d[j]*2>c[j]) continue; if (cnt && same(res,ans)) continue;
		rep(j,n) if (b[j]) t[L++]=s[j];
		rep(v,L) if (*res==t[v]) for (int j=i+1;j<n;++j) if (check(L,j,v)){
			if (cnt++) return 2; else rep(j,m) ans[j]=res[j]; goto end;
		}
		end:;
	}
	return cnt;
}
int main()
{
	for (n=1;n<=40;++n){
		rep(i,40){
			rep(j,n) b[j]=1; int x=0,y;
			rep(j,20) if (j<n){
				a[n][i][j]=x,b[x]=0,y=i+1;
				if (j+1<n) while (y){if (++x==n) x=0; y-=b[x];}
			}
		}
	}
	while (scanf("%s",s),(n=strlen(s))>1){
		rep(i,26) c[i]=0; rep(i,n) ++c[s[i]-65];
		for (m=n/2;m;--m) if (cnt=work()) break;
		printf("Code %d: ",++Case);
		if (cnt>1) puts("Codeword not unique"); else ans[m]='\0',puts(ans);
	}
	return 0;
}
