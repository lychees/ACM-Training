#include<cstdio>
#include<algorithm>
using namespace std;
#define N 100010
int n,b[N],a[N],c[N],ra[N];
int main()
{
	int _;scanf("%d",&_);
	while(_--)
	{
		scanf("%d",&n);
		for(int i=0;i<n;i++)scanf("%d",b+i);
		for(int i=0;i<n;i++)a[i]=ra[i]=c[i]=i;
		for(int i=0;i<n-1;i++)
		{
			int b0=b[i],n0=i,n1=i+1;
			while(a[n0]+b[n0]!=c[n0])
			{
				int n2=ra[(c[n0]-b0+n)%n];b0=(c[n2]-a[n2]+n)%n;
				swap(a[n0],a[n2]);swap(ra[a[n0]],ra[a[n2]]);
				if(n2>=n1)break;
				n0=n2;swap(c[n1],c[n0]);
			}
		}
		for(int i=0;i<n;i++)printf("%d%c",a[i],i==n-1?'\n':' ');
		for(int i=0;i<n;i++)printf("%d%c",c[i],i==n-1?'\n':' ');
	}
	return 0;
}