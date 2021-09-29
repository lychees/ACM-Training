#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#define PolygonN 205
using namespace std;

namespace Geometry{
	const double EPS=1e-10,MAXV=1e10;
	int dcmp(const double &a,double b=0){
		if (a-b>EPS) return 1;
		if (b-a>EPS) return -1;
		return 0;
	}
	double round(double x,int k){
		for (int i=1;i<=k;i++) x*=10;
		x=ceil(x);
		for (int i=1;i<=k;i++) x/=10;
		return x;
	}
	inline double sqr(double a){return a*a;}
	struct Point{
		double x,y;
		Point(double x=0,double y=0):x(x),y(y){};
		double dis(const Point &A)const{return sqrt(sqr(A.x-x)+sqr(A.y-y));}
		void read(){
			scanf("%lf%lf",&x,&y);
		}	
		void print(){
			printf("%.2lf %.2lf\n",x,y);
		}
	};
	inline double det(const Point &A,const Point &B){return A.x*B.y-A.y*B.x;}
	inline double dot(const Point &A,const Point &B){return A.x*B.x+A.y*B.y;}//Atention not '-'!
	inline double cross(const Point &A,const Point &B,const Point &C){return det(A,B)+det(B,C)+det(C,A);}
	Point operator + (const Point &A,const Point &B){return Point(A.x+B.x,A.y+B.y);}
	Point operator - (const Point &A,const Point &B){return Point(A.x-B.x,A.y-B.y);}
	Point operator * (const double &k,const Point &A){return Point(A.x*k,A.y*k);}
	Point operator * (const Point &A,const double &k){return Point(A.x*k,A.y*k);}
	Point operator / (const Point &A,const double &k){if (!k) return Point(0,0);return Point(A.x/k,A.y/k);}
	bool cmpY(Point A,Point B){return A.y<B.y||(A.y==B.y&&A.x<B.x);}
	
	struct Line{
		Point A,dir;
		Line(const Point &A,const Point &dir):A(A),dir(dir){};
		double disSeg(const Point &P){
			Point B(A+dir);
			if (dcmp(dot(P-A,B-A))<=0) return P.dis(A);
			if (dcmp(dot(P-B,A-B))<=0) return P.dis(B);
			return fabs(det(P-A,P-B))/A.dis(B);
		}
		double disLine(const Point &P){
			Point B(A+dir);	
			return fabs(det(P-A,P-B))/A.dis(B);
		}
	};
	struct Polygon{
		int n;Point a[PolygonN];
		void convex(){
			static Point d[PolygonN];
			sort(a+1,a+n+1,cmpY);
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
		double wide(){
			int t=2;double ans=MAXV;a[n+1]=a[1];
			for (int i=1;i<=n;i++){
				while (dcmp(cross(a[i],a[i+1],a[t]),cross(a[i],a[i+1],a[t+1]))<0) t=t%n+1;//Attention!!!
   	         	ans=min(ans,Line(a[i],a[i+1]-a[i]).disLine(a[t]));
   	        }
			return ans;
		}
	};	
}
using namespace Geometry;

Polygon a;
int main(){
	freopen("trash.in","r",stdin);
	freopen("trash.out","w",stdout);
	int cas=0;
	while (scanf("%d",&a.n)!=EOF&&a.n){
		cas++;
		for (int i=1;i<=a.n;i++) a.a[i].read();
		a.convex();
		printf("Case %d: %.2lf\n",cas,round(a.wide(),2));
	}	
	return 0;
}
