#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long LL;
int F(LL a,LL n,LL p)
{
	LL newn=a*n/p;
	if(!newn)
		return max(a,p-a*n);
	if(a*n%p<a*(p/a-1))
		--newn;
	return F(min(a-p%a,p%a),newn,a);
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	LL T,a,n,p,h;
	for(cin>>T;T;--T)
	{
		cin>>a>>n>>p>>h;
		a%=p;
		LL val=a*n<p?a:F(a,n,p);
		printf("%s\n",val>h?"NO":"YES");
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
