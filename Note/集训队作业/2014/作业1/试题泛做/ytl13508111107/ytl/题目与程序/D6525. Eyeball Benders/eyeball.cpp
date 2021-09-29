//By ytl 2013-11-26
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
#define N 55
#define T (N*N+2*N)
using namespace std;

const double EPS=1e-6,MAXV=1e10;

double mU,mD,mL,mR,D,U,L,R,Lv;
int cpTot0,cpTot1,n,m;
int go[2][T][4],totx[2],toty[2],num[2];

inline double sqr(double a){return a*a;}
int dcmp(const double &a,double b=0){
	if (a-b>EPS) return 1;
	if (b-a>EPS) return -1;
	return 0;
}

struct Point{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y){};
	double dis(const Point &A){return sqrt(sqr(A.x-x)+sqr(A.y-y));}
	bool in(){
		return dcmp(L,x)<=0&&dcmp(x,R)<=0&&dcmp(D,y)<=0&&dcmp(y,U)<=0;
	} 
	bool out(){
		return dcmp(x,L)<=0||dcmp(R,x)<=0||dcmp(y,D)<=0||dcmp(U,y)<=0;
	} 
	void print()const{
		printf("%.2lf %.2lf\n",x,y);
	}
	void printe()const{
		printf("%.2lf %.2lf",x,y);
	}
};

map<Point,int> my[2];
Point p[2][T],cp[2][T];


bool operator != (const Point &A,const Point &B){
	return dcmp(A.x,B.x)!=0||dcmp(A.y,B.y)!=0;
}
bool operator < (const Point &A,const Point &B){
	return dcmp(A.x,B.x)<0||(dcmp(A.x,B.x)==0&&dcmp(A.y,B.y)<0);
}
inline bool cmp(const Point &A,const Point &B){return A<B;}

int id(const Point &A,int t){
	if (my[t].find(A)==my[t].end()){
		num[t]++;
		my[t][A]=num[t];
		p[t][num[t]]=A;
		return num[t];
	}else return my[t][A];
}
struct data{
	int tot;
	double a,b[N];
	void build(int k,int t){
		sort(b+1,b+tot+1);
		int tt=tot;tot=0;
		for (int i=1;i<=tt;i++) if (i==1||dcmp(b[i],b[i-1])!=0) b[++tot]=b[i];
		for (int i=1;i<tot;i++){
			int p1,p2;
			if (k==0){
				p1=id(Point(a,b[i]),t);
				p2=id(Point(a,b[i+1]),t);
			}else{
				p1=id(Point(b[i],a),t);
				p2=id(Point(b[i+1],a),t);
			}
			go[t][p1][k^1]=p2;
			go[t][p2][k]=p1;
		}
	}	
	void push(double x){
		b[++tot]=x;
	}
	void print(){
		printf("%.2lf :",a);
		for (int i=1;i<=tot;i++) printf("%.2lf ",b[i]);
		printf("\n");
	}
	inline double head(){
		return b[1];
	}
	inline double tail(){
		return b[tot];
	}
};


data lx[2][N],ly[2][N];


