#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <set>
using namespace std;
const int b=10000;
int k,m,i;
set<int> S;
void dfs(int x,int v)
{
	if(!x)
	{
		int y=abs(k-v);
		if(y<b)S.insert(i*b+y),S.insert(y*b+i);
		y=abs(k+v);
		if(y<b)S.insert(i*b+y),S.insert(y*b+i);
		if(S.size()>=m)
		{
			for(set<int>::iterator it=S.begin();it!=S.end()&&m;++it,--m)printf("%08d\n",*it);
			exit(0);
		}
		return;
	}
	int t=x%10;
	dfs(x/10,v+t),dfs(x/10,v-t),dfs(x/10,v*t);
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	scanf("%d%d",&k,&m);
	for(i=0;i<b;i++)dfs(i/10,i%10);
	return 0;
}
