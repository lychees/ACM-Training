#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<set>
#include<ctime>
#include<map>
#include<vector>
#define rep(i,j,k) for(register int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(register int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double db;
const int P=1000000007;
inline int Pow(int a,int b){
	int c=1;
	for(;b;b>>=1,a=a*1ll*a%P)if(b&1)c=c*1ll*a%P;
	return c;
}
inline void read(int &x){
	x=0;char p=getchar();
	while(!(p<='9'&&p>='0'))p=getchar();
	while(p<='9'&&p>='0')x*=10,x+=p-48,p=getchar();
}
const int N=1010000;
inline void add(int &x,int y){x+=y;if(x>=P)x-=P;}
int n=1000000;
int f[N];
int g[N];
int miu[N];
int pr[N];
int ans[N];
int cc[N];
int cb[N];
int main(){
	int d1=clock();
	for(int i=2;i<=n;i++)if(!pr[i]){
		for(int j=i;j<=n;j+=i)if(!pr[j])pr[j]=i;
	}
	cb[1]=1;
	rep(i,2,n){
		int x=pr[i];
		int ci=0;
		int q=i;
		while(q%x==0){
			q/=x;
			ci++;
		}
		ci*=2;
		int v=(Pow(pr[i],ci+1)-1)*1ll*Pow(pr[i]-1,P-2)%P;
		cb[i]=cb[q]*1ll*v%P;
	}
	//printf("Time=%d\n",clock()-d1);
	miu[1]=1;
	rep(i,2,n){
		if((i/pr[i])%pr[i]==0)miu[i]=0;
		else{
			miu[i]=P-miu[i/pr[i]];
			if(miu[i]>=P)miu[i]-=P;
		}
	}
	//printf("Time=%d\n",clock()-d1);
	rep(i,1,n)for(int j=1;j<=n/i;j++){
		int l=i*j;
		int r=i*(j+1)-1;if(r>n)r=n;
		int v=i*1ll*j%P;
		add(g[l],v);
		add(g[r+1],(P-v)%P);
	}
	rep(i,1,n)rep(j,1,n/i)add(cc[i*j],i);
	rep(i,1,n)add(g[i],g[i-1]);
	//printf("Time=%d\n",clock()-d1);
	
	for(int i=1;i<=n;i++){
		int v=miu[i]*1ll*i%P;
		for(int j=1;j<=n/i;j++){
			int v2=cc[j]*1ll*g[j]%P;
			v2=v*1ll*v2%P;
			add(f[i*j],v2);
		}
	}
	//printf("Time=%d\n",clock()-d1);
	rep(i,1,n)f[i]=f[i]*1ll*i%P;
	rep(i,1,n){
		ans[i]=ans[i-1];
		add(ans[i],f[i]);
		add(ans[i],f[i]);
		add(ans[i],(P-(i*1ll*cb[i]%P))%P);
	}
	//printf("Time=%d\n",clock()-d1);
	int Q;scanf("%d",&Q);
	rep(Cas,1,Q){
		read(n);
		printf("Case #%d: %d\n",Cas,ans[n]);
	}
	return 0;
}