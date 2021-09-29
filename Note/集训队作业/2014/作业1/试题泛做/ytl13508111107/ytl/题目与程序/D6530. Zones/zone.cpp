#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 20;
int num[1<<maxn],n,k,m;
int max_ans,max_s;
int bitcount[1<<maxn],data[maxn+10],S[maxn],N[maxn];
void calc(int s){
    int ans = 0;
    for(int i=0;i<n;i++)
        if((s>>i)&1)ans += data[i];
    for(int i=0;i<m;i++)
        if(bitcount[S[i]&s])
            ans -= (bitcount[S[i]&s]-1)*N[i];
    if(ans>max_ans){
        max_ans = ans;
        max_s = s;
        }
    }
int main()
{
    freopen("zone.in","r",stdin);
    freopen("zone.out","w",stdout);
    scanf("%d%d",&n,&k);
    for(int i=0;i<(1<<n);i++)
        bitcount[i]=bitcount[i>>1]+(i&1);
    
    for(int i=0;i<n;i++)
        scanf("%d",&data[i]);
    scanf("%d",&m);
    for(int i=0;i<m;i++){
        int t,s=0,x;
        scanf("%d",&t);
        while(t--){
            scanf("%d",&x);x--;
            s|=(1<<x);
            }
        scanf("%d",&x);
        S[i]=s;N[i]=x;
        }
    for(int i=0;i<(1<<n);i++)
        if(bitcount[i]==k)
            calc(i);
    printf("Number of Customers: %d\n",max_ans);
    printf("Locations recommended:");
    for(int i=0;i<n;i++)
        if((max_s>>i)&1)
            printf(" %d",i+1);
    
    return 0;
}
