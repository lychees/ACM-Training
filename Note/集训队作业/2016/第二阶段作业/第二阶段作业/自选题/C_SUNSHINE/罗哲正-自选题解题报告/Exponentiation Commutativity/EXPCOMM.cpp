#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const int N=1000000,M=1000000007;
int CT;
LL P;
int ans,pr[N],isp[N],pn;

int pow(int a,int b)
{
	int s=1;
	for(;b;b>>=1,a=(LL)a*a%M)
		if(b&1)s=(LL)s*a%M;
	return s;
}

void init()
{
	for(int i=2;i<N;i++)
	{
		if(!isp[i])pr[++pn]=i;
		for(int j=1;j<=pn&&i*pr[j]<N;j++)
		{
			isp[i*pr[j]]=1;
			if(i%pr[j]==0)break;
		}
	}
}

int calc(int p,int e)
{return ((LL)pow(p,e*3-1)*(p+1)-pow(p,e*2-1))%M;}

int calc(LL n)
{
	int res=1;
	for(int p,e,i=1;n>1&&i<=pn;i++)
		if(n%(p=pr[i])==0)
		{
			for(e=0;n%p==0;n/=p,e++);
			res=(LL)res*calc(p%M,e)%M;
		}
	if(n>1)res=(LL)res*calc(n%M,1)%M;
	return res<0?res+M:res;
}

int main()
{
	init();
	for(scanf("%d",&CT);CT--;)
	{
		scanf("%lld",&P);
		ans=(P-1)%M*((P-1)%M)%M;
		ans=(ans+calc(P-1))%M;
		printf("%d\n",ans);
	}
	return 0;
}

