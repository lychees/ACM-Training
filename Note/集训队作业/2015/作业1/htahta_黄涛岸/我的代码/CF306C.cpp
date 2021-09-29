#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <ctime>
using namespace std;
typedef long long LL;
inline int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f==1)return -v;else return v;
}
typedef long long LL;
const int maxn=4003,mod=1000000009;
int n,w,b,m;
LL fac[maxn],inv[maxn],ans=0;
LL C(int k,int n)
{
	if(n<k)return 0;
	return fac[n]*inv[n-k]%mod*inv[k]%mod;
}
LL Pow(LL a,LL b)
{
	LL res=1;
	for(;b;b/=2,a=a*a%mod)
		if(b&1)res=res*a%mod;
	return res;
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	scanf("%d%d%d",&n,&w,&b);
	m=max(w,b);fac[0]=1;
	for(int i=1;i<=m;i++)fac[i]=fac[i-1]*i%mod;
	inv[m]=Pow(fac[m],mod-2);
	for(int i=m-1;i>=0;i--)inv[i]=inv[i+1]*(i+1)%mod;
	for(int i=1;i<=n-2;i++)ans=(C(n-i-1,w-1)*(n-i-1)%mod*C(i-1,b-1)+ans)%mod;
	cout<<ans*fac[b]%mod*fac[w]%mod<<endl;
	return 0;
}
