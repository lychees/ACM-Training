#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;
#define P 1000003
#define N 100010
#define N1 262144
#define N2 262145
#define P1 998244353
#define P2 995622913
#define E1 996173970
#define E2 88560779
#define F1 121392023
#define F2 840835547
#define I1 998240545
#define I2 995619115
#define M1 397550359381069386LL
#define M2 596324591238590904LL
#define MM 993874950619660289LL
int F[N],I[P],n,a[N],b,c,d;
ll mul(ll x,ll y,ll z){return (x*y-(ll)(x/(ld)z*y+1e-3)*z+z)%z;}
int trf(int x1,int x2){return (mul(M1,x1,MM)+mul(M2,x2,MM))%MM%P;}
int pd[N],pb[N],pc2[N];
int A[N2],B[N2],C[N2];
int A1[N2],B1[N2],C1[N2];
void fft(int*A,int PM,int PW)
{
	for(int m=N1,h;h=m/2,m>=2;PW=(ll)PW*PW%PM,m=h)
		for(int i=0,w=1;i<h;i++,w=(ll)w*PW%PM)
			for(int j=i;j<N1;j+=m)
			{
				int k=j+h,x=(A[j]-A[k]+PM)%PM;
				(A[j]+=A[k])%=PM;
				A[k]=(ll)w*x%PM;
			}
	for(int i=0,j=1;j<N1-1;j++)
	{
		for(int k=N1/2;k>(i^=k);k/=2);
		if(j<i)swap(A[i],A[j]);
	}
}
void mul()
{
	memset(C,0,sizeof C);
	memcpy(A1,A,sizeof A);
	memcpy(B1,B,sizeof B);
	fft(A1,P1,E1);fft(B1,P1,E1);
	for(int i=0;i<N1;i++)C1[i]=(ll)A1[i]*B1[i]%P1;
	fft(C1,P1,F1);
	for(int i=0;i<N1;i++)C1[i]=(ll)C1[i]*I1%P1;
	fft(A,P2,E2);fft(B,P2,E2);
	for(int i=0;i<N1;i++)C[i]=(ll)A[i]*B[i]%P2;
	fft(C,P2,F2);
	for(int i=0;i<N1;i++)C[i]=(ll)C[i]*I2%P2;
	for(int i=0;i<N1;i++)C[i]=trf(C1[i],C[i]);
	for(int i=n;i<N1;i++)C[i]=0;
}
int main()
{
	I[1]=1;for(int i=2;i<P;i++)I[i]=(ll)P/i*(P-I[P%i])%P;
	scanf("%d%d%d%d",&n,&b,&c,&d);
	F[0]=1;for(int i=1;i<n;i++)F[i]=(ll)F[i-1]*i%P;
	for(int i=0;i<n;i++)scanf("%d",a+i);
	pd[0]=1;for(int i=1;i<n;i++)pd[i]=(ll)pd[i-1]*d%P;
	for(int i=0;i<n;i++)A[i]=(ll)a[n-1-i]*F[n-1-i]%P;
	for(int i=0;i<n;i++)B[i]=(ll)pd[i]*I[F[i]]%P;
	mul();
	memcpy(A,C,sizeof A);reverse(A,A+n);
	pb[0]=1;for(int i=1;i<n;i++)pb[i]=(ll)pb[i-1]*b%P;
	for(int i=0;i<n;i++)A[i]=(ll)A[i]*pb[i]%P*I[F[i]]%P;
	pc2[0]=1;int c2=(ll)c*c%P;
	for(int i=1,s=c;i<n;i++)
		pc2[i]=(ll)pc2[i-1]*s%P,s=(ll)s*c2%P;
	for(int i=0;i<n;i++)A[i]=(ll)A[i]*pc2[i]%P;
	memset(B,0,sizeof B);
	B[0]=1;for(int i=1;i<n;i++)B[i]=I[pc2[i]],B[N1-i]=I[pc2[i]];
	mul();
	for(int i=0;i<n;i++)C[i]=(ll)C[i]*pc2[i]%P;
	for(int i=0;i<n;i++)printf("%d\n",C[i]);
	return 0;
}