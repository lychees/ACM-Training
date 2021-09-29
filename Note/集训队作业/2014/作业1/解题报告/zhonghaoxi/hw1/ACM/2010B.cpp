#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

const int INF=0x3f3f3f3f;

int n,z[200],match[100];

int main()
{
	memset(match,-1,sizeof(match));
	match[1]=0;
	match[17]=1;
	match[9]=2;
	match[24]=3;
	match[5]=4;
	match[20]=5;
	match[12]=6;
	match[3]=7;
	match[18]=8;
	match[16]=9;
	match[4]=10;
	match[6]=11;
	int t=0;
	while (~scanf("%d",&n))
	{
		if (!n) break;
		t++;
		printf("Case %d: ",t);
		for (int a=1;a<=n;a++)
			scanf("%d",&z[a]);
		int res=-1;
		if (n<11 || n%6!=5) res=0;
		else
		{
			double upper=z[1]*1.5;
			int minv1=z[1],maxv1=z[1];
			int minv2=INF,maxv2=0;
			for (int a=1;a<=n;a++)
				if (z[a]>upper)
				{
					minv2=min(minv2,z[a]);
					maxv2=max(maxv2,z[a]);
					z[a]=1;
				}
				else
				{
					minv1=min(minv1,z[a]);
					maxv1=max(maxv1,z[a]);
					z[a]=0;
				}
			if (minv1*105<maxv1*95 || minv2*105<maxv2*95 || minv1*210<maxv2*95 || maxv1*190>minv2*105) res=0;
			else
			{
				if (z[2]) reverse(z+1,z+n+1);
				z[n+1]=0;
				for (int a=1;a<=n;a+=6)
				{
					if (z[a+5]) res=0;
					int v=0;
					for (int b=1;b<=5;b++)
						v=v*2+z[a+b-1];
					z[a/6]=match[v];
					if (match[v]==-1) res=0;
				}
				n/=6;
				if (z[0]!=11 || z[n]!=11) res=0;
				n--;
				for (int a=1;a<=n;a++)
					if (z[a]==11) res=0;
				if (res!=0)
				{
					n-=2;
					int v=0;
					for (int a=1;a<=n;a++)
						v=(v+((n-a)%10+1)*z[a])%11;
					if (v!=z[n+1]) res=1;
					else
					{
						v=0;
						for (int a=1;a<=n+1;a++)
							v=(v+((n+1-a)%9+1)*z[a])%11;
						if (v!=z[n+2]) res=2;
						else res=3;
					}
				}
			}
		}
		if (res==0) printf("bad code\n");
		else
		{
			if (res==1) printf("bad C\n");
			else
			{
				if (res==2) printf("bad K\n");
				else
				{
					for (int a=1;a<=n;a++)
						if (z[a]==10) printf("-");
						else printf("%d",z[a]);
					printf("\n");
				}
			}
		}
	}

	return 0;
}
