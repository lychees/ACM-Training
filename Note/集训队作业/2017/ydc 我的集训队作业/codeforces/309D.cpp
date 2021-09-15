#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<ctime>
using namespace std;
typedef long long LL;
int n,m;
LL calc()
{
	LL ans=0;
	for(int i=m+1;i+m<=n&&i<=(n+1)/2;++i)
	{
		int xi=i,yi=i;
		int sum=0;
		for(int j=m+1,k=n-m;j+m<=n;++j)
		{
			int xj=(n+j+1),yj=(n-j+1);
			int val=(xj-xi)*(2*k-xi)-(yj-yi)*yi*3;
			while(k>m&&val>=0)
				val-=2*(xj-xi),--k;
			if(k==m)
				break;
			sum+=k-m;
		}
		if(i*2!=(n+1))
			sum*=2;
		ans+=sum;
	}
	return ans*3;
}
int main()
{
	freopen("input.txt","r",stdin);
	scanf("%d %d",&n,&m);
	cout<<calc()<<endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
