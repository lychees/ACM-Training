#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const double pi=acos(-1);
int n;
void print()
{
	if(n<5)
		printf("No solution\n");
	else
	{
	 	double rad=0,L=100,x=-L,y=0;
	 	for(int i=1;i<n;++i)
	 	{
	 		x+=cos(rad)*L,y+=sin(rad)*L,L+=0.002,rad+=2*pi/n;
	 		printf("%f %f\n",x,y);
		}
 		printf("%f 0\n",x-y/tan(rad));
	}
}
int main()
{
 	freopen("input.txt","r",stdin);
 	freopen("output.txt","w",stdout);
 	scanf("%d",&n);
 	print();
 	fclose(stdin);
 	fclose(stdout);
 	return 0;
}
