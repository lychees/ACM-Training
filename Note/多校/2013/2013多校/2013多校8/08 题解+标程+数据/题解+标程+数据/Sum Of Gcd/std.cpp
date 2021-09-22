#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <ctime>
using namespace std;
const int maxn=20010;
int n,a[maxn],Q,L[maxn],R[maxn],id[maxn],num[maxn],phi[maxn],M;
long long ans[maxn];
vector <int> d[maxn];
int cmp(int x,int y)
{
    int id1=L[x]/M;
    int id2=L[y]/M;
    if(id1!=id2)return id1<id2;
    return R[x]<R[y];
}
long long erase(int val)
{
    long long ret=0;
    for(int i=0;i<d[val].size();i++)
        ret+=phi[d[val][i]]*(--num[d[val][i]]);
    return ret;
}
long long insert(int val)
{
    long long ret=0;
    for(int i=0;i<d[val].size();i++)
        ret+=phi[d[val][i]]*(num[d[val][i]]++);
    return ret;
}
void solve()
{
    M=sqrt(n);
    for(int i=1;i<=n;i++)id[i]=i;
    sort(id+1,id+1+Q,cmp);
    memset(num,0,sizeof(num));
    int l=0,r=0;
    long long now=0;
    for(int i=1;i<=Q;i++)
    {
        int nxl=L[id[i]];
        int nxr=R[id[i]];
        while(l<nxl)
        {
            now-=erase(a[l]);
            l++;
        }
        while(l>nxl)
        {
            l--;
            now+=insert(a[l]);
        }
        while(r<nxr)
        {
            r++;
            now+=insert(a[r]);
        }
        while(r>nxr)
        {
            now-=erase(a[r]);
            r--;
        }
        ans[id[i]]=now;
    }
  	for(int i=1;i<=Q;i++)printf("%I64d\n",ans[i]);
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
    for(int i=1;i<maxn;i++)phi[i]=i;
    for(int i=2;i<maxn;i++)
        if(phi[i]==i)
        {
            for(int j=i;j<maxn;j+=i)
                phi[j]=phi[j]/i*(i-1);
        }
    for(int i=1;i<maxn;i++)for(int j=i;j<maxn;j+=i) d[j].push_back(i);
	int T,cas=0;
	scanf("%d",&T);
    while(T--)
    {
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		scanf("%d",&Q);
		for(int i=1;i<=Q;i++)
			scanf("%d %d",&L[i],&R[i]);
		printf("Case #%d:\n",++cas);
        solve();
    }
    return 0;
}
