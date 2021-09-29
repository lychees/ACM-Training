#include<bits/stdc++.h>
#define int64 long long
#define sqr(x) (x)*(x)
#define mk make_pair
#define pb push_back
#define fi first
#define se second
#define rep(i,x,y) for(int i=x;i<=y;++i)
#define VI vector<int>
#define VI64 vector<int64>
#define VS vector<string>
#define PII pair<int,int>
#define PDD pair<double,double>
#define VPII vector< PII >
#define SZ(x) ((int)(x).size())
using namespace std;
const double pi=acos(-1);
const int mo=900000011;
const int64 inf=8000000000000000000ll;
int comb[210][210],inv_[210],bern[210][210],S;
int64 fast[33][33],f[410][33][33],g[33][33];
int Pow(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=1ll*res*x%mo;
		x=1ll*x*x%mo;
		y/=2;
	}
	return res;
}
void Plus(int64 &x,int64 y){
	x+=y;
	if(x>=inf || x<=-inf)x%=mo;
}
int64 Div(int64 n,int64 a,int64 c,int64 b){
	int64 u=((long double)n*a+c)/b;
	int64 v=n*a+c-u*b;
	int cnt=0;
	while(v<0){
		v+=b,u--;
		assert(cnt++<1000);
	}
	while(v>=b){
		v-=b,u++;
		assert(cnt++<1000);
	}
	return u;
}
int inv(int x){
	if(x<0)return -inv_[-x];
	return inv_[x];
}
int poly_val(int *a,int n,int64 x){
	int ans=0,y=1;
	x%=mo;
	rep(i,0,n){
		ans=(ans+1ll*a[i]*y)%mo;
		y=1ll*y*x%mo;
	}
	return ans;
}
void poly_mul(int *a,int n,int x,int y){
	for(int i=n;i>=0;--i){
		a[i+1]=(a[i+1]+1ll*a[i]*x)%mo;
		a[i]=1ll*a[i]*y%mo;
	}
}
void poly_div(int *a,int n,int x,int y){
	int t=a[n];
	a[n]=0;
	for(int i=n-1;i>=0;--i){
		int tmp=a[i];
		a[i]=t/x;
		t=(tmp-1ll*a[i]*y)%mo;
	}
	assert(t==0);
}
void poly(int *a,int n){
	int tmp[n+3],ans[n+3];
	memset(tmp,0,sizeof(tmp));
	memset(ans,0,sizeof(ans));
	tmp[0]=1;
	rep(i,0,n)poly_mul(tmp,i+1,1,-i);
	rep(i,0,n){
		poly_div(tmp,n+1,1,-i);
		int Inv=1;
		rep(j,0,n)if(j!=i)Inv=1ll*Inv*inv(i-j)%mo;
		rep(j,0,n)ans[j]=(ans[j]+1ll*tmp[j]*Inv%mo*a[i])%mo;
		poly_mul(tmp,n+1,1,-i);
	}
	rep(i,0,n)a[i]=ans[i];
}
void prep(){
	rep(i,0,200)
		rep(j,0,i)comb[i][j]=!j?1:(comb[i-1][j-1]+comb[i-1][j])%mo;
	rep(i,0,200)inv_[i]=Pow(i,mo-2);
	rep(j,0,30){
		rep(i,0,j+1)bern[j][i]=((!i?0:bern[j][i-1])+Pow(i,j))%mo;
		poly(bern[j],j+1);
	}
}
void work(int dep,int64 N,int64 A,int64 B,int64 C){
	rep(i,0,S)
		rep(j,0,S)f[dep][i][j]=0;
//	if(N<0)return;
	if(A>=B || abs(C)>=B){
		work(dep+1,N,A%B,B,C%B);
		int PowA[32],PowC[32];
		PowA[0]=PowC[0]=1;
		rep(i,1,S){
			PowA[i]=1ll*PowA[i-1]*((A/B)%mo)%mo;
			PowC[i]=1ll*PowC[i-1]*((C/B)%mo)%mo;
		}
		rep(v,0,S)rep(p2,0,v)fast[v][p2]=1ll*comb[v][p2]*PowC[p2]%mo;
		rep(u,0,S)
			rep(v,0,S-u){
				g[u][v]=0;
				rep(p2,0,v)Plus(g[u][v],fast[v][p2]*f[dep+1][u][v-p2]);
				g[u][v]%=mo;
			}
		rep(k,0,S)rep(p1,0,k)fast[k][p1]=1ll*PowA[p1]*comb[k][p1]%mo;
		rep(j,0,S)
			rep(k,0,S-j){
				int64 ans=0;
				rep(p1,0,k)Plus(ans,fast[k][p1]*g[j+p1][k-p1]);
				f[dep][j][k]=ans%mo;
			}
		return;
	}else if(!A){
		rep(j,0,S){
			f[dep][j][0]=poly_val(bern[j],j+1,N);
			rep(k,1,S-j)f[dep][j][k]=0;
		}
		return;
	}else{
		int64 M=Div(N,A,C,B);
		work(dep+1,M-1,B,A,A-1-C+B);
		int tmp[33];
		rep(i,0,S+1)tmp[i]=Pow((A-1-C)/A,i);
		rep(i,0,S+1)
			rep(k,1,S+1-i){
				g[i][k]=0;
				rep(u,0,k-1)Plus(g[i][k],1ll*comb[k][u]*(f[dep+1][u][i]));
				g[i][k]%=mo;
			}
		rep(j,0,S){
			int con=poly_val(bern[j],j+1,N);
			rep(k,0,S-j){
				if(!k){
					f[dep][j][k]=con;
					continue;
				}
				int64 ans=0;
				rep(i,0,j+1){
					int c=-bern[j][i];
					if(i==0)c=(c+con)%mo;
					if(i==j)c++;
					Plus(ans,c*g[i][k]);
				}
				f[dep][j][k]=ans%mo;
			}
		}
		return;
	}
}
int main(){
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	prep();
	int T,a[120],b[120];
	int64 N,A,B,K,L;
	for(scanf("%d",&T);T--;){
		scanf("%lld%lld%lld%lld%lld",&N,&A,&B,&K,&L);
		S=K+L+1;
		memset(a,0,sizeof(a));
		a[0]=1;
		rep(i,0,L-1)poly_mul(a,i+1,-1,(N-i)%mo);
		memset(b,0,sizeof(b));
		b[0]=1;
		rep(i,0,K)poly_mul(b,i+1,1,1-i);
		
		work(0,N,A,B,0);
		int ans=0;
		rep(j,0,L)
			rep(k,0,K+1)ans=(ans+1ll*a[j]*b[k]%mo*f[0][j][k])%mo;
		rep(i,1,L)ans=1ll*ans*inv(i)%mo;
		rep(i,1,K+1)ans=1ll*ans*inv(i)%mo;
		printf("%d\n",(ans+mo)%mo);
	}
//	printf("%d\n",clock());
} 
