#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define MOD 998244353
#define MAX 840000
int fpow(int a,int b){int s=1;while(b){if(b&1)s=1ll*s*a%MOD;a=1ll*a*a%MOD;b>>=1;}return s;}
int r[MAX],W[MAX];
void NTT(int *P,int opt,int len)
{
    int N,l=0;for(N=1;N<len;N<<=1)++l;
    for(int i=0;i<N;++i)r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
    for(int i=0;i<N;++i)if(i<r[i])swap(P[i],P[r[i]]);
    for(int i=1;i<N;i<<=1)
    {
        int w=fpow(3,(MOD-1)/(i<<1));W[0]=1;
        for(int k=1;k<i;++k)W[k]=1ll*W[k-1]*w%MOD;
        for(int j=0,p=i<<1;j<N;j+=p)
            for(int k=0;k<i;++k)
            {
                int X=P[j+k],Y=1ll*W[k]*P[i+j+k]%MOD;
                P[j+k]=(X+Y)%MOD;P[i+j+k]=(X+MOD-Y)%MOD;
            }
    }
    if(opt==-1)
    {
        reverse(&P[1],&P[N]);
        for(int i=0,inv=fpow(N,MOD-2);i<N;++i)P[i]=1ll*P[i]*inv%MOD;
    }
}
int jc[MAX],inv[MAX],jv[MAX];
int f[MAX],g[MAX],A[MAX];
int L[MAX],R[MAX];
void CDQ(int l,int r)
{
    if(l==r)
    {
        if(l!=1) f[l]=1ll*f[l]*inv[2]%MOD*jc[l-1]%MOD;
        return;
    }
    int mid=(l+r)>>1,N;
    CDQ(l,mid);
    for(N=1;N<=mid-l+1+r-l;N<<=1);


    for(int i=0;i<=r-l;++i)L[i-l]=f[i] * jv[i];
    for(int i=0;i<=r-l;++i)R[i]=A[i];
    NTT(L,1,N);NTT(R,1,N);
    for(int i=0;i<N;++i)L[i]=1ll*L[i]*R[i]%MOD*L[i]%MOD;
    NTT(L,-1,N);
    for(int i=mid+1;i<=r;++i)f[i]=(f[i]+L[i-1-l])%MOD;



    /*for(int i=0;i<N;++i)L[i]=R[i]=0;
    for(int i=l;i<=mid;++i)L[i-l]=1ll*f[i]*jv[i]%MOD;

    for(int i=0;i<=r;++i) {
        //if(i<l)R[i]=2ll*f[i]*jv[i]%MOD;
        //else if(i<=mid)

            R[i]=1ll*f[i]*jv[i]%MOD;
    }


    NTT(L,1,N);NTT(R,1,N);
    for(int i=0;i<N;++i)L[i]=1ll*L[i]*R[i]%MOD;
    NTT(L,-1,N);
    for(int i=mid+1;i<=r;++i)g[i]=(g[i]+L[i-l])%MOD;
    for(int i=0;i<N;++i)L[i]=R[i]=0;*/

    CDQ(mid+1,r);
}
int n;
char ch[MAX];
int main()
{

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    //freopen("/Users/minakokojima/Documents/GitHub/ACM-Training/Workspace/out.txt", "w", stdout);
#endif


    scanf("%d%s",&n,ch);

    jc[0]=jv[0]=inv[0]=inv[1]=1;
    for(int i=2;i<=n;++i)inv[i]=1ll*inv[MOD%i]*(MOD-MOD/i)%MOD;
    for(int i=1;i<=n;++i)jc[i]=1ll*jc[i-1]*i%MOD;
    for(int i=1;i<=n;++i)jv[i]=1ll*jv[i-1]*inv[i]%MOD;
    f[1]=1;

    for(int i=0;i<n;++i)A[i]=(ch[i]-48)*jv[i];;
    /*
    for(int i=2;i<=n;++i)
    {
        for(int j=0;j<=i;++j)g[i]=(g[i]+1ll*f[j]*jv[j]%MOD*f[i-j]%MOD*jv[i-j]%MOD)%MOD;
        for(int j=0;j<i;++j)
            if(A[i-1-j])
                f[i]=(f[i]+1ll*g[j]*jv[i-1-j])%MOD;
        f[i]=1ll*f[i]*inv[2]%MOD*jc[i-1]%MOD;
    }
    */
    CDQ(1,n);
    for(int i=1;i<=n;++i)printf("%d\n",f[i]);
    return 0;
}
