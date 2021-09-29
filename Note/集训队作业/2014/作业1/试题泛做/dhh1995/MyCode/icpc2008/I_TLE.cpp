#include<cstdio>
#include<string>
#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
string a[15]; bool b[15]; long long ans,z,f[26][1<<10][105];
int Case,n,m,S,tot,c[105][27],d[105],q[105];
vector<string> res,tmp,g[1<<10][105],g1[1<<10][105];
void ins(int i,string s)
{
	int x=1,y;
	rep(j,s.size()){
		y=s[j]-96;
		if (!c[x][y]) c[x][y]=++tot;
		x=c[x][y];
	}
	d[x]|=1<<i;
}
void bfs()
{
	int h=0,t=1; q[1]=1;
	while (h<t){
		int x=q[++h],y;
		rep(i,27) if (i) if (y=c[x][i]) *c[y]=c[*c[x]][i],q[++t]=y; else c[x][i]=c[*c[x]][i];
	}
}
int main()
{
	freopen("I.in","r",stdin);
	freopen("I.out","w",stdout);
	while (scanf("%d%d",&n,&m)!=EOF && n){
		rep(x,tot){d[x]=0; rep(i,27) c[x][i]=0;} ans=S=0,tot=1; rep(i,27) c[0][i]=1;
		rep(i,m) cin>>a[i],b[i]=1;
		rep(i,m) if (b[i]) rep(j,m) if (b[j] && i!=j) if (a[i].find(a[j])!=-1) b[j]=0;
		rep(i,m) if (b[i]) ins(i,a[i]); else S|=1<<i; 
		++tot,bfs(); rep(i,n+1) rep(j,1<<m) rep(x,tot) f[i][j][x]=0; f[0][S][1]=1;
//		rep(x,tot){rep(i,27) printf("%d ",c[x][i]); puts("");}
		rep(i,n) rep(j,1<<m) rep(x,tot) if (z=f[i][j][x])
			rep(k,26){int y=c[x][k+1]; f[i+1][j|d[y]][y]+=z;}
		rep(x,tot) ans+=f[n][(1<<m)-1][x];
		printf("%lld\n",ans); //printf("Case %d: %lld suspects\n",++Case,ans);
		if (ans<=42){
			rep(j,1<<m) rep(x,tot) g[j][x].clear(); g[S][1].push_back("");
			rep(i,n){
				rep(j,1<<m) rep(x,tot) if ((tmp=g[j][x]).size()){
					g[j][x].clear();
					if (tmp.size()<42) rep(k,26){
						int y=c[x][k+1];
						rep(l,tmp.size()) g1[j|d[y]][y].push_back(tmp[l]+char(k+97));
					}
				}
				rep(j,1<<m) rep(x,tot) g[j][x]=g1[j][x],g1[j][x].clear();
			}
			res.clear();
			rep(x,tot) if ((tmp=g[(1<<m)-1][x]).size())
				rep(i,tmp.size()) res.push_back(tmp[i]);
			sort(res.begin(),res.end()); rep(i,res.size()) cout<<res[i]<<endl;
		}
	}
	return 0;
}
