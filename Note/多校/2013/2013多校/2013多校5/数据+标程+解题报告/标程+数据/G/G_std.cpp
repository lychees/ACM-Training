#include <cstdio>
#include <cstring>

double f[201][2];
int a[201];
double p[201];
char op[201];
int n;
double sum;
char b[201][20];

inline void makebit()
{
  int i,j,x;
  memset(b,0,sizeof(b));
  for (i=0;i<=n;i++)
  {
    x=a[i];
    j=0;
    while (x>0)
    {
      b[i][j]=x&1;
      j++;
      x=x>>1;
    }
  }
}

double DP(int x)
{
  int i;
  memset(f,0,sizeof(f));
  if (b[0][x])
    f[0][1]=1;
  else
    f[0][0]=1;
  for (i=1;i<=n;i++)
  {
    f[i][0]=f[i-1][0]*p[i];
    f[i][1]=f[i-1][1]*p[i];
    if (op[i]=='&')
    {
      if (b[i][x])
      {
        f[i][1]+=f[i-1][1]*(1-p[i]);
        f[i][0]+=f[i-1][0]*(1-p[i]);
      }
      else
      {
        f[i][0]+=f[i-1][1]*(1-p[i]);
        f[i][0]+=f[i-1][0]*(1-p[i]);
      }
    }
    if (op[i]=='|')
    {
      if (b[i][x])
      {
        f[i][1]+=f[i-1][1]*(1-p[i]);
        f[i][1]+=f[i-1][0]*(1-p[i]);
      }
      else
      {
        f[i][1]+=f[i-1][1]*(1-p[i]);
        f[i][0]+=f[i-1][0]*(1-p[i]);
      }
    }
    if (op[i]=='^')
    {
      if (b[i][x])
      {
        f[i][1]+=f[i-1][0]*(1-p[i]);
        f[i][0]+=f[i-1][1]*(1-p[i]);
      }
      else
      {
        f[i][1]+=f[i-1][1]*(1-p[i]);
        f[i][0]+=f[i-1][0]*(1-p[i]);
      }
    }
  }
  return f[n][1];
}

int main()
{
  int x,T,i;
  T=0;
  while (scanf("%d",&n)==1)
  {
    for (i=0;i<=n;i++)
      scanf("%d",&a[i]);
    getchar();
    for (i=1;i<=n;i++)
    {
      op[i]=getchar();
      getchar();
    }
    for (i=1;i<=n;i++)
      scanf("%lf",&p[i]);
    sum=0;
    makebit();
    for (i=0;i<20;i++)
      sum=sum+(1<<i)*DP(i);
    T++;
    printf("Case %d:\n",T);
    printf("%.6lf\n",sum);
  }
  return 0;
}