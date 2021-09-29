#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#define N 30
#define PolygonN N
using namespace std;

double ans,ddd;
namespace Geometry{
	const double EPS=1e-8,PI=acos(-1);
	
	int dcmp(const double &a,double b=0){
		if (a-b>EPS) return 1;
		if (b-a>EPS) return -1;
		return 0;
	}	
	inline double sqr(double a){
		return a*a;
	}	
	struct Point{
		double x,y;
		Point(double x=0,double y=0):x(x),y(y){};
		double len()const{
			return sqrt(sqr(x)+sqr(y));
		}	
		double dis(const Point &A)const{
			return sqrt(sqr(A.x-x)+sqr(A.y-y));
		}
		void read(){
			scanf("%lf%lf",&x,&y);
		}
		void print()const{
			printf("%.2lf %.2lf\n",x,y);
		}
	};
	double dot(const Point &A,const Point &B){
		return A.x*B.x+A.y*B.y;
	}	
	double det(const Point &A,const Point &B){
		return A.x*B.y-A.y*B.x;
	}
	double cos(const Point &A,const Point &B){
		if (A.len()*B.len()==0) return 0;return dot(A,B)/(A.len()*B.len());
	}
	Point operator + (const Point &A,const Point &B){return Point(A.x+B.x,A.y+B.y);}
	Point operator - (const Point &A,const Point &B){return Point(A.x-B.x,A.y-B.y);}
	Point operator * (const double &k,const Point &A){return Point(A.x*k,A.y*k);}
	Point operator * (const Point &A,const double &k){return Point(A.x*k,A.y*k);}
	Point operator / (const Point &A,const double &k){if (!k) return Point(0,0);return Point(A.x/k,A.y/k);}
	bool operator == (const Point &A,const Point &B){
		return dcmp(A.x,B.x)==0&&dcmp(A.y,B.y)==0;
	}
	struct Polygon{
		int n;
		Point a[PolygonN];
		bool pointIn(const Point &P){ 
			int tot=0;           
   	    	for (int i=1;i<=n;i++){
				int k1=dcmp(a[i].x-P.x);
				int k2=dcmp(a[i+1].x-P.x);
				int k3=dcmp(det(a[i+1]-a[i],P-a[i]));
				if (k1<=0&&k2>0&&k3>0) tot++;
				if (k2<=0&&k1>0&&k3<0) tot++;
			}
			return tot&1;
		}
		void calc(const Point &P){
			for (int i=1;i<=n;i++){ 
				double t=abs(det(a[i]-P,a[i+1]-P))/a[i].dis(a[i+1]);
				if (dcmp(t,0.5)<0&&dcmp(t,0)>0){
					if (!(dcmp(P.dis(a[i]),0.5)>=0&&dcmp(P.dis(a[i+1]),0.5)>=0&&dot(a[i]-P,a[i+1]-P)>=0))
						return;
				}
			}
			for (int i=1;i<=n;i++) 
				if (a[i]==P){
					double x=acos(cos(a[i-1]-a[i],a[i+1]-a[i]));
					if (det(a[i]-a[i-1],a[i+1]-a[i])<0) ddd+=2*PI-x;else ddd+=x;
					return;
				}
			for (int i=1;i<=n;i++){
				if (dot(a[i]-P,a[i+1]-P)<0&&det(a[i]-P,a[i+1]-P)==0){
				//	P.print();
					ans+=0.5;
					return;
				}
			}
			if (pointIn(P)) ans+=1;
		}
	};
}
using namespace Geometry;

Polygon a;
int main(){
	freopen("clear.in","r",stdin);
	freopen("clear.out","w",stdout);
	while (scanf("%d",&a.n)!=EOF&&a.n){
		ans=ddd=0;
		double Lx=400,Ly=400,Rx=400,Ry=-400;
		for (int i=1;i<=a.n;i++){ 
			a.a[i].read();
			Lx=min(Lx,a.a[i].x);
			Rx=max(Rx,a.a[i].x);
			Ly=min(Ly,a.a[i].y);
			Ry=max(Ry,a.a[i].y);
		}
		if (a.n<3){
			printf("0\n");
			continue;
		}
		if (a.n>1) reverse(a.a+2,a.a+a.n+1);
		a.a[0]=a.a[a.n];
		a.a[a.n+1]=a.a[1];
		Lx=-250,Rx=250,Ly=-250,Ry=250;
		for (int i=(int)Lx;i<=(int)Rx;i++)
			for (int j=(int)Ly;j<=(int)Ry;j++)
				a.calc(Point(i,j));
		printf("%.3lf\n",ans*0.25*PI+ddd/8);
	}		
	return 0;
}
