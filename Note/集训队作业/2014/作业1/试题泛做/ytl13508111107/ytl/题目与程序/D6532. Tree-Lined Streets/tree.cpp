#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#define N 205
using namespace std;

namespace Geometry{
	const double EPS=1e-6;
	int dcmp(const double &a,double b=0){
		if (a-b>EPS) return 1;
		if (b-a>EPS) return -1;
		return 0;
	}
	inline double sqr(double a){return a*a;}
	struct Point{
		double x,y;
		Point(double x=0,double y=0):x(x),y(y){};
		void read(){
			scanf("%lf%lf",&x,&y);
		}
		double len()const{
			return sqrt(sqr(x)+sqr(y));
		}
		double dis(const Point &A){
			return sqrt(sqr(A.x-x)+sqr(A.y-y));
		}
		void print(){
			printf("%.2lf %.2lf\n",x,y);
		}
	};	
	Point operator + (const Point &A,const Point &B){return Point(A.x+B.x,A.y+B.y);}
	Point operator - (const Point &A,const Point &B){return Point(A.x-B.x,A.y-B.y);}
	Point operator * (const double &k,const Point &A){return Point(A.x*k,A.y*k);}
	Point operator * (const Point &A,const double &k){return Point(A.x*k,A.y*k);}
	Point operator / (const Point &A,const double &k){if (!k) return Point(0,0);return Point(A.x/k,A.y/k);}
	double det(const Point &A,const Point &B){return A.x*B.y-A.y*B.x;}
	double dot(const Point &A,const Point &B){return A.x*B.x+A.y*B.y;}//Atention not '-'!
	
	struct Line{
		Point A,dir;
		Line(Point A=Point(0,0),Point dir=Point(0,0)):A(A),dir(dir){};
		void read(){
			A.read();dir.read();
			dir=dir-A;
		}
	};
	bool intersectSeg(const Line &la,const Line &lb,Point &P){
			Point A(la.A),A1(la.A+la.dir),
                 B(lb.A),B1(lb.A+lb.dir);
		int d1=dcmp(det(A1-A,B-A)),d2=dcmp(det(A1-A,B1-A)),d3=dcmp(det(B1-B,A-B)),d4=dcmp(det(B1-B,A1-B));
		if ((d1^d2)==-2&&(d3^d4)==-2){
			double s1=det(B-A,B1-A),s2=det(B-A1,B1-A1);
			P=A+la.dir*s1/(s1-s2);
            return true;
		}
		return false;
	}
}
using namespace Geometry;

double d[N];
Line l[N];
int n;

int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++) l[i].read();
	int ans=0;
	for (int i=1;i<=n;i++){
		Point P;int tot=0;
		for (int j=1;j<=n;j++) if (j!=i&&intersectSeg(l[i],l[j],P)){
			d[++tot]=P.dis(l[i].A);
		}
		sort(d+1,d+tot+1);
		d[0]=-25;
		d[++tot]=l[i].dir.len()+25;
		for (int j=1;j<=tot;j++) ans+=int(floor((d[j]-d[j-1])/50.0));
	}
	printf("%d\n",ans);
	return 0;
}	
