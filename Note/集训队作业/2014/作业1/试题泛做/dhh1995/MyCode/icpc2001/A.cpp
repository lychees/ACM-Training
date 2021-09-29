#include<cstdio>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const int N=35;
int n,m,x,y,z,id,sum,a[N][N],p[N],q[N]; pair<int,int> o[N];
int main()
{
	while (scanf("%d",&n),n){
		rep(i,n) rep(j,n) a[i][j]=0;
		rep(i,n){scanf("%d%d",&x,&m); while (m--) scanf("%d%d",&y,&z),a[x][y]=z;}
		m=0;
		while (scanf("%d",&id),id){
			sum=0; rep(i,n) scanf("%d",p+i); rep(i,n) scanf("%d",q+i);
			rep(i,n) rep(j,n) sum+=a[p[i]][q[j]]*(abs(i-j)+1);
			o[++m]=make_pair(sum,id);
		}
		sort(o+1,o+m+1);
		puts("Configuration Load");
		rep(i,m) printf("%5d         %d\n",o[i].second,o[i].first);
	}
	return 0;
}
