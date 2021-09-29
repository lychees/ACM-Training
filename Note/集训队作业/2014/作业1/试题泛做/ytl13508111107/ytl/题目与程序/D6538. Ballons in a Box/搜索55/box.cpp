#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#define N 10
using namespace std;

const double PI=acos(-1);
const int inf=0x7fffffff/3;

int n,use[N];
double a1,a2,b1,b2,c1,c2,ans;

inline double sqr(double a){return a*a;}
inline double sqr3(double a){return a*a*a;}
struct Circle{
	double x,y,z,r;
	Circle(double x=0,double y=0,double z=0,double r=0):x(x),y(y),z(z),r(r){};
	void read(){
		scanf("%lf%lf%lf",&x,&y,&z);
	}
	double dis(const Circle &c){
		return sqrt(sqr(c.x-x)+sqr(c.y-y)+sqr(c.z-z));
	}	
}c[N];

void choose(int i){
	double x=inf;
	for (int j=1;j<=n;j++) if (use[j]) x=min(x,c[i].dis(c[j])-c[j].r);
	x=min(x,abs(a1-c[i].x));
	x=min(x,abs(a2-c[i].x));
	x=min(x,abs(b1-c[i].y));
	x=min(x,abs(b2-c[i].y));
	x=min(x,abs(c1-c[i].z));
	x=min(x,abs(c2-c[i].z));
	c[i].r=x;
}
void search(int k,double now){
	
	/*if (k==n+1){
		now=now*PI*4/3;
		ans=max(ans,now);
		return;
	}*/
	if (now>ans) ans=now;
	if (k==n+1) return;
	for (int i=1;i<=n;i++) if (!use[i]){
		choose(i);
		if (c[i].r<1e-6) continue;
		use[i]=1;
		search(k+1,now+sqr3(c[i].r)*PI*4/3);
		use[i]=0;
	}
}

void init(){
	ans=0;
	for (int i=1;i<=n;i++) use[i]=0; 
}
int main(){
	freopen("box.in","r",stdin);
	freopen("box.out","w",stdout);
	while(scanf("%d",&n)!=EOF){
		init();
		scanf("%lf%lf%lf%lf%lf%lf",&a1,&b1,&c1,&a2,&b2,&c2);
		if (a1>a2) swap(a1,a2);
		if (b1>b2) swap(b1,b2);
		if (c1>c2) swap(c1,c2);
		for (int i=1;i<=n;i++) c[i].read();
		search(1,0);
		printf("%.lf\n",(a2-a1)*(b2-b1)*(c2-c1)-ans);
	}
	return 0;
}
