#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
#define pb push_back
typedef pair<int,int> pr;
const int N=105;
int Case,n,m,d,r1,r2,x[N],y[N],x1[N],x2[N],y1[N],y2[N];
vector<int> c1[N],c2[N]; bool b[N][N];
void work(int &n,int &m,int *u,int *v,vector<int> *c)
{
	int L=0,Y; rep(i,n) scanf("%d%d",x+i,y+i),u[L]=x[i],v[L++]=y[i]; x[n]=*x,y[n]=*y;
	sort(u,u+L),m=unique(u,u+L)-u,sort(v,v+L),L=unique(v,v+L)-v; rep(i,L) c[i].clear();
	rep(i,n) if (y[i]==y[i+1]) Y=lower_bound(v,v+L,y[i])-v,c[Y].pb(x[i]),c[Y].pb(x[i+1]);
	n=L-1;
	rep(i,n){
		sort(c[i].begin(),c[i].end());
		if (i){
			rep(j,c[i-1].size()) c[i].pb(c[i-1][j]); sort(c[i].begin(),c[i].end());
			rep(j,c[i].size()-1) if (c[i][j]==c[i][j+1])
				c[i].erase(c[i].begin()+j,c[i].begin()+j+2),--j;
		}
	}
	rep(i,n) v[i]=v[i+1]-v[i];
}
bool cover(vector<int> &c1,vector<int> &c2)
{
	int j=0;
	rep(i,c1.size()){
		while (j<c2.size() && c2[j+1]+d<c1[i+1]) j+=2;
		if (j>=c2.size() || c2[j]+d>c1[i++]) return 0;
	}
	return 1;
}
bool check(int i,int h1,int j,int h2,int d)
{
	if (!h1) h1=y1[i+=d]; if (!h2) h2=y2[j+=d];
	if (d>0?i>=n:i<0) return 1; if (d>0?j>=m:j<0) return 0;
	if (!b[i][j]) return 0; int h=min(h1,h2); return check(i,h1-h,j,h2-h,d);
}
bool solve()
{
	rep(l1,r1) rep(l2,r2){
		d=x1[l1]-x2[l2]; rep(i,n) rep(j,m) b[i][j]=cover(c1[i],c2[j]);
		rep(i,n+1) rep(j,m+1) if (check(i-1,0,j-1,0,1) && check(i,0,j,0,-1)) return 1;
	}
	return 0;
}
int main()
{
	while (scanf("%d%d",&n,&m),n||m)
		work(n,r1,x1,y1,c1),work(m,r2,x2,y2,c2),printf("Hole %d: %s\n",++Case,solve()?"Yes":"No");
	return 0;
}
