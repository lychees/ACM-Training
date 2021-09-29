#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define x first
#define y second
#define mp make_pair
#define LL long long
using namespace std;
typedef pair<int,int> Pair;
Pair e[3000005];
int n,pri,fir,las;
int a[1500005];
void Get(int &x)
{
	char c=getchar();x=0;
	while(c<48||c>57)c=getchar();
	while(c>47&&c<58)x=x*10+c-48,c=getchar();
}
int main()
{
	int x,y,i;
	Get(n);
	for(i=1;i<n;i++)
		Get(e[i].x),Get(e[i].y),
		e[n-1+i]=e[i],
		swap(e[n-1+i].x,e[n-1+i].y);
	Get(pri);
	if(n==1)return printf("0\n%d\n",1%pri),0;
	sort(e+1,e+n*2-1);
	for(i=1;i<n*2-1;i++)
		if(e[i].x!=e[i-1].x)
			for(int j=e[i-1].x+1;j<=e[i].x;++j)
				a[j]=i;
	a[n+1]=n*2-1;
	las=e[1].x=1;
	e[n+1].x=fir=0;
	while(fir<las)
	{
		x=e[++fir].x;
		for(i=a[x];i<a[x+1];i++)
			if(e[i].y!=e[x+n].x)
				e[++las].x=e[i].y,
				e[n+e[i].y].x=x;
	}
	for(i=1;i<=n;i++)
		e[e[i].x].y=i;
	a[1]=0;
	for(i=2;i<=n;i++)
		a[i]=e[e[e[i].x+n].x].y;
	for(i=1;i<=n;i++)
		e[i]=mp(0,-1500005);
	for(i=1;i<=n;i++)
		e[i+n]=mp(1,0);
	for(i=n;i>=2;i--)
	{
		y=a[i];
		if(e[i]==mp(0,-1500005))
			e[i]=mp(0,0),
			e[i+n]=mp(1,0);
		else
			e[i].y+=e[i].x+1;
		e[y].x+=e[i].y;
		e[y].y=max(e[y].y,e[i].x-e[i].y);
	}
	e[1].y+=e[1].x+1;
	for(i=n;i>=2;i--)
	{
		y=a[i];
		if(e[i].x==e[i].y)
			e[i+n].y=(e[i+n].x+e[i+n].y)%pri;
		e[y+n].y=(LL)e[y+n].y*e[i+n].y%pri;
		if(e[y].y==e[y].x+e[i].x-e[i].y+1)
			e[y+n].y=((LL)e[y+n].y+(LL)e[y+n].x*e[i+n].x)%pri;
		e[y+n].x=(LL)e[y+n].x*e[i+n].y%pri;
	}
	if(e[1].x==e[1].y)
		e[1+n].y=(e[1+n].x+e[1+n].y)%pri;
	printf("%d\n%d\n",e[1].y,e[n+1].y);
	return 0;
}
