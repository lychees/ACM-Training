#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;
int n;
double L,A,x=0,y=0,B;
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	scanf("%d",&n);
	if(n<5)return puts("No solution"),0;
	B=A=2*acos(-1.0)/n;L=500;
	for(int i=1;i<n;i++)
	{
		printf("%.10lf %.10lf\n",x,y);
		if(i==n-1)break;
		x+=L*cos(A),y+=L*sin(A);
		L+=0.01;A+=B;
	}
	printf("%.10lf %.10lf\n",x-y/tan(A),0.0);
	return 0;
}
