/*
问题转化一下就是求数列中最长的连续数的和模M等于0.
因为要求的是连续的数，所以对于余数相同的前i项和，
记录得到该余数的最少连续前k1项，和最多连续前k2项，
k2-k1即为能整除的最长序列长度
*/
#include <cstdio>
#include <cstring>

#define MAXM 10000

int n,m;
int a[MAXM];

int main()
{
  int i,s,x,ans;
  while (scanf("%d%d",&n,&m)==2)
  {
    memset(a,-1,sizeof(a));
    a[0]=0;
    s^=s;
    ans^=ans;
    for (i=1;i<=n;i++)
    {
      scanf("%d",&x);
      s+=x;
      if (s>=0)
        s=s%m;
      else
        s=(s%m+m)%m;
      if (a[s]==-1)
        a[s]=i;
      else
      {
        if (i-a[s]>ans)
          ans=i-a[s];
      }
    }
    printf("%d\n",ans);
  }
  return 0;
}