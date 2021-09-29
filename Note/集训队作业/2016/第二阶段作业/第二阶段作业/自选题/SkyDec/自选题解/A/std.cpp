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
namespace gt{
	int val[110000];
	int big[110000];
	const int N=100000;
	void init(int p){
		val[0]=1;
		rep(i,1,N)val[i]=val[i-1]*1ll*p%P;
		big[0]=1;
		rep(i,1,N)big[i]=big[i-1]*1ll*val[N]%P;
	}
	inline int ask(int x){
		return big[x/N]*1ll*val[x%N]%P;
	}
};
int n,p,k;
int pre1[1100000];
int pre2[1100000];
inline int GetA(int i){
	int v1=(P+1-gt::ask(i))*1ll*Pow(gt::ask(i),P-2)%P;
	v1=Pow(v1,k-1);
	int v2=Pow(pre1[k-i],P-2);
	int v3=Pow(pre2[i-1],P-2);
	return (v1*1ll*v2%P)*1ll*v3%P;
}
int Q,x,y;
int main(){
	scanf("%d%d%d",&n,&x,&y);
	p=x*1ll*Pow(y,P-2)%P;
	gt::init(p);
	
	pre1[0]=1;
	rep(i,1,n)pre1[i]=(pre1[i-1]*1ll*(gt::ask(i)+P-1))%P;
	pre2[0]=1;
	rep(i,1,n)pre2[i]=(pre2[i-1]*1ll*(gt::ask(P-1-i)+P-1))%P;
	
	
	scanf("%d",&Q);
	while(Q--){
		read(k);
		if(k==0){
			printf("%d\n",Pow(n,P-2));
			continue;
		}
		int ans=0;
		rep(i,1,k){
			int A=GetA(i);
			A=A*1ll*gt::ask(P-1-i)%P;
			ans=(ans+A*1ll*(P+1-Pow(P+1-gt::ask(i),n-k)))%P;
		}
		ans=ans*1ll*gt::ask(((k*1ll*(k+1)/2)%(P-1)))%P;
		printf("%d\n",ans*1ll*Pow(n,P-2)%P);
	}
	return 0;
}






