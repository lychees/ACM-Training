#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
#define P 1000000007
#define N 1000010
int n,a[N],b[N],s[N],t[N];
int main()
{
	int _;scanf("%d",&_);
	while(_--)
	{
		scanf("%d",&n);
		for(int i=0;i<n;i++)scanf("%d",a+i);
		sort(a,a+n);reverse(a,a+n);int c=0;
		for(int i=1;i<n;i+=2)b[i]=a[c++];
		for(int i=0;i<n;i+=2)b[i]=a[c++];
		s[0]=1;t[n]=1;
		for(int i=0;i<n;i++)s[i+1]=(ll)s[i]*b[i]%P;
		for(int i=n;i>0;i--)t[i-1]=(ll)t[i]*b[i-1]%P;
		int S=0;
		for(int i=0;i<n-1;i++)
		{
			int le=i,ri=i+1,z;
			if(b[le]>b[ri])z=le;else z=ri;
			S=(S+(ll)s[z]*t[z+1])%P;
		}
		int T=(ll)s[n]*n%P;
		printf("%d\n",(T-S+P)%P);
	}
	return 0;
}