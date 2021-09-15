#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<map>
using namespace std;
typedef long long LL;
LL n,Power[20];
map< pair<LL,int>,pair<LL,int> >dp;
pair<LL,int> Dp(LL n,int dep,int m)
{
	if(dep==1)
		return make_pair(1LL,(int)n-max((int)n,m));
	if(n<Power[dep-1])
		return Dp(n,dep-1,m);
	pair<LL,int> &ans=dp[make_pair(n,m)];
	if(ans.first)
		return ans;
	pair<LL,int> tmp=Dp(n%Power[dep-1],dep-1,max(m,(int)(n/Power[dep-1])));
	LL newn=n-n%Power[dep-1]+tmp.second;
	pair<LL,int> v=Dp(newn,dep,m);
	ans=make_pair(tmp.first+v.first,v.second);
	return ans;
}
LL work()
{
	Power[0]=1;
	for(int i=1;i<=18;++i)
		Power[i]=Power[i-1]*10;
	int cnt=0;
	for(LL i=n;i;i/=10)
		++cnt;
	if(n==0)
		return 0;
	return Dp(n,cnt,0).first;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n;
	cout<<work()<<endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
