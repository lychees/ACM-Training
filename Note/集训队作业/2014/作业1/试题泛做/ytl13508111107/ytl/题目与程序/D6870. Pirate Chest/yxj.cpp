#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=510;
const int inf=0x7fffffff/2;
int n,m,a,b;
int d[MAXN][MAXN],minv[MAXN][MAXN];
int l[MAXN],r[MAXN];
int w[MAXN],tt[MAXN];

void calc()
{
 int hi[MAXN],loc[MAXN],p=0;
 hi[0]=-1;loc[0]=0;
 for(int i=1;i<=m;i++)
 {
  while(hi[p]>=w[i])
   p--;
        tt[i]=i-loc[p];
        hi[++p]=w[i];loc[p]=i;
 }
 return ;
}
void solve()
{
 long long ans=0,s;
 for(int k=1;k<=n;k++)
 {
  for(int i=1;i<=n-k+1;i++)
   for(int j=1;j<=m;j++)
    minv[i][j]=min(minv[i][j],d[i+k-1][j]);
  for(int i=1;i<=n-k+1;i++)
  {
   for(int j=1;j<=m;j++)
    w[j]=minv[i][j];
   calc();
   for(int j=1;j<=m;j++)
    l[j]=tt[j];
   reverse(w+1,w+1+m);
   calc();
   for(int j=1;j<=m;j++)
    r[j]=tt[m+1-j];
   for(int j=1;j<=m;j++)
   {
            int x=k,y=l[j]+r[j]-1;
            if(x>y) swap(x,y);
            x=min(x,a);
            y=min(y,b);
            s=x*y;
            ans=max(ans,((s*minv[i][j]-1)/(m*n-s)+minv[i][j])*s);
         }
  }
 }
 cout<<ans<<endl;
}

int main()
{
 
 	freopen("pirate.in","r",stdin);
	freopen("yxj.out","w",stdout);
	scanf("%d%d%d%d",&a,&b,&n,&m);
 if(a>b)swap(a,b);
 for(int i=1;i<=n;i++)
  for(int j=1;j<=m;j++)
   scanf("%d",&d[i][j]);
 for(int i=1;i<=n;i++)
  for(int j=1;j<=m;j++)
   minv[i][j]=inf;
 solve();
 return 0;
}
