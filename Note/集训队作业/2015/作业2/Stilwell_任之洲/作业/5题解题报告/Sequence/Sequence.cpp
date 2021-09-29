#include <stdio.h>
#include <stdlib.h>
using namespace std;

int n,i,j,k;
int d[15][100005];

long long calc(int deep,int n,int digit)
{
	int i;
	long long ans=102345678900000ll;
	if(n==1)
	{
		ans=0;
		for(i=1;i<=9;++i)
		if(d[deep][1]&(1<<i))
		{
			ans=ans*10+i;
			if(ans==i&&(d[deep][1]&1))ans*=10;
		}
		if(!ans&&(d[deep][1]&1))ans=10;
		return ans;
	}
	int j,k,l,t;
	bool zero;
	long long tmp;
	for(i=0;i<=digit;++i)
	{
		k=i;l=t=0;zero=false;
		for(j=1;j<=n;++j)
		{
			t|=d[deep][j]&(1023-(1<<k));
			if((d[deep][j]&1)&&!k)zero=true;
			if(k==9||j==n)d[deep+1][++l]=t,t=0,k=0;else ++k;
		}
		if(i<9||n>2)tmp=calc(deep+1,l,9);else tmp=calc(deep+1,l,8);
		tmp=tmp*10+i;
		if(!tmp&&zero)tmp=10;
		if(tmp<ans)ans=tmp;
	}
	return ans;
}

int main()
{
	scanf("%d",&n);
	for(i=1;i<=n;++i)scanf("%d",&k),d[0][i]|=1<<k;
	printf("%lld\n",calc(0,n,9));
}
