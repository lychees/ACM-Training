#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int s[405],h[15],a[405],p[405],Case,L,n,m,t,last,flag;
bool R(int y){return y%4==0 && (y%100!=0 || y%400==0);}
int chg(int t)
{
	int y=t/10000,m=t/100%100,d=t%100;
	return s[y-1700]+h[m]+(m>2&&R(y))+d;
}
void prt(int t,bool flag)
{
	int y=t/365,m,d; if (s[y]>=t) --y; t-=s[y],y+=1700;
	m=t/30+1; if (h[m]+(m>2&&R(y))>=t) --m; d=t-h[m]-(m>2&&R(y));
	printf("%d/%d/%d%s",m,d,y,flag?" to ":"\n");
}
void Prt(int s,int t){if (s==t) return; printf("    "),flag=0,--t; if (s!=t) prt(s,1); prt(t,0);}
bool cmp(const int i,const int j){return a[i]==a[j]?(i&1)<(j&1):a[i]<a[j];}
int main()
{
	rep(i,401) s[i+1]=s[i]+365+R(i+1700);
	rep(i,13) if (i) h[i+1]=h[i]+(i==2?28:i==4||i==6||i==9||i==11?30:31);
	while (L=0,scanf("%d%d",&n,&m),n||m){
		if (Case) puts("");
		rep(i,n+m) scanf("%d",&t),a[L++]=chg(t),scanf("%d",&t),a[L++]=chg(t)+1;
		rep(i,L) p[i]=i; sort(p,p+L,cmp); int X=0,Y=0; flag=1,printf("Case %d:\n",++Case);
		rep(k,L){
			int i=p[k],x=X,y=Y; (i<n*2?X:Y)+=i&1?-1:1;
			if (y && !Y && !X || y && !x && X) Prt(last,a[i]);
			if (!y && Y && !X || y && x && !X) last=a[i];
		}
		if (flag) puts("    No additional quotes are required.");
	}
	return 0;
}
