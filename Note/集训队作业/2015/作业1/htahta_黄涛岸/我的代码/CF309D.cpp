#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
int n,m,L,lim;
long long ans=0;
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	scanf("%d%d",&n,&m);
	L=n+1;lim=n-m;
	for(int i=m+1;i+i<=L;++i)
		for(int j=m+1,k=lim,C=2*i*(i-L)+j*(L-i);j<=lim&&k>m;++j,C+=L-i)
		{
			//for(;k>m&&C+(i+j)*k>=0;--k);
			if((k=(-C-1)/(i+j))<m)break;
			if(k>lim)k=lim;
			ans+=(k-m)<<((i<<1)<L);
			
		}
	cout<<ans*3<<endl;
	return 0;
}

