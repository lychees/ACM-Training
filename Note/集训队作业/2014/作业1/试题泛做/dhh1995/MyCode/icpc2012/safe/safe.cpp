#include<cstdio>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
#define pb push_back
#define mk make_pair
#define X first
#define Y second
#define tree int t,int l,int r
#define left t*2,l,mid
#define right t*2+1,mid+1,r
#define M int mid=l+r>>1
const int N=1000005;
typedef pair<int,int> pr;
typedef vector<pair<int,pr> > seq;
set<pr> a[N],b[N]; seq f1,g1,f2,g2; int Case,n,m,R,C,x,y,ll,rr,c[N]; long long ans;
int get(int x){int res=0; for (;x;x-=x&-x) res+=c[x]; return res;}
void add(int x,int v){for (;x<=C;x+=x&-x) c[x]+=v;}
void ins(int side){scanf("%d%d",&x,&y),a[x].insert(mk(y,side)),b[y].insert(mk(x,side));}
bool track(int x,int y,int d,seq &f,seq &g)
{
	f.clear(),g.clear(); set<pr> :: iterator it;
	for (;;){
		if (d&1){
			if (d==1){
				it=b[y].upper_bound(mk(x,1)); f.pb(mk(x+1,mk(y,1)));
				if (it==b[y].end()) return f.pb(mk(R+1,mk(y,-1))),0;
				f.pb(mk(it->X,mk(y,-1))),x=it->X,d=it->Y?2:0;
			}else{
				it=b[y].lower_bound(mk(x,0)); f.pb(mk(x,mk(y,-1)));
				if (it==b[y].begin()) return f.pb(mk(1,mk(y,1))),0; --it;
				f.pb(mk(it->X+1,mk(y,1))),x=it->X,d=it->Y?0:2;
			}
		}else{
			if (d==0){
				it=a[x].upper_bound(mk(y,1));
				if (it==a[x].end()) return g.pb(mk(x,mk(y+1,C))),x==R;
				g.pb(mk(x,mk(y+1,it->X-1))),y=it->X,d=it->Y?3:1;
			}else{
				it=a[x].lower_bound(mk(y,0));
				if (it==a[x].begin()) return g.pb(mk(x,mk(1,y-1))),0; --it;
				g.pb(mk(x,mk(it->X+1,y-1))),y=it->X,d=it->Y?1:3;
			}
		}
	}
}
void work(seq &f,seq &g)
{
	sort(f.begin(),f.end()),sort(g.begin(),g.end());
	int m=f.size(),n=g.size(),j=0;
	rep(i,n){
		while (j<m && f[j].X<=g[i].X) add(f[j].Y.X,f[j].Y.Y),++j;
		ll=g[i].Y.X,rr=g[i].Y.Y; int res=get(rr)-get(ll-1); ans+=res;
		if (g[i].X<x && res){
			x=g[i].X,y=ll;
			for (int j=20;j>=0;--j)
				if (y+(1<<j)<=rr && !(get(y-1+(1<<j))-get(y-1))) y+=1<<j;
			}
		}
	while (j<m) add(f[j].Y.X,f[j].Y.Y),++j;
}
int main()
{
	freopen("safe.in","r",stdin);
	freopen("safe.out","w",stdout);
	while (scanf("%d%d%d%d",&R,&C,&n,&m)!=EOF){
		rep(i,R+1) a[i].clear(); rep(j,C+1) b[j].clear();
		rep(i,n+m) ins(i<n); printf("Case %d: ",++Case);
		if (track(1,0,0,f1,g1)){puts("0"); continue;} track(R,C+1,2,f2,g2);
		ans=0,x=R+1,work(f1,g2),work(f2,g1);
		if (ans) printf("%I64d %d %d\n",ans,x,y); else puts("impossible");
	}
	return 0;
}
