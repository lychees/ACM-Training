//By ytl 2013-11-19
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#define N 15
#define PolygonN N
using namespace std;

int n;
double CIRCLE;

namespace Geometry{
	const double EPS=1e-6;
	const double PI=acos(-1);
	
	int dcmp(const double &a,double b=0){
		if (a-b>EPS) return 1;
		if (b-a>EPS) return -1;
		return 0;
	}
	inline double sqr(double a){return a*a;}
	struct Point{
		double x,y;
		Point(double x=0,double y=0):x(x),y(y){};
		double dis(const Point &A)const{return sqrt(sqr(A.x-x)+sqr(A.y-y));}
		void read(){scanf("%lf%lf",&x,&y);}
		void print(){
			printf("%.2lf %.2lf\n",x,y);
		}
	};
	double det(const Point &A,const Point &B){return A.x*B.y-A.y*B.x;}
	double dot(const Point &A,const Point &B){return A.x*B.x+A.y*B.y;}//Atention not '-'!
	Point operator - (const Point &A,const Point &B){return Point(A.x-B.x,A.y-B.y);}
	
	bool cmpY(const Point &A,const Point &B){return A.y<B.y||(A.y==B.y&&A.x<B.x);}
	struct Polygon{
		int n;Point a[PolygonN];
		void convex(){
			static Point d[PolygonN];
			int p1=0;
			for (int i=1;i<=n;i++){
				while (p1>1&&dcmp(det(d[p1]-d[p1-1],a[i]-d[p1]))<=0) p1--;
				d[++p1]=a[i];
			}
			int p2=p1;
			for (int i=n;i>=1;i--){
				while (p2>p1&&dcmp(det(d[p2]-d[p2-1],a[i]-d[p2]))<=0) p2--;
				d[++p2]=a[i];
			}
			n=p2-1;
			for (int i=1;i<=n;i++) a[i]=d[i];
		}
		double getCircum(){
			double cir=0;
			a[n+1]=a[1];
			for (int i=1;i<=n;i++) cir+=a[i].dis(a[i+1]);
			return cir;
		}
	};
}
using namespace Geometry;

Polygon a;
Point p[N];
double f[1<<11];

double ask(int x){
	a.n=0;
	for (int i=0;i<n;i++) if ((x>>i)&1){
		a.a[++a.n]=p[i];
	}
	a.convex();
	return a.getCircum()+CIRCLE;
}
void DP(){
	for (int i=1;i<(1<<n);i++){
		f[i]=ask(i);
		for (int j=i&(i-1);j;j=i&(j-1)){
			f[i]=min(f[i],f[j]+f[i-j]);
		}
	}
}
int main(){
	freopen("deer.in","r",stdin);
	freopen("deer.out","w",stdout);
	int cas=0;
	while (scanf("%d%lf",&n,&CIRCLE)!=EOF&&(n||CIRCLE)){
		CIRCLE*=2*PI;
		for (int i=0;i<n;i++) p[i].read();
		sort(p,p+n,cmpY);
		DP();
		printf("Case %d: length = %.2lf\n",++cas,f[(1<<n)-1]);
	}
	return 0;
}
