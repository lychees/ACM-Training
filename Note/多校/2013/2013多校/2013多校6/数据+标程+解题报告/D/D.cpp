#include<cstdio>
#include<algorithm>
using namespace std;
#define P 1000000007
#define N 100010
int a[N];
int main()
{
	a[0]=1;
	for(int n=1;n<N;n++)
	{
		int S=0;
		for(int i=1,w=0;;i++)
		{
			w+=2*i-1;
			if(w>n)break;
			if(i&1)S=(S+a[n-w])%P;
			else S=(S-a[n-w]+P)%P;
			w+=i;
			if(w>n)break;
			if(i&1)S=(S+a[n-w])%P;
			else S=(S-a[n-w]+P)%P;
		}
		a[n]=S;
	}
	int _;scanf("%d",&_);
	while(_--)
	{
		int n,k;scanf("%d%d",&n,&k);int S=a[n];
		for(int i=1,w=0;;i++)
		{
			w+=(2*i-1)*k;
			if(w>n)break;
			if(~i&1)S=(S+a[n-w])%P;
			else S=(S-a[n-w]+P)%P;
			w+=i*k;
			if(w>n)break;
			if(~i&1)S=(S+a[n-w])%P;
			else S=(S-a[n-w]+P)%P;
		}
		printf("%d\n",S);
	}
	return 0;
}