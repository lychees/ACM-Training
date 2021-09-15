#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long LL;
LL n,C;
int work()
{
	int ans=0;
	LL now=0;
	while(now<n*C)
		now+=now/n+1,++ans;
	return ans;
}
int main()
{
	int T;
	scanf("%d",&T);
	for(int i=1;i<=T;++i)
	{
		cin>>n>>C;
		printf("Case #%d: %d\n",i,work());
	}
	return 0;
}
