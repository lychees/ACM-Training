#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#define N 105
using namespace std;

namespace TreeDGeometry{
	const double EPS=1e-6,MAXV=1e10;
	int dcmp(double a,double b=0){
		if (a-b>EPS) return 1;
		if (b-a>EPS) return -1;
		return 0;
	}
	double round(double x,int k){
		for (int i=1;i<=k;i++) x*=10;
		x=floor(x+0.5);
		for (int i=1;i<=k;i++) x/=10;
		return x;
	}
	inline double sqr(double a){return a*a;}
	struct Point{
		double x,y,z;
		Point(double x=0,double y=0,double z=0):x(x),y(y),z(z){};
		void read(){
			scanf("%lf%lf%lf",&x,&y,&z);
		}
		double dis(const Point &A){
			return sqrt(sqr(A.x-x)+sqr(A.y-y)+sqr(A.z-z));
		}
		
	}; 
	struct Circle{
		double x,y,z,r;
		Circle(double x=0,double y=0,double z=0,double r=0):x(x),y(y),z(z),r(r){};
		void read(){
			scanf("%lf%lf%lf%lf",&x,&y,&z,&r);
		}
		double dis(const Circle &c){
			return sqrt(sqr(c.x-x)+sqr(c.y-y)+sqr(c.z-z));
		}
		double dis(const Point &A)const{
			return sqrt(sqr(A.x-x)+sqr(A.y-y)+sqr(A.z-z));
		}
	};
	double getDis(const Point &A,const Circle &c){
		return max(0.0,c.dis(A)-c.r);
	}
}
using namespace TreeDGeometry;

Point A,B;
Circle cir[N];
double dis[N][N];
int n;

void init(){
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			dis[i][j]=MAXV;
	for (int i=1;i<=n;i++) dis[i][i]=0;
}
void Floyd(){
	for (int k=1;k<=n;k++)
		for (int i=1;i<=n;i++) if (i!=k)
			for (int j=1;j<=n;j++) if (j!=k&&j!=i)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
}
int main(){
	freopen("say.in","r",stdin);
	freopen("say.out","w",stdout);
	int cas=0;
	while (scanf("%d",&n)!=EOF&&n!=-1){
		cas++;
		init();
		for (int i=1;i<=n;i++) cir[i].read();
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				dis[i][j]= max(0.0,cir[i].dis(cir[j])-cir[i].r-cir[j].r);
		Floyd();
		A.read();
		B.read();
		double ans=A.dis(B);
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				ans=min(ans,getDis(A,cir[i])+dis[i][j]+getDis(B,cir[j]));
		printf("Cheese %d: Travel time = %.lf sec\n",cas,round(ans*10,0));
	}
	return 0;
}
