#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
typedef long long LL;
const int mod=1000000007;
int n,m=0,f[1000003];
int main()
{
	n=get();f[0]=f[1]=1;
	for(int i=1;i<=n;i++)m+=get()&1;
	for(int i=2;i<=m;i++)f[i]=(LL(f[i-2])*(i-1)+f[i-1])%mod;
	LL ans=f[m];
	for(int i=m+1;i<=n;i++)ans=ans*i%mod;
	cout<<ans<<endl;
	return 0;
}
