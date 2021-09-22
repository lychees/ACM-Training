#include<stdio.h>
#include<string.h>
#include<math.h>
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<algorithm>
using namespace std;
typedef __int64 lld;
#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define inf 0xfffffff
#define mod 10007
#define maxn 100010
lld dp[maxn];
void init()
{
	dp[0]=1;
	dp[1]=1;
	for(int i=2;i<maxn;i++)
		dp[i]=(dp[i-1]+dp[i-2])%mod;
}
char str[maxn];
int main()
{
	init();
	int cas;
	scanf("%d",&cas);
	for(int cc=1;cc<=cas;cc++)
	{
		scanf("%s",str);
		int len=strlen(str);
		lld ans=1;
		for(int i=0;i<len-1;i++)
		{
			if(str[i] == 'h' && str[i+1] == 'e')
			{
				int t=0;
				int j=i;
				while(j < len-1 && str[j] == 'h' && str[j+1] == 'e')
				{
					j+=2;
					t++;
				}
				ans=(ans*dp[t])%mod;
				i=j;
			}
		}
		printf("Case %d: ",cc);
		cout << ans << endl;
	}
	return 0;
}
