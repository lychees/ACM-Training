#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <map>
#define mp make_pair
#define x first
#define y second
using namespace std;
typedef long long LL;
typedef pair<LL,int> pLi;
map<pLi,pLi> f;
LL n;
pLi dp(LL x,int y)
{
	pLi res=mp(0,0),st=mp(x,y),v;
	if(!x)return res;
	if(x<10)return mp(1,max(y-x,0ll));
	if(f.count(st))return f[st];
	LL tp=1,num;
	for(;tp<=x/10;tp*=10);
	while(x>0)
	{
		num=max(x/tp,LL(y));
		v=dp(x%tp,num);
		res.x+=v.x,x-=x%tp+v.y;
		if(!v.y&&num)x-=num,res.x++;
	}
	res.y=-x;
	return f[st]=res;
}
int main()
{
	cin>>n;
	cout<<dp(n,0).x<<endl;
	return 0;
}
