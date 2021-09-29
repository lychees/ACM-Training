#include<cstdio>
#include<cmath>
#include<set>
#include<map>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
double tx,ty;
#define double long double
const double eps=1e-10; const int N=40005;
char PRT[100005],*buffer;
int Case,n,m,D,E,ans,st[N],ed[N],son[N],next[N],p[N]; double e[N]; bool v[N];
struct node{
	double x,y; node(){}
	node(double _x,double _y):x(_x),y(_y){}
	node operator +(const node &A){return node(x+A.x,y+A.y);}
	node operator -(const node &A){return node(x-A.x,y-A.y);}
	node operator *(const double &A){return node(x*A,y*A);}
	node operator /(const double &A){return node(x/A,y/A);}
	double operator %(const node &A){return x*A.y-y*A.x;}
	bool operator <(const node &A) const{return fabs(x-A.x)<eps?y<A.y:x<A.x;}
	double angle(){return atan2(y,x);}
	double len(){return sqrt(x*x+y*y);}
	void read(){scanf("%lf%lf",&tx,&ty),x=tx,y=ty;}
	void prt(){buffer+=sprintf(buffer,"(%.2lf,%.2lf)",tx=x,ty=y);}
}a[N],b[N],d[N],O;
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
int get(node &A){if (H.find(A)!=H.end()) return H[A]; return d[D]=A,H[A]=D++;}
void add(int x,int y)
{
	if (x>y) swap(x,y); pair<int,int> pr=make_pair(x,y);
	if (x!=y && Edge.find(pr)==Edge.end()) Edge.insert(pr),st[E]=ed[E+1]=x,st[E+1]=ed[E]=y,E+=2;
}
bool up(node A,node B,node &C)
{if (B<A) swap(A,B); return A.x<C.x+eps && C.x+eps<B.x && (C-A)%(B-A)<0;}
bool inside(int n,node *a,node &A,node &B)
{
	node C=(A+B)/2,V=A-B; V=node(V.y,-V.x); C=C+V/V.len()*1e-6; int c=0;
	rep(i,n) if (up(a[i],a[i+1],C)) c^=1; return c;
}
int main()
{
	for(;;){
		scanf("%d",&n); rep(i,n) a[i].read(); a[n]=*a;
		scanf("%d",&m); rep(i,m) b[i].read(); b[m]=*b;
		if (!n && !m) break;
		Edge.clear(),H.clear(); D=E=ans=0,buffer=PRT,*PRT='\0';
		rep(i,n){
			int L=0; p[L++]=get(a[i]),p[L++]=get(a[i+1]);
			rep(j,m) if (cross(a[i],a[i+1],b[j],b[j+1],O)) p[L++]=get(O);
			sort(p,p+L,cmp); rep(k,L-1) add(p[k],p[k+1]);
		}
		rep(j,m){
			int L=0; p[L++]=get(b[j]),p[L++]=get(b[j+1]);
			rep(i,n) if (cross(a[i],a[i+1],b[j],b[j+1],O)) p[L++]=get(O);
			sort(p,p+L,cmp); rep(k,L-1) add(p[k],p[k+1]);
		}
		rep(i,D) son[i]=-1-i; rep(i,E) v[i]=0,p[i]=i,e[i]=(d[ed[i]]-d[st[i]]).angle();
		sort(p,p+E,cmpe); rep(k,E){int i=p[k],x=st[i]; next[i]=son[x],son[x]=i;}
		rep(i,E) if (!v[i] && inside(n,a,d[st[i]],d[ed[i]]) && inside(m,b,d[st[i]],d[ed[i]])){
			int j=i,L=0,w=0; ++ans;
			do{
				v[j]=1,p[L]=st[j]; if (d[p[L]]<d[p[w]]) w=L; ++L; j^=1;
				if (next[j]<0) j=son[-next[j]-1]; else j=next[j];
			}while (j!=i);
			buffer+=sprintf(buffer,"Region %d:",ans);
			rep(k,L){
				int x=(k+w)%L;
				if (!k || !online(d[p[(x+L-1)%L]],d[p[x]],d[p[(x+1)%L]])) d[p[x]].prt();
			}
			buffer+=sprintf(buffer,"\n");
		}
		printf("Data Set %d\n",++Case);
		printf("Number of intersection regions: %d\n%s",ans,PRT);
	}
	return 0;
}
