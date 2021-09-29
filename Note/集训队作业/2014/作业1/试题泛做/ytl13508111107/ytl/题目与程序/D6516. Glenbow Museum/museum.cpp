#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
typedef long long LL;
LL C(int n,int m){
    LL ans = 1;
    for(int i=1;i<=m;i++)
        ans *= (n-i+1);
    for(int i=2;i<=m;i++)
        ans /= i;
    return ans;
    }
LL solve(int x){
    if(x<4 || x%2)
        return 0;
    int n = (x-4)/2;
    return C(n+4-1,4-1) + C(n+4-1,4)*2LL;
    }
int main()
{
    freopen("museum.in","r",stdin);
    freopen("museum.out","w",stdout);   
    int x,cases=0;
    while(scanf("%d",&x)==1 && x){
        printf("Case %d: %I64d\n",++cases,solve(x));
        }
    
    return 0;   
}
