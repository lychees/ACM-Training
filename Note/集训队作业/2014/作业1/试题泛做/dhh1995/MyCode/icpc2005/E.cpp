#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const int S=20220,T=45600; const double pi=acos(-1.);
int Case,n,w,h,x,y,m[105],d[105];
void prt(double x){int t=S+T*x; printf("%02d:%02d:%02d",t/3600,t/60%60,t%60);}
double cal(int x,int y){return atan(1.*y/x);}
int main()
{
	while (scanf("%d",&n),n){
		scanf("%d%d",&w,&h);
		rep(i,n){scanf("%d",m+i); if (i<n) scanf("%d",d+i+1),d[i+1]+=d[i];}
		printf("Apartment Complex: %d\n",++Case);
		while (scanf("%d",&x),x){
			printf("Apartment %d: ",x),y=x/100,x%=100;
			if (!x || !y || x>n || y>m[x]) puts("Does not exist");
			else{
				double L=0,R=0;
				rep(i,n){
					if (i<x && m[i]>=y) L=max(L,cal(w*(x-i-1)+d[x]-d[i],h*(m[i]-y+1)));
					if (i>x && m[i]>=y) R=max(R,cal(w*(i-x-1)+d[i]-d[x],h*(m[i]-y+1)));
				}
				prt(L/pi),printf(" - "),prt(1-R/pi),puts("");
			}
		}
	}
	return 0;
}
