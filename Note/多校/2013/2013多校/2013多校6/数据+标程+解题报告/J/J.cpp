#include<cstdio>
#include<algorithm>
using namespace std;
const int S0[34]={4,8,1,1,2,0,3,1,1,0,3,3,2,2,4,4,5,5,9,3,3,0,1,1,3,0,2,1,1,0,4,5,3,7};
int ff(int x)
{
	if(x==0)return 0;
	if(x==1)return 0;
	if(x==15)return 0;
	if(x==17)return 2;
	if(x==18)return 2;
	if(x==32)return 2;
	if(x==35)return 0;
	if(x==52)return 2;
	return S0[x%34];
}
int main()
{
	int _;scanf("%d",&_);
	while(_--)
	{
		int n,S=0;scanf("%d",&n);
		for(int i=0,x;i<n;i++)
			scanf("%d",&x),S^=ff(x);
		puts(S?"Carol":"Dave");
	}
	return 0;
}