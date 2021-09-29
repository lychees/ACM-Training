//By ytl 2013-11-22
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#define N 10
using namespace std;

int use[N],s[N],n,flag;
double a[N],b[N],X;

const double EPS=1e-3;
int dcmp(const double &a,double b=0){
	if (a-b>EPS) return 1;
	if (b-a>EPS) return -1;
	return 0;
}

void check(){
	double now=a[s[1]];
	for (int i=2;i<=n;i++){
		now=max(now+X,a[s[i]]);
		if (dcmp(now,b[s[i]])>0) return;
	}
	flag=1;
}
void search(int k){
	if (k==n+1){
		check();
		return;
	}
	for (int i=n;i>=1;i--) if (!use[i]&&!flag){
		use[i]=1;
		s[++s[0]]=i;
		search(k+1);
		use[i]=0;
		s[0]--;
	}
}
bool can(double x){
	X=x;
	flag=0;
	search(1);
	return flag;
}

int main(){
	freopen("careful.in","r",stdin);
	freopen("careful.out","w",stdout);
	int cas=0;
	while (scanf("%d",&n)!=EOF&&n){
		double l,r,mid,Min=0,Max=1440;
		for (int i=1;i<=n;i++){
			scanf("%lf%lf",&a[i],&b[i]);
			Max=max(b[i],Max);
			Min=min(a[i],Min);
		}
		l=0;r=Max-Min;
		while (dcmp(l,r)<0){
			mid=(l+r)/2;
			if (can(mid)) l=mid;else r=mid;
		}
		double a=trunc(l);
		double b=trunc((l-a)*60+0.5);
		if (b>=60) {a++;b-=60;}
		printf("Case %d: %.lf:",++cas,a);
		if (b<10) printf("0");
		printf("%.lf\n",b);
	}
	return 0;
}
