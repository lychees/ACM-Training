#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define mod 1000000007
#define maxm 50010
using namespace std;
void add(int &a,int b)
{
	a+=b;
	if(a>=mod)
		a-=mod;
}
int get(int p,int n)
{
	return p>>(n-1)&1;
}
int calc(int p,int n)
{
	return p<<(n-1);
}
int n,m=3,px,py;
char map[maxm][5];
void read()
{
	scanf("%d",&n);
	static char str[maxm];
	for(int i=1;i<=3;++i)
	{
		scanf("%s",str+1);
		for(int j=1;j<=n;++j)
		{
			map[j][i]=str[j];
			if(str[j]=='O')
				px=j,py=i;
		}
	}
}
int Dp()
{
	static int dp[2][1<<3][2];
	int cur=0;
	dp[cur][7][0]=1;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		{
			cur^=1;
			memset(dp[cur],0,sizeof(dp[cur]));
			for(int S=0;S<(1<<m);++S)
				for(int t=0;t<=1;++t)
					if(dp[cur^1][S][t])
					{
						int newS,newt=t,x=dp[cur^1][S][t];
						newS=S&3,newS<<=1;
						if(map[i][j]!='.')
						{
							if(i>1&&!get(S,3))
								continue;
							newS|=1,add(dp[cur][newS][newt],x);
						}
						else
						{
							if(i>1&&!get(S,3))
							{
								newS|=1;
								if(i==px-1&&j==py)
									newt=1;
								if(i==px+2&&j==py)
									newt=1;
								add(dp[cur][newS][newt],x);
							}
							else
							{
								if(j>1&&!get(S,1))
								{
									newS|=3;
									if(i==px&&j==py-1)
										newt=1;
									if(i==px&&j==py+2)
										newt=1;
									add(dp[cur][newS][newt],x);
								}
								newS=S&3,newS<<=1,newt=t;
								add(dp[cur][newS][newt],x);
							}
						}
					}
		}
	return dp[cur][7][1];
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	printf("%d\n",Dp());
	fclose(stdin);
	fclose(stdout);
	return 0;
}
