#include<cstdio>
#include<map>
#include<algorithm>
#include<iostream>
using namespace std;
typedef unsigned long long ll;
const ll inf=(ll)1<<63;
const int p[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};
map<ll,ll> H; ll n;
void dfs(int i,int j,int s,ll x,ll y)
{
	map<ll,ll> ::iterator it=H.find(y);
	if (it==H.end()) H[y]=x; else if (x<it->second) H.erase(it),H[y]=x;
	for (int k=1;k<=j;++k){
		if (x>inf/p[i] || y/k>inf/++s) return;
		ll g=__gcd(k,s); x*=p[i],y=y/(k/g)*(s/g);
		dfs(i+1,k,s,x,y);
		}
}
int main()
{
	freopen("factors.in","r",stdin);
	freopen("factors.out","w",stdout);
	dfs(0,63,0,1,1);
	while (cin>>n) cout<<n<<" "<<(n==1?2:H[n])<<endl;
	return 0;
}
