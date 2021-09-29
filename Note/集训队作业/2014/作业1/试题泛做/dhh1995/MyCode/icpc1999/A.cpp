#include<cstdio>
#include<algorithm>
using namespace std;
const int u[]={-1,-1,0,1,1,0},v[]={-1,0,1,1,0,-1};
int x,y,a,b,X[20005],Y[20005];
int work(int a,int b)
{
	x=X[a]-X[b],y=Y[a]-Y[b]; if (x<0) x=-x,y=-y;
	return y>=0?x+y-min(x,y):x+abs(y);
}
int main()
{
	for (int i=1,L=1;++x,L<=10000;++i)
		for (int j=0;j<6;j++) for (int k=0;k<i;++k) X[++L]=x+=u[j],Y[L]=y+=v[j];
	while (scanf("%d%d",&a,&b),a||b)
		printf("The distance between cells %d and %d is %d.\n",a,b,work(a,b));
	return 0;
}
