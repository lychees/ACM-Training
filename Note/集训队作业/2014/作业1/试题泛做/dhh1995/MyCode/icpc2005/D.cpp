#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int T,Case,ans,res,n=52,a[15][55],b[55],f[55],g[55];
vector<int> o,p,v,w;
int diff(int *a,int *b)
{
	int res=0,c[55]; rep(i,n) c[a[i]]=b[i];
	rep(i,n) if (c[i]!=i) for (int x=c[i],y;x!=i;x=y) y=c[x],c[x]=x,++res;
	return res;
}
bool small()
{
	for (int i=res-1;i>=0;--i) if (w[i]!=p[i]) return w[i]<p[i];
	return 0;
}
void dfs(int i)
{
	int D=diff(a[i],b); if (D>i || v.size()+D>res) return;
	if (!i){if (v.size()==res?small():v.size()<res) res=v.size(),o=v,p=w; return;}
	int c[55]; rep(j,n) c[j]=b[j]; rep(j,n) b[g[j]]=c[j]; dfs(i-1);
	rep(j,n-1){
		swap(c[j],c[j+1]);
		if (diff(a[i],c)<=i-1){
			rep(k,n) b[g[k]]=c[k]; v.push_back(i),w.push_back(j);
			dfs(i-1); v.pop_back(),w.pop_back();
		}
		swap(c[j],c[j+1]);
	}
}
int main()
{
	rep(j,n) a[0][j]=j,f[j]=j<26?j*2+1:(j-26)*2,g[j]=j&1?j/2:j/2+26;
	rep(i,10) rep(j,n) a[i+1][f[j]]=a[i][j];
	for (scanf("%d",&T);T--;){
		rep(j,n) scanf("%d",b+j); rep(i,11) if ((res=diff(a[i],b))<=i){ans=i; break;}
		printf("Case %d\nNumber of shuffles = %d\n",++Case,ans);
		if (!res) puts("No error in any shuffle");
		else{
			++res,dfs(ans);
			for (int i=res-1;i>=0;--i)
				printf("Error in shuffle %d at location %d\n",o[i],p[i]);
		}
		puts("");
	}
	return 0;
}
