#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#define N 10
using namespace std;

const double MAXV=1e10,PI=acos(-1);


int n,use[N],a1,a2,b1,b2,c1,c2;
double ans;

inline double sqr(double a){return a*a;}
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
void make(){
	double r=-MAXV;int p=-1;
	for (int i=1;i<=n;i++) if (!use[i]&&c[i].r>r){
		r=c[i].r;p=i;
	}
	use[p]=1;
	ans+=PI*r*r*r*4/3;
	for (int i=1;i<=n;i++) if (!use[i]&&i!=p) c[i].r=min(c[i].r,c[i].dis(c[p])-r); 
}
void init(){
	for (int i=1;i<=n;i++) use[i]=0;
	ans=0;
}
int main(){
	freopen("box.in","r",stdin);
	freopen("box.out","w",stdout);
	int cas=0;
while (scanf("%d",&n)!=EOF&&n){
	init();cas++;
	scanf("%d%d%d%d%d%d",&a1,&b1,&c1,&a2,&b2,&c2);
	if (a1>a2) swap(a1,a2);
	if (b1>b2) swap(b1,b2);
	if (c1>c2) swap(c1,c2);
	for (int i=1;i<=n;i++) c[i].read();
	for (int i=1;i<=n;i++){
		c[i].r=MAXV;
		c[i].r=min(c[i].r,abs(c[i].x-a1));
		c[i].r=min(c[i].r,abs(c[i].x-a2));
		c[i].r=min(c[i].r,abs(c[i].y-b1));
		c[i].r=min(c[i].r,abs(c[i].y-b2));
		c[i].r=min(c[i].r,abs(c[i].z-c1));
		c[i].r=min(c[i].r,abs(c[i].z-c2));
	}
	for (int i=1;i<=n;i++) make();
	//printf("Box %d: %.lf\n\n",cas,(a2-a1)*(b2-b1)*(c2-c1)-ans); 
	printf("%.lf\n",(a2-a1)*(b2-b1)*(c2-c1)-ans);
}
	return 0;
}
