#include<bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;++i)
#define re(i,a,b) for (int i=a;i<b;++i)
#define dep(i,a,b) for (int i=a;i>=b;--i)
template<class T> inline void read(T&x){char c;bool fu=0;for(c=getchar();c<=32;c=getchar());if(c=='-')fu=1,c=getchar();for(x=0;c>32;c=getchar())x=x*10+c-'0';if(fu)x*=-1;}
template<class T> inline void read(T&x,T&y){read(x);read(y);}
template<class T> inline void read(T&x,T&y,T&z) {read(x,y);read(z);}
using namespace std;
typedef long long ll;
const int maxn=65536;
const int P=104857601,G=3;
int a[maxn],b[maxn],c[maxn];
int r[maxn],N,M,k;

int pw(int a,int b){int an=1;for(;b;b>>=1){if(b&1)an=1ll*an*a%P;a=1ll*a*a%P;}return an;}
void rev(int *a,int m) {
	r[0]=0;
	re(i,1,1<<m)r[i]=(r[i>>1]>>1)|((i&1)<<(m-1));
	re(i,0,1<<m)if(r[i]>i)swap(a[r[i]],a[i]);
}
int p[maxn+1],pm[maxn+1],pv[maxn+1];
void prepare(){
	p[0]=1;int gg=pw(G,(P-1)/maxn);
	rep(i,1,maxn)p[i]=1ll*gg*p[i-1]%P;
	pv[0]=1;gg=pw(gg,P-2);
	rep(i,1,maxn)pv[i]=1ll*gg*pv[i-1]%P;
	rep(i,0,35)pm[i]=pw(1<<i,P-2);
}
void dft(int *a,int m,bool inv=0){
	rev(a,m);
	re(i,0,m) {
		int fc=maxn>>(i+1);
		//ll c=pw(G,(P-1)>>(i+1));
	//	if(inv)c=pw(c,P-2);
		for(int j=0;j<1<<m;j+=1<<i+1){
			int w=1;
			re(k,j,j+(1<<i)){
				int w=(inv==0)?p[fc*(k-j)]:pv[fc*(k-j)];
				int u=a[k],v=a[k+(1<<i)];
				a[k]=(u+1ll*w*v%P),a[k+(1<<i)]=(u-1ll*w*v%P);
				if(a[k]>P)a[k]-=P;
				if(a[k+(1<<i)]<0)a[k+(1<<i)]+=P;
			//	w=1ll*w*c%P;
			}
		}
	}
	if(inv){
		int d=pm[m];
		re(i,0,1<<m)a[i]=1ll*a[i]*d%P;
	}
}

void polymul(int *a,int *b,int m) {
	dft(a,m);dft(b,m);
	re(i,0,1<<m)a[i]=1ll*a[i]*b[i]%P;
	dft(a,m,-1);
}
int A[maxn],X[maxn];
void polyinv(int *a,int *b) { //b_r -> c
	b[0]=pw(a[0],P-2);
	for(int m=0;(1<<m)<N;++m){ // get 1<<m+1 from 1<<m
		int n=1<<m;
		re(i,0,n)X[i]=b[i];
		re(i,n,n<<2)X[i]=0;
		re(i,n<<1,n<<2)A[i]=0;
		re(i,0,n<<1)A[i]=a[i];
		dft(X,m+2);dft(A,m+2);
		re(i,0,n<<2){
			b[i]=(2ll-1ll*A[i]*X[i]%P)*X[i]%P;
			if(b[i]<0)b[i]+=P;
		}
		dft(b,m+2,-1);
	}
	re(i,N,N<<1)b[i]=0;
}
int dc[maxn],db_r[maxn],b_r[maxn];
//dfted b -> db
void polymod(int *a){ 
	re(i,0,N<<1)A[i]=a[i];reverse(A,A+2*k-2+1);
	rep(i,0,2*k-2)a[i]=A[i];
	re(i,k,N<<1)a[i]=0;
//	int t=clock();
	
//	rep(i,0,N<<1)printf("%d ",a[i]);puts("");
	//inv(b,c);
	dft(a,M+1);
	//	printf("%d\n",clock()-t);
	//dft(c,M+1);
	re(i,0,N<<1)a[i]=1ll*a[i]*dc[i]%P;// a-> dfted d_r
	dft(a,M+1,-1);re(i,k-1,N<<1)a[i]=0;// a-> real d_r
	dft(a,M+1);
	re(i,0,N<<1)a[i]=1ll*a[i]*db_r[i]%P;
	dft(a,M+1,-1); // real b*d
	rep(i,0,2*k-2){
	//	printf("%d ",A[i]);
		a[i]=(A[i]-a[i])%P;
		if(a[i]<0)a[i]+=P;
	}
	//puts("");
	//rep(i,0,2*k-2)printf("%d ",a[i]);puts("");
	reverse(a,a+2*k-2+1);
	//rep(i,0,2*k-2)printf("%d ",a[i]);puts("");
	re(i,k,N<<1)a[i]=0;
}

int cur[maxn],tmp[maxn];
void polypow(int *ans,ll n){
	//tmp[] will be dfted
	// ans=1 -> __G0=1
	// cur=G1 -> __G1=1 
	/*rep(i,1,n-1){
		re(i,0,N<<1)tmp[i]=cur[i];
		polymul(ans,tmp,M+1);
		polymod(ans);
	}*/
	ans[0]=1;cur[1]=1;//the real
	for (;n;n>>=1){
		if(n&1){
			re(i,0,N<<1)tmp[i]=cur[i];
			
			polymul(ans,tmp,M+1);
			//re(i,0,N<<1)printf("%d ",ans[i]);puts("");
			polymod(ans);
		}
		re(i,0,N<<1)tmp[i]=cur[i];
		polymul(cur,tmp,M+1);
		polymod(cur);
	}
}
int Ans[maxn];ll n;
int main() {
	prepare();
	read(k);read(n);n--;
	M=0;while((1<<M)<=k)++M;
	N=1<<M;
	rep(i,1,k)read(a[i]);
	rep(i,1,k)read(c[i]);
	if(k==1){
		int an=0;
		an=1ll*a[1]*pw(c[1],n%(P-1))%P;
		cout<<an<<endl;
		return 0;
	}
	rep(i,1,k)b[k-i]=P-c[i];b[k]=1;
	rep(i,0,k)b_r[i]=b[i];reverse(b_r,b_r+k+1);
	rep(i,0,k)db_r[i]=b_r[i];dft(db_r,M+1);
	//reverse(b,b+k+1);rep(i,0,k)db[i]=b[i];dft(db,M+1);
	rep(i,0,N<<1)c[i]=0;
	b_r[k]=0;
	polyinv(b_r,c);
	
	re(i,0,N<<1)dc[i]=c[i];
	re(i,k,N<<1)dc[i]=0;
	dft(dc,M+1);
	polypow(Ans,n);
	
	int an=0;
	re(i,0,k)an=(an+1ll*Ans[i]*a[i+1])%P;
	an=(an+P)%P;
	cout<<an<<endl;
	//return clock();
}
