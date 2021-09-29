#include <cstdio>
#include <cmath>
#include <cassert>
#include <algorithm>
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
//typedef long double ldb;
//typedef __float128 db;
//#define acos(x) acos(ldb(x))
//#define sqrt(x) sqrt(ldb(x))
//#define fabs(x) fabs(ldb(x))
//#define atan2(y,x) atan2(ldb(y),ldb(x))
typedef double db;

inline db sqr(const db x){ return x*x; }

const int N=1005,inf=int(1e9)+7;

const db pi=acos(db(-1)),Eps=1e-3,eps=1e-12;

inline int getint(){
	int f=1;
	char c;
	while((c=getchar())<'0'||c>'9') if(c=='-') f*=-1;
	int a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+(c-'0');
	return f*a;
}

int n;
db R;

struct vec{
	db x,y,z;
	vec(){
	}
	vec(db _x,db _y,db _z):x(_x),y(_y),z(_z){
	}
	friend vec operator + (const vec &a,const vec &b){
		return vec(a.x+b.x,a.y+b.y,a.z+b.z);
	}
	friend vec operator - (const vec &a,const vec &b){
		return vec(a.x-b.x,a.y-b.y,a.z-b.z);
	}
	friend db operator * (const vec &a,const vec &b){
		return a.x*b.x+a.y*b.y+a.z*b.z;
	}
	friend vec operator / (const vec &a,const vec &b){
		return vec(
			a.y*b.z-b.y*a.z,
			a.z*b.x-b.z*a.x,
			a.x*b.y-b.x*a.y
		);
	}
	friend vec operator * (const db lam,const vec &a){
		return vec(lam*a.x,lam*a.y,lam*a.z);
	}
	db norm() const{
		return sqr(x)+sqr(y)+sqr(z);
	}
	db abs() const{
		return sqrt(norm());
	}
	vec unit() const{
		return 1./abs()**this;
	}
	friend bool operator == (const vec &a,const vec &b){
		return fabs(a.x-b.x)<eps&&fabs(a.y-b.y)<eps&&fabs(a.z-b.z)<eps;
	}
	friend bool operator != (const vec &a,const vec &b){
		return !(a==b);
	}
} a[N];

struct data{
	db angle;
	int w;
	friend bool operator < (const data &a,const data &b){
		return a.angle<b.angle;
	}
} seq[N*2],*top;

vec dx,dy,dz;
vec da;
db dr;

int lev;

void add(vec st,vec en){
	if(top==seq){
		da=st*dz*dz;
		dr=(st-da).abs();
		dx=(st-da).unit();
		dy=dz/dx;
	}
	db l=atan2(st*dy,st*dx);
	db r=atan2(en*dy,en*dx);
	if(l>r){
		lev++;
	}
	*top++=(data){l,+1};
	*top++=(data){r,-1};
}

void input(){
	n=getint(),R=getint();
	for(int i=1;i<=n;i++){
		a[i].x=getint(),a[i].y=getint(),a[i].z=getint();
		if(sqr(a[i].x)+sqr(a[i].y)+sqr(a[i].z)<=sqr(R+Eps)){
			n--;
			i--;
		}
	}
}

int calc(vec d){
	d=d.unit();
	int cnt=0;
	for(int i=1;i<=n;i++) if(a[i]*d>=R+Eps-eps) cnt++;
	return cnt;
}

int Main(){
	int ans=inf;
	for(int i=1;i<=n;i++){
		top=seq;
		lev=0;
		dz=a[i].unit();
		for(int j=1;j<=n;j++) if(a[j]!=a[i]){
			vec ez=(a[j]-a[i]).unit();
			vec ex=a[i]-a[i]*ez*ez;
			db len=ex.abs();
			if(len<=R+Eps+eps){
				if(a[j].abs()>a[i].abs()&&(a[i]-ex)*(a[j]-ex)>eps){
					lev++;
				}
				continue;
			}
			ex=ex.unit();
			vec ey=ex/ez;
			assert(fabs(a[i]*ey)<eps);
			db costheta=(R+Eps)/len,sintheta=sqrt(1-costheta*costheta);
			add(costheta*ex-sintheta*ey,costheta*ex+sintheta*ey);
		}
		if(top==seq){
			ans=min(ans,lev);
		}
		else{
			sort(seq,top);
			db las=top[-1].angle-2*pi;
			for(data *cur=seq;cur<top;cur++){
				if(fabs(cur->angle-las)>eps){
					if(lev<ans){
						ans=lev;
						/*
						db theta=(las+cur->angle)/2;
						vec d=da+(dr+eps)*(cos(theta)*dx+sin(theta)*dy);
						eprintf("%d\n",int(d.unit()*a[i]>R+Eps-eps));
						eprintf("ans=%d calc=%d\n",ans,calc(d));
						*/
					}
				}
				las=cur->angle;
				lev+=cur->w;
			}
		}
	}
	return ans;
}

int main(){
	freopen("exp.in","r",stdin);
	freopen("exp.out","w",stdout);
	input();
	printf("%d\n",Main());
}