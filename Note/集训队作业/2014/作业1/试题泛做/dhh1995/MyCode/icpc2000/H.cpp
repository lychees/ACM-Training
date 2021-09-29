#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const double eps=1e-8;
int Case,x,y,z;
struct node{
	double x,y; node(){}
	node(double _x,double _y):x(_x),y(_y){}
	node operator +(const node &A){return node(x+A.x,y+A.y);}
	node operator -(const node &A){return node(x-A.x,y-A.y);}
	node operator *(const double &A){return node(x*A,y*A);}
	node operator /(const double &A){return node(x/A,y/A);}
	double operator %(const node &A){return x*A.y-y*A.x;}
	node turn(){return node(y,x);}
	double Max(){return max(x,y);}
	double len(){return sqrt(x*x+y*y);}
	void read(){scanf("%lf%lf",&x,&y);}
}A,B,C,D,E,F,O=node(0,0),X,Y;
bool check(node A,node B,node C)
{return (D-E).len()+eps>(A+B).Max() && (D-F).len()+eps>(A+C).Max() && (E-F).len()+eps>(B+C).Max();}
void move(node &A,node &B,double r)
{node V=(B-A).turn(); V.y=-V.y; V=V/V.len()*r,A=A+V,B=B+V;}
void cross(node A,node B,node C,node D,double r,node &E)
{
	move(A,B,r),move(C,D,r);
	double s1=(C-A)%(B-A),s2=(D-A)%(B-A);
	E=(C*s2-D*s1)/(s2-s1);
}
bool work(double x,double y,double z)
{
	double Cos=(x*x+y*y-z*z)/(2*x*y),Sin=sqrt(1-Cos*Cos),R=x*y*Sin/(x+y+z)+eps;
	if (A.y>R || B.y>R || C.y>R) return 0; X=node(x,0),Y=node(Cos*y,Sin*y);
	cross(X,O,O,Y,A.y,D),cross(Y,X,X,O,B.y,E),cross(O,Y,Y,X,C.y,F);
	return check(A.turn(),B,C) || check(A,B.turn(),C) || check(A,B,C.turn());
}
int main()
{
	while (scanf("%d%d%d",&x,&y,&z),x){
		A.read(),B.read(),C.read(),A=A/2,B=B/2,C=C/2;
		if (Case) puts(""); printf("Triangle number %d:\n",++Case);
		if (work(x,y,z) || work(x,z,y) || work(y,x,z) || work(y,z,x) || work(z,x,y) || work(z,y,x))
			puts("All three stoppers will fit in the triangular space");
		else puts("Stoppers will not fit in the triangular space");
	}
	return 0;
}
