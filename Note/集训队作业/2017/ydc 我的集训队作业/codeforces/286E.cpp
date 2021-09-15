#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 2097200
#define mod 1004535809
#define P 3
using namespace std;
typedef long long LL;
int n,m,a[maxn],*pw;
int Power(int p,int n)
{
	int ans=1;
	for(;n;n>>=1,p=(LL)p*p%mod)
		if(n&1)
			ans=(LL)ans*p%mod;
	return ans;
}
void Read(int &digit)
{
	digit=0;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
}
void read()
{
	a[0]=1;
	Read(n),Read(m);
	for(int i=1,x;i<=n;++i)
		Read(x),a[x]=1;
}
void FFT(int *a,int *b,int step,int n)
{
	if(n==1)
		b[0]=a[0];
	else
	{
		int m=n>>1;
		FFT(a,b,step<<1,m),FFT(a+step,b+m,step<<1,m);
		for(int i=0;i<m;++i)
		{
			int even=b[i],odd=(LL)b[i+m]*pw[i*step]%mod;
			b[i]=(odd+even)%mod,b[i+m]=(even-odd+mod)%mod;
		}
	}
}
void print()
{
	static int pw1[maxn],pw2[maxn],ta[maxn],b[maxn];
	int tn;
	for(tn=1;tn<m+m+1;tn<<=1);
	int n=tn;
	int p=Power(P,(mod-1)/n),inv=Power(p,mod-2);
	pw1[0]=1,pw2[0]=1;
	for(int i=1;i<n;++i)
		pw1[i]=(LL)pw1[i-1]*p%mod,pw2[i]=(LL)pw2[i-1]*inv%mod;
	pw=pw1;
	FFT(a,ta,1,n);
	for(int i=0;i<n;++i)
		ta[i]=(LL)ta[i]*ta[i]%mod;
	pw=pw2;
	FFT(ta,b,1,n);
	static int ans[maxn];
	int tot=0;
	for(int i=1;i<=m;++i)
	{
		if(!a[i]&&b[i])
		{
			printf("NO\n");
			exit(0);
		}
		if(a[i]&&b[i]==n*2)
			ans[++tot]=i;
	}
	printf("YES\n");
	printf("%d\n",tot);
	for(int i=1;i<=tot;++i)
		printf("%d%c",ans[i],i<tot?' ':'\n');
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	print();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
