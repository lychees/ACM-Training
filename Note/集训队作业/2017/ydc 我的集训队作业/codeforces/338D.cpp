#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cassert>
#define maxn 10010
using namespace std;
typedef long long LL;
pair<LL,LL> ex_gcd(LL a,LL b)
{
	if(b==0)
		return make_pair(1,0);
	pair<LL,LL> temp=ex_gcd(b,a%b);
	return make_pair(temp.second,temp.first-a/b*temp.second);
}
LL lcm(LL x,LL y)
{
	return x/__gcd(x,y)*y;
}
LL n,m,digit[maxn],k;
void read()
{
	cin>>n>>m>>k;
	for(int i=1;i<=k;++i)
		cin>>digit[i];
}
LL mul(LL a,LL b,LL c)
{
	LL ans=0;
	for(;b;b>>=1,a=(a+a)%c)
		if(b&1)
			ans=(ans+a)%c;
	return ans;
}
bool check()
{
	LL row=1,a1=digit[1],b1=0;
	for(int i=1;i<=k;++i)
	{
		LL t=__gcd(row,digit[i]);
		if(row/t>n/digit[i])
			return false;
		row=row/t*digit[i];
	}
	for(int i=2;i<=k;++i)
	{
		LL a2=digit[i],b2=((digit[i]-i+1)%digit[i]+digit[i])%digit[i];
		pair<LL,LL> sol=ex_gcd(a1,a2);
		LL t=__gcd(a1,a2);
		if(abs(b2-b1)%t)
			return false;
		LL tmp=lcm(a1,a2);
		sol.first=mul((sol.first%tmp+tmp)%tmp,((b2-b1)/t%tmp+tmp)%tmp,tmp);
		b1=(mul(a1,sol.first,tmp)+b1)%tmp,a1=tmp;
		if(b1>m-k+1||(b1==0&&a1>m-k+1))
			return false;
	}
	if(b1==0)
		b1=a1;
	if(b1>m-k+1)
		return false;
	for(int i=1;i<=k;++i)
		if(__gcd(row,b1+i-1)!=digit[i])
			return false;
	return true;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	printf("%s\n",check()?"YES":"NO");
	fclose(stdin);
	fclose(stdout);
	return 0;
}
