#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<iostream>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
int n,L,Q,m[55],p[55],c[55]; string opr,a[55][15]; char s[10005];
bool cmp(const int i,const int j){return c[i]==c[j]?i<j:c[i]>c[j];}
int main()
{
	puts("Query Pages"),n=1;
	while (cin>>opr,opr!="E"){
		gets(s),L=strlen(s); a[n][m[n]=1]="";
		rep(i,L-1) if (s[i]==' ') a[n][++m[n]]=""; else a[n][m[n]]+=s[i]<'a'?s[i]+32:s[i];
		if (opr=="Q"){
			printf("Q%d:",++Q);
			rep(i,n-1){
				c[i]=0,p[i]=i;
				rep(j,m[i]) rep(k,m[n]) if (a[i][j]==a[n][k]) c[i]+=(9-j)*(9-k);
				}
			sort(p+1,p+n,cmp);
			rep(i,5) if (c[p[i]]){printf("  "); break;}
			rep(i,5) if (c[p[i]]) printf(" P%d",p[i]); puts("");
		}else ++n;
	}
	return 0;
}
