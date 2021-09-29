#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=100005;
int n,Case,p[N*3]; double T;
struct node{
	double x,y; node(){}
	node(double _x,double _y):x(_x),y(_y){}
	bool operator ==(const node &A) const {return x==A.x && y==A.y;}
	bool operator <(const node &A) const {return x==A.x?y<A.y:x<A.x;}
	node operator -(const node &A) const {return node(x-A.x,y-A.y);}
	double operator ^(const node &A) const {return x*A.y-y*A.x;}
	void read(){scanf("%lf%lf",&x,&y),x+=y*1e-7;}
}a[N*3];
double get(double T,const node &A,const node &B){return (T-A.x)/(B.x-A.x)*(B.y-A.y)+A.y;}
struct seg{
	node A,B; int id,flag,val; seg(){}
	seg(const node &_A,const node &_B,int _id,int _flag):A(_A),B(_B),id(_id),flag(_flag){val=1;}
	bool operator <(const seg &E) const{
		return	A==E.A && B==E.B?	0:
				T==A.x && A==E.A?	get(T+1e-5,A,B)<get(T+1e-5,E.A,E.B):
				T==B.x && B==E.B?	get(T-1e-5,A,B)<get(T-1e-5,E.A,E.B):
									get(T,A,B)<get(T,E.A,E.B);
	}
	bool operator ^(const seg &E) const{
		if (id==E.id) return 0;
		return	((B-A)^(E.A-A))*((B-A)^(E.B-A))<1e-4 &&
				((E.B-E.A)^(A-E.A))*((E.B-E.A)^(B-E.A))<1e-4;
	}
}s[N];
set<seg> L;
bool cmp(const int &i,const int &j){return a[i]<a[j];}
#define del(s) it=L.lower_bound(s),side=it->flag,l=r=it; if (*--l^*++r) return 0; L.erase(it);
#define ins(s)\
	t=s; l=L.upper_bound(t),r=l--; if ((t^*l) || (t^*r)) return 0;\
	if (t.flag) t.val=r->val+r->flag; else t.val=l->val+!l->flag;\
	L.insert(t); ans=max(ans,t.val);
int work()
{
	int m=3*n,side,ans=1; rep(i,m) p[i]=i; sort(p,p+m,cmp);
	rep(i,m-1) if (a[p[i]]==a[p[i+1]]) return 0;
	set<seg> :: iterator it,l,r; L.clear(); T=-1e7;
	L.insert(seg(node(-1e7,-1e7),node(1e7,-1e7),-1,0));
	L.insert(seg(node(-1e7,1e7),node(1e7,1e7),-1,1));
	rep(k,m){
		int i=p[k],j=i/3; seg t; T=a[i].x;
		if (j*3==i){
			int tmp=get(T+1e-5,a[i],a[j*3+2])<get(T+1e-5,a[i],a[j*3+1]);
			ins(seg(a[i],a[j*3+1],j,tmp)); ins(seg(a[i],a[j*3+2],j,!tmp));
		}else if (j*3+1==i){del(seg(a[j*3],a[i],j,0)); ins(seg(a[i],a[j*3+2],j,side));}
		else {del(seg(a[j*3],a[i],j,0)); del(seg(a[j*3+1],a[i],j,0));}
	}
	return ans;
}
int main()
{
	while (scanf("%d",&n),n>=0){
		rep(i,n){rep(j,3) a[i*3+j].read(); sort(a+i*3,a+i*3+3);}
		int res=work(); printf("Case %d: ",++Case);
		if (res) printf("%d shades\n",res); else puts("ERROR");
	}
	return 0;
}
