#include<bits/stdc++.h>
#define int64 long long
#define mk make_pair
#define pb push_back
#define fi first
#define se second
#define sqr(x) (x)*(x)
#define rep(i,x,y) for(int i=x;i<=y;++i)
#define VI vector<int>
#define VS vector<string>
#define PII pair<int,int>
#define PDD pair<double,double>
#define VPII vector< PII >
#define N 1010000
//ans=968697378
using namespace std;
const double pi=acos(-1);
const int mo=1e9,p1=12000017,p2=137;
int64 Hash[12100000];
int p[12100000];
int F[N],S[N],bo[N];
int Find(int64 n){
	int x=n%p1,y=n%p2+1;
	for(;;){
		if(!Hash[x] || Hash[x]==n+1)return x;
		x+=y;
		if(x>=p1)x-=p1;
	}
}
int64 Sum(int64 x,int64 y){
	int64 l=x+y,r=y-x+1;
	if(l&1)r/=2;
	else l/=2;
	return l%mo*(r%mo)%mo;
}
int calc(int64 n){
	if(n<1000000)return S[n];
	if(!n)return 0;
	int id=Find(n);
	if(Hash[id])return p[id];
	Hash[id]=n+1;
	int64 x=2,ans=1;
	while(x<=n){
		int64 y=n/x,z=n/y;
		ans=(ans-Sum(x,z)*calc(y))%mo;
		x=z+1;
	}
	return p[id]=(ans+mo)%mo;
}
int f(int64 n){
	if(n<1000000)return F[n];
	int64 x=1;
	int ans=0;
	while(x<=n){
		int64 y=n/x,z=n/y;
		ans=(ans+Sum(x,z)*y)%mo;
		x=z+1;
	}
	return ans;
}
int work(int64 n){
	int64 x=1;
	int ans=0;
	while(x<=n){
		int64 y=n/x,z=n/y,tmp=f(y);
		ans=(ans+1ll*(calc(z)-calc(x-1))*tmp%mo*tmp)%mo;
		x=z+1;
	}
	return (ans+mo)%mo;
}
void prep(){
	int n=1000000;
	rep(i,1,n)S[i]=1;
	rep(i,2,n){
		if(!bo[i]){
			for(int j=i;j<=n;j+=i)S[j]*=-1,bo[j]=1;
			for(int64 j=1ll*i*i;j<=n;j+=i*i)S[j]=0;
		}
		for(int j=i;j<=n;j+=i)F[j]+=i;
	}
	rep(i,1,n){
		F[i]=(1+F[i]+F[i-1])%mo;
		S[i]=(S[i]*i+S[i-1])%mo;
	}
}
int main(){//freopen("1.out","w",stdout);
	prep();
	printf("%d\n",work(2000000000ll));
	cout<<clock()<<endl;
}
