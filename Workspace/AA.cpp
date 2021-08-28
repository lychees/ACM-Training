//��CF1558E
#include<iostream>
#include<cstdio>
#include<fstream>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<bitset>
#include<cmath>
#include<cstring>
#include<cstdlib>
using namespace std;
typedef long long LL;
typedef double DB;
const int N = 2222;
int n,m,a[N],b[N];
int c[N],d[N],f[N];
LL g[N];
queue<int> q;
vector<int> v[N];
int solve(LL h){
	int i,j,o,x,y;
	memset(c,0,sizeof(c));
	c[1]=1;
	while(1){
		for(i=1;i<=n;i++){
			if(c[i])
				g[i]=h,q.push(i);
			d[i]=c[i];
			f[i]=0;
		}
		o=0;
		while(!q.empty()){
			x=q.front();
			q.pop();
			o=0;
			for(j=0;j<v[x].size();j++){
				y=v[x][j];
				if(c[x]&&c[y])
					continue;
				if(g[x]<=a[y]||y==f[x])
					continue;
				if(d[y]){
					o=1;
					break;
				}
				d[y]=1;
				f[y]=x;
				g[y]=g[x]+b[y]; //!
				q.push(y);
			}
			if(o)
				break;
		}
		while(!q.empty()){
			q.pop();
		}
		if(!o)
			return 0;
		while(!c[x]){
			c[x]=1;
			h+=b[x];
			x=f[x];
		}
		while(!c[y]){
			c[y]=1;
			h+=b[y];
			y=f[y];
		}
		o=1;
		for(i=1;i<=n;i++)
			o&=c[i];
		if(o)
			return 1;
	}
}
int main()
{
	int T,i,x,y,l,r,h;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(i=2;i<=n;i++)
			scanf("%d",a+i);
		for(i=2;i<=n;i++)
			scanf("%d",b+i);
		for(i=1;i<=m;i++){
			scanf("%d%d",&x,&y);
			v[x].push_back(y);
			v[y].push_back(x);
		}
		l=1,r=1e9+19;
		while(l<r){
			h=l+r>>1;
			if(solve(h))
				r=h;
			else
				l=h+1;
		}
		printf("%d\n",l);
		for(i=1;i<=n;i++)
			v[i].clear();
	}
	return 0;
}
