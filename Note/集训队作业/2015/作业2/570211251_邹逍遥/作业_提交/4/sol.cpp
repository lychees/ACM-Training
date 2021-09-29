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
template<class T> inline void read(T&x){bool fu=0;char c;for(c=getchar();c<=32;c=getchar());if(c=='-')fu=1,c=getchar();for(x=0;c>32;c=getchar())x=x*10+c-'0';if(fu)x=-x;};
template<class T> inline void read(T&x,T&y){read(x);read(y);}
template<class T> inline void read(T&x,T&y,T&z){read(x);read(y);read(z);}
template<class T> inline void read(T&x,T&y,T&z,T&q){read(x);read(y);read(z);read(q);}
const int DX[]={1,0,-1,0},DY[]={0,1,0,-1};
ll powmod(ll a,ll b) {ll res=1;a%=mod;for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll powmod(ll a,ll b,ll mod) {ll res=1;a%=mod;for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
//*******************************************
 
const int N=333333,M=11111111;
int l,m,n,t,C,pt[N],tot,tx,ty;
char s[9];
map<int,int>Mx,My;
struct zcc{int l,r,v;}a[M];
struct qeury{int ty,x1,y1,x2,y2,p,ans;}q[N];
void mod2(int &x,int p,int v,int l,int r){
	if(!x)x=++tot,a[x].v=a[x].l=a[x].r=0;a[x].v+=v;
	if(l==r)return;int mid=l+r>>1;
	if(p<=mid)mod2(a[x].l,p,v,l,mid);else mod2(a[x].r,p,v,mid+1,r);
}
void modi(int x,int y,int v){for(int i=x;i<=tx;i+=i&-i)mod2(i,y,v,1,ty);}
int ask2(int &x,int p,int l,int r){
	if(!x)x=++tot,a[x].v=a[x].l=a[x].r=0;
	if(l==r)return a[x].v;int mid=l+r>>1;
	if(p<=mid)return ask2(a[x].l,p,l,mid);else return ask2(a[x].r,p,mid+1,r)+a[a[x].l].v;
}
int ask(int x,int y){int ans=0;for(int i=x;i;i-=i&-i)ans+=ask2(i,y,1,ty);return ans;}
struct biubiu{
	int a[N];
	void modi(int x,int v){for(int i=x;i<=tx;i+=i&-i)a[i]+=v;}
	int ask(int x){int ans=0;for(int i=x;i;i-=i&-i)ans+=a[i];return ans;}
}T;
int main()
{
	scanf("%d",&C);rep(i,1,C){
		scanf("%s",s);q[i].ans=q[i-1].ans;
		if(s[0]=='D')scanf("%d",&t),q[i]=q[pt[t]],q[i].ty=0,q[i].ans=q[i-1].ans-1;
		if(s[0]=='I')q[i].ty=1,scanf("%d%d%d%d",&q[i].x1,&q[i].y1,&q[i].x2,&q[i].y2),pt[++tot]=i,q[i].ans++;
		if(s[0]=='Q')q[i].ty=2,scanf("%d%d%d%d",&q[i].x1,&q[i].y1,&q[i].x2,&q[i].y2);
		Mx[q[i].x1]=Mx[q[i].x2]=1;My[q[i].y1]=My[q[i].y2]=1;
	}ALL(it,Mx)it->Y=++tx;ALL(it,My)it->Y=++ty;tx++;ty++;tx=max(tx,ty);ty=tx;
	rep(i,1,C)q[i].x1=Mx[q[i].x1],q[i].x2=Mx[q[i].x2],q[i].y1=My[q[i].y1],q[i].y2=My[q[i].y2];
	rep(_,1,4){
		//rep(i,1,C)printf("%d %d %d %d\n",q[i].x1,q[i].y1,q[i].x2,q[i].y2);
		//rep(i,1,C)printf("%d ",q[i].ans);puts("");puts("");
		tot=0;rep(i,1,tx)a[++tot].l=a[tot].r=a[tot].v=0;
		rep(i,1,C){
			if(q[i].ty==0)modi(q[i].x2,q[i].y2,-1);
			if(q[i].ty==1)modi(q[i].x2,q[i].y2,1);
			if(q[i].ty==2)if(q[i].x1-1&&q[i].y1-1)q[i].ans+=ask(q[i].x1-1,q[i].y1-1);
		}
		CLR(T.a);
		rep(i,1,C){
			if(q[i].ty==0)T.modi(q[i].x2,-1);
			if(q[i].ty==1)T.modi(q[i].x2,1);
			if(q[i].ty==2)if(q[i].x1-1)q[i].ans-=T.ask(q[i].x1-1);
		}
		rep(i,1,C){
			int X1=ty-q[i].y2,X2=ty-q[i].y1;q[i].y2=q[i].x2;q[i].y1=q[i].x1;
			q[i].x1=X1;q[i].x2=X2;
		}
	}
	rep(i,1,C)if(q[i].ty==2)printf("%d\n",q[i].ans);
	
	return 0;
} 
