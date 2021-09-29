#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 505
using namespace std;
typedef long long LL;

const int INF=0x7fffffff;

int n,m,A,B,v[N][N],w[N][N];
double SS;
LL ans;

int calc(double S,double x){
    return int(trunc(x/(1-S/SS)-1e-4));
}
inline int min(int a,int b,int c){
    return min(a,min(b,c));
}
int main(){
    
	freopen("pirate.in","r",stdin);
	freopen("bc.out","w",stdout);
	scanf("%d%d%d%d",&A,&B,&n,&m);
    SS=n*m;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            scanf("%d",&v[i][j]);
    for (int a1=1;a1<=n;a1++)
        for (int b1=1;b1<=m;b1++){
            for (int i=1;i<=n;i++) w[i][b1-1]=INF;
            for (int j=1;j<=m;j++) w[a1-1][j]=INF;
            for (int a2=a1;a2<=n;a2++)
                for (int b2=b1;b2<=m;b2++) if ((a2-a1+1<=A&&b2-b1+1<=B)||(a2-a1+1<=B&&b2-b1+1<=A)){
                    w[a2][b2]=min(w[a2][b2-1],w[a2-1][b2],v[a2][b2]);
                    int S=(a2-a1+1)*(b2-b1+1);
                    int h=calc(S,w[a2][b2]);
                    ans=max(ans,LL(h)*S);
                    if (LL(h)*S>=27580361800LL){
						printf("%I64d %d %d %d %d\n",LL(h)*S,a1,a2,b1,b2);
					}
                }
        }
    printf("%I64d\n",ans);
    return 0;
}