Point operator * (const Point &A,const double &k){
	return Point(A.x*k,A.y*k);
}
Point operator - (const Point &A,const Point &B){
	return Point(A.x-B.x,A.y-B.y);
}
bool comp(const Point &A,const Point &B){
	sort(cp[1]+1,cp[1]+cpTot1+1,cmp);
	int tt=cpTot1;cpTot1=0;
	for (int i=1;i<=tt;i++) if (i==1||cp[1][i]!=cp[1][i-1]) cp[1][++cpTot1]=cp[1][i];
	
	if (cpTot0!=cpTot1) return false;
	for (int i=1;i<=cpTot0;i++){
		if ((cp[0][i]-A)*Lv!=cp[1][i]-B) return false;
	}	
	return true;
}
bool check(const Point &A,const Point &B){
	int p0=my[0][A],p1=my[1][B],flag=0;
	for (int i=0;i<4;i++) if (go[0][p0][i]){
		if (go[1][p1][i]){
			Lv=p[1][p1].dis(p[1][go[1][p1][i]])/p[0][p0].dis(p[0][go[0][p0][i]]);
			flag=1;
			break;
		}
	}
	if (!flag||dcmp(Lv,1)>0) return false;
	L=B.x-(A.x-mL)*Lv;
	R=B.x+(mR-A.x)*Lv;
	D=B.y-(A.y-mD)*Lv;
	U=B.y+(mU-A.y)*Lv;

	cpTot1=0;
	for (int i=1;i<=num[1];i++) if (p[1][i].in()) cp[1][++cpTot1]=p[1][i];
	for (int i=1;i<=m;i++){
		for (int i=1;i<=totx[1];i++) if (dcmp(D,lx[1][i].a)<=0&&dcmp(lx[1][i].a,U)<=0){
			Point A(lx[1][i].head(),lx[1][i].a);
			Point B(lx[1][i].tail(),lx[1][i].a);
			if (dcmp(A.x,L)<=0&&dcmp(R,B.x)<=0){
				cp[1][++cpTot1]=Point(L,A.y);
				cp[1][++cpTot1]=Point(R,A.y);
			}else if (dcmp(A.x,R)<=0&&dcmp(R,B.x)<=0) cp[1][++cpTot1]=Point(R,A.y);
			else if (dcmp(A.x,L)<=0&&dcmp(L,B.x)<=0){
				cp[1][++cpTot1]=Point(L,A.y);
			}
		}
		for (int i=1;i<=toty[1];i++) if (dcmp(L,ly[1][i].a)<=0&&dcmp(ly[1][i].a,R)<=0){
			Point A(ly[1][i].a,ly[1][i].head());
			Point B(ly[1][i].a,ly[1][i].tail());
			if (dcmp(A.y,D)<=0&&dcmp(U,B.y)<=0){
				cp[1][++cpTot1]=Point(A.x,D);
				cp[1][++cpTot1]=Point(A.x,U);
			}else if (dcmp(A.y,U)<=0&&dcmp(U,B.y)<=0) cp[1][++cpTot1]=Point(A.x,U);
			else if (dcmp(A.y,D)<=0&&dcmp(D,B.y)<=0){
				 cp[1][++cpTot1]=Point(A.x,D);
			}
		}
	}
	if (comp(A,B)){
		return true;
	}else return false;
}
void build(data lx[],int &totx,data ly[],int &toty,int t){
	for (int i=1;i<=totx;i++) lx[i].build(2,t);
	for (int i=1;i<=toty;i++) ly[i].build(0,t);				
}
void  intersect(data lx[],int totx,data ly[],int toty,int t){
	for (int i=1;i<=totx;i++)
		for (int j=1;j<=toty;j++){
			if (lx[i].b[1]<=ly[j].a&&ly[j].a<=lx[i].b[2]&&ly[j].b[1]<=lx[i].a&&lx[i].a<=ly[j].b[2]){
				lx[i].push(ly[j].a); 
				ly[j].push(lx[i].a);
			}
		}
}
void read(int n,data lx[],int &totx,data ly[],int &toty){
	for (int i=1;i<=n;i++){
		double a1,a2,b1,b2;
		scanf("%lf%lf%lf%lf",&a1,&b1,&a2,&b2);
		if (a1>a2) swap(a1,a2);
		if (b1>b2) swap(b1,b2);
		if (b1==b2){
			totx++;
			lx[totx].a=b1;
			lx[totx].tot=2;
			lx[totx].b[1]=a1;
			lx[totx].b[2]=a2;	
		}else{
			toty++;
			ly[toty].a=a1;
			ly[toty].tot=2;
			ly[toty].b[1]=b1;
			ly[toty].b[2]=b2;	
		} 
	}
}
void makecp0(){
	mL=MAXV;
	mR=-MAXV;
	mU=-MAXV;
	mD=MAXV;
	cpTot0=num[0];
	for (int i=1;i<=num[0];i++){
		cp[0][i]=p[0][i];
		mL=min(mL,p[0][i].x);
		mR=max(mR,p[0][i].x);
		mD=min(mD,p[0][i].y);
		mU=max(mU,p[0][i].y);	
	}
	sort(cp[0]+1,cp[0]+cpTot0+1,cmp);
}

int main(){
	freopen("eyeball.in","r",stdin);
	freopen("eyeball.out","w",stdout);
	scanf("%d%d",&n,&m);
	read(n,lx[0],totx[0],ly[0],toty[0]);
	read(m,lx[1],totx[1],ly[1],toty[1]);


	intersect(lx[0],totx[0],ly[0],toty[0],0);
	intersect(lx[1],totx[1],ly[1],toty[1],1);
	build(lx[0],totx[0],ly[0],toty[0],0);
	build(lx[1],totx[1],ly[1],toty[1],1);
	
	
	makecp0();

	for (int i=1;i<=totx[0];i++)
		for (int j=1;j<=totx[1];j++){
			if (check(Point(lx[0][i].b[1],lx[0][i].a),
				      Point(lx[1][j].b[1],lx[1][j].a)))
			    {printf("valid puzzle\n");exit(0);}	  
			if (check(Point(lx[0][i].b[lx[0][i].tot],lx[0][i].a),
				      Point(lx[1][j].b[lx[1][j].tot],lx[1][j].a)))
				{printf("valid puzzle\n");exit(0);}
		}
	for (int i=1;i<=toty[0];i++)
		for (int j=1;j<=toty[1];j++){
			if (check(Point(ly[0][i].a,ly[0][i].b[1]),
			          Point(ly[1][j].a,ly[1][j].b[1])))
			    {printf("valid puzzle\n");exit(0);}
			if (check(Point(ly[0][i].a,ly[0][i].b[ly[0][i].tot]),
		   	          Point(ly[1][j].a,ly[1][j].b[ly[1][j].tot])))
	   		    {printf("valid puzzle\n");exit(0);}		   
		}
	printf("impossible\n");
	return 0;
}
