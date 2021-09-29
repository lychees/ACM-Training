#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
#define N 505
int Case,n,x,cnt; long double f[N],a[N];
const double pi=acos(-1.);
long double work(int i,int j)
{
	if (i+1>=j) return 0; ++cnt;
	long double l=0,r=1e5,mid,s,area=0,theta,L=0,sum=0; int x;
	for (int k=i;k<=j;k++) {sum+=a[k]; if (a[k]>L) L=a[k],x=k;}
	l=L;
	while (l+1e-10<r){
		mid=(l+r)/2,s=0;
		for (int k=i;k<=j;k++) s+=asin(a[k]/mid)*2;
		if (s>2*pi) l=mid; else r=mid;
		}
	s=0; for (int k=i;k<=j;k++) s+=asin(a[k]/r)*2;
	if (fabs(s-2*pi)<1e-3){
		for (int k=i;k<=j;k++)
			theta=asin(a[k]/r),area+=sqrt(r*r-a[k]*a[k])*a[k];	
		return area;
		}
	l=L,r=1e5;
	while (l+1e-10<r){
		mid=(l+r)/2,s=0;
		for (int k=i;k<=j;k++) s+=asin(a[k]/mid)*2*(k==x?-1:1);
		if (s<0) l=mid; else r=mid;
		}
	s=0; for (int k=i;k<=j;k++) s+=asin(a[k]/r)*2*(k==x?-1:1);
	if (fabs(s)<1e-10){
		long double tmp=0;
		for (int k=i;k<=j;k++)
			theta=asin(a[k]/r),tmp+=sqrt(r*r-a[k]*a[k])*a[k]*(k==x?-1:1);
		if (tmp>area) area=tmp;
		}
	if (fabs(L*2-sum)<1e-10) area=0;
	return max(area,work(i,x-1)+work(x+1,j));
}
int main()
{
	freopen("G.in","r",stdin);
	freopen("G.out","w",stdout);
	while (scanf("%d",&n),n){
		for (int i=1;i<=n;i++) scanf("%d",&x),a[i]=x/2.;
		printf("Case %d: %.15lf\n",++Case,double(work(1,n)));
		}
	return 0;
}
