#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double db;
const int N=55;
const int P=1000000007;
inline int Pow(int a,int b){
	int c=1;
	for(;b;b>>=1,a=a*1ll*a%P)if(b&1)c=c*1ll*a%P;
	return c;
}
inline void add(int &a,int b){a+=b;if(a>=P)a-=P;}
int n;int a[N];
int fac[1005];
int inv[1005];
int inv_w[1005];
int m;
int s[N];
int f[2][N][1005];
int g[1005];
int C(int a,int b){
	int ret=fac[a]*1ll*inv[b]%P;
	return ret*1ll*inv[a-b]%P;
}
int Main(){
	m=0;rep(i,1,n)m+=a[i];
	rep(i,1,n)s[i]=a[i]+s[i-1];
	
	fac[0]=1;
	rep(i,1,m)fac[i]=fac[i-1]*1ll*i%P;
	inv[m]=Pow(fac[m],P-2);
	per(i,m-1,0)inv[i]=inv[i+1]*1ll*(i+1)%P;
	rep(i,1,m)inv_w[i]=inv[i]*1ll*fac[i-1]%P;
	
	int now=0;
	rep(i,a[1],m)
	f[now][1][i-a[1]]=C(i-1,a[1]-1);
	
	rep(i,2,n){
		memset(f[now^1],0,sizeof f[now^1]);
		rep(j,1,i-1)rep(k,0,m){
			register int val=f[now][j][k];
			if(!val)continue;
			rep(d,1,a[i])if(m-k-s[i-1]>=d)if(k>=a[i]-d)
			add(f[now^1][j][k-(a[i]-d)],(val*1ll*C(m-k-s[i-1],d)%P)*1ll*C(k,a[i]-d)%P);
		}
	
		
		memset(g,0,sizeof g);
		
		rep(j,1,i-1)rep(k,0,m)add(g[k],f[now][j][k]);
		
		per(k,m,0)add(g[k],g[k+1]);
		
		rep(k,a[i],m)
		add(f[now^1][i][k-a[i]],g[k]*1ll*C(k-1,a[i]-1)%P);
		now^=1;
	}
	int ans=0;
	rep(i,1,n){
		int ret=f[now][i][0];
		rep(j,1,n)ret=ret*1ll*fac[a[j]]%P;
		rep(j,1,n)if(i^j)ret=ret*1ll*inv_w[a[j]]%P;
		add(ans,ret);
	}
	return ans;
}
class Permutant{
	public:
	int counthis(vector<int> _a){
		n=_a.size();
		rep(i,1,n)a[i]=_a[i-1];
		return Main();
	}
};
int main(){
	n=20;
	rep(i,1,n)a[i]=50;
	printf("%d\n",Main());
	return 0;
}


