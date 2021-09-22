#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;

typedef __int64 ll;

const int N = 111111;
vector<int> e[N];
int d[N];
int n,m,k,ret;

void dfs(int k,int fa,int dp){
    d[k]=dp;
    for (int i=0;i<e[k].size();++i)
        if (e[k][i]!=fa) dfs(e[k][i],k,dp+1);
}

int main(){
    int _;
    scanf("%d",&_);
    while (_--){
        scanf("%d%d",&n,&m);
        for (int i=1;i<=n;++i) e[i].clear();
        for (int i=1,p1,p2;i<n;++i){
            scanf("%d%d",&p1,&p2);
            e[p1].push_back(p2);
            e[p2].push_back(p1);
        }
        ret = 1;
        dfs(ret,0,0);
        for (int i=2;i<=n;++i) if (d[i]>d[ret]) ret=i;
        dfs(ret,0,0);
        for (int i=2;i<=n;++i) if (d[i]>d[ret]) ret=i;
        ret = d[ret];
        while (m--){
            scanf("%d",&k);
            if (k<=ret+1) printf("%d\n",k-1);
            else printf("%d\n",ret+(k-ret-1)*2);
        }
    }
    return 0;
}
