#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int x,lim,r,y,m,s,n,t,M,S,N,T,a[8],v[8],f[10005];
bool big(){return m>5?1:v[m]*s+v[n]*(t-s)>x;}
void upd()
{
	if ((f[m]*s+f[n]*(t-s))%x==0 && big())
		if (!M || (s==S?n>N && t<S:s<S)) M=m-n,S=s,N=n,T=t;
}
int main()
{
	while (scanf("%d",&x),x){
		f[1]=1%x,v[1]=1,r=x%10,M=0;
		for (m=2;;++m){
			f[m]=(f[m-1]*10+1)%x; if (m<7) v[m]=v[m-1]*10+1;
			if (x%10==0 && m>12) lim=12; else lim=m;
			for (n=1;n<lim;++n) for (s=1;s<=9;++s)
				if (!r) t=0,upd();
				else if (r==5){t=0,upd(); if (s!=5) t=5,upd();}
				else if (r&1){for (t=0;t<=9;++t) if (s!=t) upd();}
				else for (t=0;t<=9;t+=2) if (s!=t) upd();
			if (M) break;
		}
		printf("%d: %d %d %d %d\n",x,M,S,N,T);
	}
	return 0;
}
