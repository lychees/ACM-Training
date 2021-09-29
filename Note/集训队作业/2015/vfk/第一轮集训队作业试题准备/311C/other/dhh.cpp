#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#define pr pair<int,int>
#define mk make_pair
#define rep(i,n) for (int i=1;i<=n;i++)
#define N 100005
priority_queue<pr > H;
int n,m,k,type,x,y,L,ed[25],f[N*20],c[N];
long long d[N],a[N],data[25],z; bool b[N];
int main()
{
	scanf("%*lld%d%d%d",&n,&m,&k); memset(d,1,sizeof(d)),d[1]=0;
	rep(i,n) {scanf("%lld%d",a+i,c+i); if (a[i]%k==1) H.push(mk(c[i],-i));}
	while (m--){
		scanf("%d",&type);
		while (type==3){
			if (H.empty()) {puts("0"); break;}
			pr o=H.top(); H.pop(); x=-o.second,y=o.first;
			if (c[x]==y) {printf("%d\n",y),c[x]=0; break;}
			}
		if (type==2){
			scanf("%d%d",&x,&y),c[x]-=y;
			if (d[a[x]%k]<=a[x]/k) H.push(mk(c[x],-x));
			}
		if (type==1){
			scanf("%lld",&z); data[++L]=z/k,ed[L]=z%k;			
			int h=0,t=0; rep(i,k) f[++t]=i-1;
			while (h<t){
				x=f[++h],b[x]=0;
				rep(i,L){
					y=x+ed[i],z=d[x]+data[i]; if (y>=k) y-=k,z++;
					if (z<d[y]) {d[y]=z; if (!b[y]) b[y]=1,f[++t]=y;}
					}
				}
			while (!H.empty()) H.pop();
			rep(i,n){
				if (d[a[i]%k]<=a[i]/k && c[i]) H.push(mk(c[i],-i));
				}
			}
		}
	return 0;
}
