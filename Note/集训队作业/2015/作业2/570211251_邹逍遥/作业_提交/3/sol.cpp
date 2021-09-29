#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<string>
#include<vector>
#include<queue>
#include<cmath>
#include<stack>
#include<map>
#include<set>
#define X first
#define Y second
#define mp make_pair
#define ph push
#define pb push_back
#define rep(i,a,n) for(int _tmp=n,i=a;i<=_tmp;++i)
#define dep(i,a,n) for(int _tmp=n,i=a;i>=_tmp;--i)
#define ALL(x,S) for(__typeof((S).end()) x=S.begin();x!=S.end();x++)
#define eps 1e-8
#define pi 3.1415926535897
#define sqr(x) ((x)*(x))
#define MAX(a,b) a=max(a,b)
#define MIN(a,b) a=min(a,b)
#define SZ(x) ((int)(x).size())
#define CPY(a,b) memcpy(a,b,sizeof(a))
#define CLR(a) memset(a,0,sizeof(a))
#define POSIN(x,y) (1<=(x)&&(x)<=n&&1<=(y)&&(y)<=m)
#define all(x) (x).begin(),(x).end()
#define COUT(S,x) cout<<fixed<<setprecision(x)<<S<<endl
using namespace std;
typedef long long ll;
typedef double lf;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<lf,lf> pff;
typedef complex<double> CD;
const int inf=0x20202020;
const int mod=1000000007;
char buf[20000022],*pp=buf;
template<class T> inline void read(T&x){bool fu=0;char c;for(c=*++pp;c<'0'||c>'9';c=*++pp);if(c=='-')fu=1,c=*++pp;for(x=0;c>32;c=*++pp)x=x*10+c-'0';if(fu)x=-x;};
template<class T> inline void read(T&x,T&y){read(x);read(y);}
template<class T> inline void read(T&x,T&y,T&z){read(x);read(y);read(z);}
template<class T> inline void read(T&x,T&y,T&z,T&q){read(x);read(y);read(z);read(q);}
const int DX[]={1,0,-1,0},DY[]={0,1,0,-1};
ll powmod(ll a,ll b) {ll res=1;a%=mod;for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll powmod(ll a,ll b,ll mod) {ll res=1;a%=mod;for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
//*******************************************
 
const int N=1111111,M=33333333;
struct EDGE {int a,b,l,r,s;} e[M];
int l,m,n,C;
int tot,root[N];
int rank[N],rank2[N],pai[N],sa[N],rmq[N][22];
ll h[N],X,Y;
int creat(int l,int r){
    if(l>r)return 0;e[++tot].a=l;e[tot].b=r;e[tot].s=0;int k=tot;if(l==r)return k;
    e[k].l=creat(l,(l+r)/2);e[k].r=creat((l+r)/2+1,r);return k;
}
int mdf(int root,int x){
    int k=++tot;e[k]=e[root];++e[k].s;if(e[root].a==x&&e[root].b==x)return k;
    int mid=(e[root].a+e[root].b)/2;if(x<=mid)e[k].l=mdf(e[root].l,x);else e[k].r=mdf(e[root].r,x);
    return k;
}
int que(int x,int y,int t){
	//printf("%d:%d:%d\n",x,y,t);
    if(e[x].a==e[x].b)return e[x].a; int k=e[e[x].l].s-e[e[y].l].s;
    if(t<=k)return que(e[x].l,e[y].l,t); else return que(e[x].r,e[y].r,t-k);
}
int ask(int x,int y,int t){
	//printf("%d:%d:%d:%d\n",x,y,t,e[x].s-e[y].s);
    if(e[x].a==e[x].b) return 0;int mid=e[x].a+e[x].b>>1;
    if(t<=mid)return ask(e[x].l,e[y].l,t);return ask(e[x].r,e[y].r,t)+e[e[x].l].s-e[e[y].l].s;
}
 
 
char s[N],asks[N];
int *x=rank,*y=rank2,*t;
bool cmp(int *y,int a1,int a2, int a3){return y[a1]==y[a2]&&y[a1+a3]==y[a2+a3];}
bool scmp(const int &a, const int &b){return x[a]<x[b];}
void calcsa(){
    int j=1,p=1,m=20010;
    rep(i,1,n) pai[i]=i,x[i]=s[i];
    sort(pai+1,pai+n+1,scmp);
    rep(i,1,n) sa[i]=pai[i+1];
    for(;j<=n;j*=2,m=p){
        p=1;rep(i,n-j,n-1) y[p++]=i;
        rep(i,1,n) if(sa[i]>j) y[p++]=sa[i]-j;
        rep(i,1,m) pai[i]=0;
        rep(i,1,n) ++pai[x[y[i]]];
        rep(i,2,m) pai[i]+=pai[i-1];
        dep(i,n,1) sa[pai[x[y[i]]]--]=y[i];
        t=x;x=y;y=t;p=2;x[sa[1]]=1;
        rep(i,2,n) x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
}
void calch(){
    int i,j,k=0;rep(i,0,n) rank[sa[i]]=i;
    for(i=1;i<=n;h[rank[i++]]=k) for(k?k--:0,j=sa[rank[i]-1];s[i+k]==s[j+k];k++);
}
int LOG[N];
inline int RMQ(const int &l,const int &r){
	if(l>r)return inf;
	int p=LOG[r-l+1];
	return min(rmq[l][p],rmq[r-(1<<p)+1][p]);
}
 
#include<ctime>
int main(){
	rep(i,1,20)LOG[1<<i]=i;
	rep(i,2,1000000)if(!LOG[i])LOG[i]=LOG[i-1];
	//rep(i,1,20)printf("%d %d\n",i,LOG[i]);return 0;
	fread(buf,1,20000000,stdin);
	while(*pp<'a'||*pp>'z')++pp;
	while(*pp>='a'&&*pp<='z')s[++n]=*pp,pp++;s[++n]=0;
	calcsa();calch();
	root[0]=creat(1,n);rep(i,1,n)root[i]=mdf(root[i-1],sa[i]);
	rep(i,1,n)rmq[i][0]=h[i];
	rep(i,1,20)rep(j,1,n){
		if(j+(1<<i-1)>n)break;
		rmq[j][i]=min(rmq[j][i-1],rmq[j+(1<<i-1)][i-1]);
	}
	h[0]=0;
	rep(i,1,n)h[i]=h[i-1]+(n-sa[i])-h[i];
	//printf("%d\n",clock());int ttt=clock();
	//rep(i,1,n)printf("%d %d %d\n",i,h[i],sa[i]);
	//return 0;
	read(C);rep(_,1,C){
		char ch;
		for(ch=*++pp;ch!='S'&&ch!='R';ch=*++pp);read(X);read(Y);
		if(ch=='S'){
			int Min=1,Max=n,pt,len;
			while(Min<Max){
				int mid=Min+Max>>1;if(h[mid]<X)Min=mid+1;else Max=mid;
			}pt=Min;Max=n;len=X-h[pt-1]+rmq[pt][0]-1;
			while(Min<Max){
				int mid=Min+Max+1>>1;if(RMQ(pt+1,mid)<len+1)Max=mid-1;else Min=mid;
			}int tmp=que(root[Min],root[pt-1],Y);
			//printf("%d %d %d\n",pt,Min,Y);
			printf("%d %d\n",tmp,tmp+len);
		}else{
			int Min=1,Max=rank[X],pt;ll num;
			while(Min<Max){
				int mid=Min+Max>>1;if(RMQ(mid+1,rank[X])<Y-X+1)Min=mid+1;else Max=mid;
			}pt=Min;Max=n;num=Y-X+1+h[pt-1]-rmq[pt][0];
			while(Min<Max){
				int mid=Min+Max+1>>1;if(RMQ(pt+1,mid)<Y-X+1)Max=mid-1;else Min=mid;
			}
			//printf("[%d,%d]\n",pt,Max);
			printf("%lld %d\n",num,ask(root[Min],root[pt-1],X)+1);
		}
	}
	//printf("%d\n",clock()-ttt);
	return 0;
} 
