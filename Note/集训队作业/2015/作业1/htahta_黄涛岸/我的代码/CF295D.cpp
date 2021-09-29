#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
typedef long long LL;
const int mod=1000000007,maxn=2003;
int f[maxn][maxn],n,m;
LL v,ans=0;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		f[i][2]=(v=f[i-1][2])+1;
		for(int j=3;j<=m;j++)v=v+f[i-1][j],f[i][j]=(v+f[i][j-1])%mod;
	}
	for(int i=1;i<=n;i++)
		for(int j=2;j<=m;j++)ans+=LL(f[i][j])*(f[n-i+1][j]-f[n-i][j])%mod*(m-j+1)%mod;
	cout<<(ans%mod+mod)%mod<<endl;
	return 0;
}
