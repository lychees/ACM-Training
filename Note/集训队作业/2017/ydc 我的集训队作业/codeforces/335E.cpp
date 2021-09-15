#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<string>
using namespace std;
int n,h;
double calc()
{
	double ans=n,v1=1;
	for(int i=1;i<=h;++i)
	{
		double v=1<<(i-1),v2=1;
		v1/=4;
		for(int l=1;l<n;++l)
			ans+=v*(n-l)*v1*v2,v2=v2*(1-1.0/(1<<i)),v-=1.0*(1<<(i-1))/((1<<i)-1);
	}
	return ans;
}
int main()
{
	freopen("input.txt","r",stdin);
	string str;
	cin>>str>>n>>h;
	printf("%.20f\n",str=="Alice"?calc():n);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
