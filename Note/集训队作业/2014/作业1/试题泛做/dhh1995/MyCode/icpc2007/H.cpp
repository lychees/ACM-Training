#include<cstdio>
#include<cmath>
#include<set>
#include<map>
#include<algorithm>
using namespace std;
double tmp;
#define double long double
#define rep0(i,n) for (int i=0;i<n;++i)
#define rep(i,n) for (int i=1;i<=n;++i)
const double eps=1e-9; const int N=4005,M=1100005;
int Case,n,m,s,D,E,x[N],y[N],st[M],ed[M],son[M],next[M],p[M]; double e[M],h[M],ans; bool v[M];
double Read(){scanf("%lf",&tmp); return tmp;}
struct node{
	double x,y; node(){}
	node(double _x,double _y):x(_x),y(_y){}
	node operator +(const node &A){return node(x+A.x,y+A.y);}
	node operator -(const node &A){return node(x-A.x,y-A.y);}
	node operator *(const double &A){return node(x*A,y*A);}
	node operator /(const double &A){return node(x/A,y/A);}
	double operator %(const node &A){return x*A.y-y*A.x;}
	double operator *(const node &A){return x*A.x+y*A.y;}
	bool operator <(const node &A) const{return fabs(x-A.x)<eps?y<A.y:x<A.x;}
	double angle(){return atan2(y,x);}
	double len(){return sqrt(x*x+y*y);}
	void read(){x=Read(),y=Read();}
}d[M],O;
struct vec{
	node P; double z;
	void read(){P.read(); z=Read();}
	double len(){return sqrt(P.x*P.x+P.y*P.y+z*z);}
}a[N];
struct tri{
	vec A,B,C,V; double p;
	double cal(node &U){return A.z-(U-A.P)*V.P/V.z;}
	void read(){
		++s,scanf("%d%d%d",x+s,x+s+1,x+s+2);
		y[s]=x[s+1],y[s+1]=x[s+2],y[s+2]=x[s];
		A=a[x[s]],B=a[x[s+1]],C=a[x[s+2]],s+=2;
		vec U,W; U.P=B.P-A.P,U.z=B.z-A.z,W.P=C.P-A.P,W.z=C.z-A.z;
		V.P=node(U.P.y*W.z-W.P.y*U.z,U.z*W.P.x-W.z*U.P.x),V.z=U.P%W.P;
		p=V.z/V.len();
	}
}t[N];
map<node,int> H; set<pair<int,int> > Edge;
bool online(node &A,node &B,node &C){return fabs((B-A)%(C-A))<eps;}
bool cross(node &A,node &B,node &C,node &D,node &E)
{
	if (online(A,B,C) && online(A,B,D)) return 0;
	double s1=(C-A)%(B-A),s2=(D-A)%(B-A);
	if (s1*s2>0 || ((A-C)%(D-C))*((B-C)%(D-C))>0) return 0;
	return E=(C*s2-D*s1)/(s2-s1),1;
}
bool cmp(const int i,const int j){return d[i]<d[j];}
bool cmpe(const int i,const int j){return e[i]<e[j];}
int get(node &A){if (H.find(A)!=H.end()) return H[A]; d[++D]=A,H[A]=D; return D;}
void add(int x,int y)
{
	if (x>y) swap(x,y); pair<int,int> pr=make_pair(x,y);
	if (x!=y && Edge.find(pr)==Edge.end())
		Edge.insert(pr),st[E]=ed[E+1]=x,st[E+1]=ed[E]=y,E+=2;
}
int chg(double a){return a>eps?1:a<-eps?2:0;}
bool inside(node &A,tri &T)
{
	int c[3]={0,0,0};
	++c[chg((A-T.B.P)%(T.A.P-T.B.P))];
	++c[chg((A-T.C.P)%(T.B.P-T.C.P))];
	++c[chg((A-T.A.P)%(T.C.P-T.A.P))];
	return !c[1] || !c[2];
}
int main()
{
	while (scanf("%d%d",&n,&m),n || m){
		Edge.clear(),H.clear(); D=E=s=0,ans=0;
		rep(i,n) a[i].read(),x[++s]=i,y[s]=n+1; a[++n].P=node(0,0); rep(i,m) t[i].read();
		rep(i,s){
			int L=0; p[L++]=get(a[x[i]].P),p[L++]=get(a[y[i]].P);
			rep(j,s) if (cross(a[x[i]].P,a[y[i]].P,a[x[j]].P,a[y[j]].P,O)) p[L++]=get(O);
			sort(p,p+L,cmp); rep(k,L-1) add(p[k-1],p[k]);
		}
		rep(i,D) son[i]=-i; rep0(i,E) v[i]=0,p[i]=i,e[i]=(d[ed[i]]-d[st[i]]).angle();
		sort(p,p+E,cmpe); rep0(k,E){int i=p[k],x=st[i]; next[i]=son[x],son[x]=i;}
		rep0(i,E) if (!v[i]){
			int j=i,x,y,z=0; double sum=0,opt=0; rep(k,m) h[k]=0;
			do{
				v[j]=1,x=st[j],y=ed[j],sum+=d[x]%d[y];
				rep(k,m) if (h[k]<0 || !inside(d[x],t[k])) h[k]=-1; else h[k]+=t[k].cal(d[x]);
				j^=1,j=next[j]<0?son[-next[j]]:next[j];
			}while (j!=i);
			rep(k,m) if (h[k]>opt) opt=h[k],z=k; if (z>0) ans+=fabs(sum/2/t[z].p);
		}
		printf("Case %d: %.2lf\n\n",++Case,tmp=ans);
	}
	return 0;
}
