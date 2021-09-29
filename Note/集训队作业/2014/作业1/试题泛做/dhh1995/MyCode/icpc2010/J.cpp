#include<cstdio>
#include<cstring>
int s[100005],c[25],n,m,p,G,Case=0;
char f[105][33000];
inline int abs(int a){return a>0?a:-a;}
bool check(int n,int x)
{
	if (abs(f[n][x])==Case) return f[n][x]>0;
	f[n][x]=Case; if (x-(x&-x)==0) return 1;
	int m=s[x]/n,len=0,y,a[25];
	for (int i=0;i<p;i++) if (x&1<<i) a[len++]=1<<i;
	for (int i=1;i+1<1<<len;i++){
		y=0; for (int j=0;j<len;j++) if (i&1<<j) y|=a[j]; if (y>(x^y)) continue;
		if (s[y]%n==0 && check(n,y) && check(n,x^y)) return 1;
		if (s[y]%m==0 && check(m,y) && check(m,x^y)) return 1;
		}
	f[n][x]=-Case; return 0;
}
int main()
{
	while (scanf("%d",&p),p){
		scanf("%d%d",&n,&m); G=1<<p;
		for (int i=0;i<p;i++) scanf("%d",&c[i]);
		printf("Case %d: ",++Case);
		for (int i=0;i<G;i++){
			s[i]=0; for (int j=0;j<p;j++) if (i&1<<j) s[i]+=c[j];
			}
		if (n*m==s[G-1] && check(n,G-1)) printf("Yes\n");
		else printf("No\n");
		}
	return 0;
}
