#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;i++)
int n,a[5]; char s[55]; bool b[55][55];
int get(char x,char y){return x=='0'?52:(x-65)*2+(y=='+');}
int main()
{
	freopen("assembly.in","r",stdin);
	freopen("assembly.out","w",stdout);
	while (scanf("%d",&n)!=EOF){
		rep(i,54) rep(j,54) b[i][j]=0;
		rep(i,n){
			scanf("%s",s); rep(i,4) a[i]=get(s[i*2],s[i*2+1]);
			rep(i,4) rep(j,4) if (i!=j) b[a[i]][a[j]^1]=1;
			}
		rep(k,52) rep(i,52) rep(j,52) b[i][j]|=b[i][k]&&b[k][j];
		int ans=0; rep(i,52) ans|=b[i][i];
		puts(ans?"unbounded":"bounded");
		}
	return 0;
}
