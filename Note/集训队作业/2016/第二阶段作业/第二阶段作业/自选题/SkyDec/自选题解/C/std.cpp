#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<map>
#include<set>
#include<string>
#include<vector>
#include<assert.h>
#define pb push_back
#define rep(i,j,k) for(int i=(j);i<=(int)k;i++)
#define per(i,j,k) for(int i=(j);i>=(int)k;i--)
#define lowbit(x) ((x)&(-(x)))
#define fi first
#define se second
#define pii pair<int,int>
#define VI vector<int>
using namespace std;
typedef long long LL;
typedef double db;
const int P=1000000007;
inline int Pow(int a,int b){
    int c=1;for(;b;b>>=1,a=a*1ll*a%P)if(b&1)c=c*1ll*a%P;
    return c;
}
int Bo[55];
int Xi[55][55];
int comb[55][55];
inline void Get_Bo(){
    Bo[0]=1;
    rep(i,1,51){
        rep(j,0,i-1)Bo[i]=(Bo[i]+Bo[j]*1ll*comb[i+1][j])%P;
        Bo[i]=-Bo[i];
        Bo[i]=Bo[i]*1ll*Pow(i+1,P-2)%P;
         
    }
     
    rep(i,0,51){
        rep(j,1,i+1){
            Xi[i][j]=Bo[i+1-j]*1ll*comb[i+1][j]%P;
            Xi[i][j]=Xi[i][j]*1ll*Pow(i+1,P-2)%P;
        }
    }
}
int S(int n,int m){
    int base=n+1;int ans=0;
    rep(i,1,m+1){
        ans=(ans+base*1ll*Xi[m][i])%P;
        base=base*1ll*(n+1)%P;
    }
    return ans;
}
int ans[55][55];
int tmp[55][55]; 
void Work(int A,int B,int C,int N,int M){
    if(N<0){memset(ans,0,sizeof ans);return;}
     
    if(A>=C){
        Work(A%C,B,C,N,M);
        int pp=A/C;
        memset(tmp,0,sizeof tmp);
        rep(m,0,M)rep(k,0,M-m){
            rep(u,0,m){
                int v=comb[m][u]*1ll*Pow(pp,m-u)%P;
                v=v*1ll*ans[u][m-u+k]%P;
                tmp[m][k]=(tmp[m][k]+v)%P;
            }
        }
         
        rep(i,0,M)rep(j,0,M)ans[i][j]=tmp[i][j];
    }
    else
    if(B>=C){
        Work(A,B%C,C,N,M);
        int pp=B/C;
         
        memset(tmp,0,sizeof tmp);
        rep(m,0,M)rep(k,0,M-m){
            rep(u,0,m){
                int v=comb[m][u]*1ll*Pow(pp,m-u)%P;
                v=v*1ll*ans[u][k]%P;
                tmp[m][k]=(tmp[m][k]+v)%P;
            }
        }
         
        rep(i,0,M)rep(j,0,M)ans[i][j]=tmp[i][j];
    }
    else{
        if(A==0){
            memset(ans,0,sizeof ans);
            rep(i,0,M)ans[0][i]=S(N,i);
            return;
        }
         
        int UP=(A*1ll*N+B)/(C*1ll);
         
        Work(C,C-B-1+A,A,UP-1,M);
         
        memset(tmp,0,sizeof tmp);
        rep(i,0,M)tmp[0][i]=S(N,i);
        rep(m,1,M)rep(k,0,M-m){
            tmp[m][k]=S(N,k)*1ll*Pow(UP,m)%P;
            rep(u,1,m){
                int v=0;
                rep(o,1,k+1)v=(v+Xi[k][o]*1ll*ans[o][m-u])%P;
                tmp[m][k]=(tmp[m][k]-v*1ll*comb[m][u])%P;
            }
        }
         
        rep(m,0,M)rep(k,0,M)ans[m][k]=tmp[m][k];
    }
}
int main(){
    //freopen("newwork.in","r",stdin);
    //freopen("newwork.out","w",stdout);
    rep(i,0,52){
        comb[i][0]=comb[i][i]=1;
        rep(j,1,i-1)comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%P;
    }
    Get_Bo();
    int K,L,R,A,B,C;
    scanf("%d%d%d%d%d%d",&K,&L,&R,&A,&B,&C);
    Work(A,B,C,R,K);
    int res=ans[K][0];
    memset(ans,0,sizeof ans);
    Work(A,B,C,L-1,K);
    res=(res-ans[K][0])%P;
    if(res<0)res+=P;
    printf("%d\n",res);
    return 0;
}