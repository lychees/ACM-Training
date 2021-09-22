#include "iostream"
#include "cstring"
#include "cstdio"
using namespace std;
typedef long long LOL;
const LOL MOD = 1000000007ll;
LOL solve(LOL n,LOL k)
{
    if(n<k) return 0;
    if(n==k) return 1;
    LOL ans=n-k+3;
    LOL tmp=2;
    k=n-k-2;
    if(k==-1){
        return ans/2;
    }
    while(k){
        if(k%2){
            ans=(ans*tmp)%MOD;
        }
        tmp=(tmp*tmp)%MOD;
        k/=2;
    }
    return ans;
}
int main(void)
{
    LOL n,k;
    int T;
    scanf("%d",&T);
    while(T--){
        cin>>n>>k;
        cout<<solve(n,k)<<endl;
    }
    return 0;
}
