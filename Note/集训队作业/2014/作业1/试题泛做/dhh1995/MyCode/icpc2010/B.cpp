#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=155,t[]={1,17,9,24,5,20,12,3,18,16,4};
int Case,n,a[N],c[N],p[N],b[32];
bool cmp(const int i,const int j){return a[i]<a[j];}
char chg(int x){return x>9?'-':x+48;}
bool work(int m)
{
	int m0=1<<20,m1=0,x;
	rep(i,n) x=a[p[i]]*(1+(i<m)),m0=min(m0,x),m1=max(m1,x);
	return m0*105>=m1*95;
}
bool trans(){rep(i,n) if (work(i)){rep(j,n) a[p[j]]=j>=i; return 1;} return 0;}
int solve()
{
	sort(p,p+n,cmp); if (n%6!=5 || n<24 || !trans()) return -1;
	if (a[1]) reverse(a,a+n); a[n]=0,n=n/6-3; int C=0,K=0;
	rep(i,n+4){
		int x=0; rep(j,5) x=x*2+a[i*6+j]; if (a[i*6+5]) return -1;
		if (i==0 || i==n+3){if (x!=6) return -1; continue;}
		x=c[i]=b[x]; if (x>10) return -1;
		if (i==n+1) if (x!=C%11) return 'C';
		if (i==n+2) if (x!=K%11) return 'K';
		C+=((n-i)%10+1)*x,K+=((n-i+1)%9+1)*x;
	}
	return 0;
}
int main()
{
	rep(i,32) b[i]=99; rep(i,11) b[t[i]]=i;
	while (scanf("%d",&n),n){
		rep(i,n) scanf("%d",a+i),p[i]=i; int ans=solve();
		printf("Case %d: ",++Case);
		if (ans<0) puts("bad code"); else if (ans>0) printf("bad %c\n",ans);
		else{rep(i,n) printf("%c",chg(c[i+1])); puts("");}
	}
	return 0;
}
