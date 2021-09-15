#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define mod 1000000007
#define maxn 1000010
using namespace std;
int n,m,k,cnt,sum,power[maxn]={1};
int delta[maxn],must[maxn],s[maxn];
void read()
{
	scanf("%d %d %d",&n,&m,&k);
	for(int i=1;i<=n;i++)
		power[i]=power[i-1]*2%mod;
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d %d",&a,&b);
		if(b==a+1)
			continue;
		if(b!=a+k+1)
		{
			printf("0\n");
			exit(0);
		}
		must[a]=1,cnt++;
		delta[max(1,a-k)]++,delta[min(n+1,a+k+1)]--;
	}
	int i;
	for(i=1;i<=n;i++)
	{
		delta[i]+=delta[i-1],s[i]=s[i-1];
		if(must[i]==0&&delta[i]==cnt)
			s[i]++;
		if(must[i]&&delta[i]!=cnt)
		{
			printf("0\n");
			exit(0);
		}
	}
}
int solve()
{
	int ans=1;
	for(int i=1;i+k+1<=n;i++)
		if(must[i]==0&&delta[i]==cnt)
			ans=(ans+power[s[min(i+k,n-k-1)]-s[i]])%mod;
	return ans;
}
int main()
{
	read();
	printf("%d\n",solve());
	return 0;
}
