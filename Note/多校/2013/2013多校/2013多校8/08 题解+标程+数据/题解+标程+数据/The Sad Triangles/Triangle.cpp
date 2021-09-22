#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

#define MaxLen 400000
//#define MaxLen 100
using namespace std;

struct RightTriangle
{
    long long apex, hei, tan;
    bool operator <(const RightTriangle &b) const
    {
        return apex<b.apex;
    }
} LeftTri[100010],RightTri[100010];

long long gcd(long long a, long long b)
{
    if (b==0)
        return a;
    return gcd(b, a%b);
}

long long MaxHeight[400010];

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    long long n, m, h;
  //  while (cin>>n>>m>>h)
    int CAS;
    scanf("%d",&CAS);
    for (int T=1; T<=CAS; T++)
    {
        scanf("%I64d%I64d%I64d", &n, &m, &h);
        h*=4;
        for (int i=1; i<=n; i++)
        {
           // cin>>LeftTri[i].apex>>LeftTri[i].tan>>LeftTri[i].hei;
            scanf("%I64d%I64d%I64d", &LeftTri[i].apex, &LeftTri[i].tan, &LeftTri[i].hei);
            LeftTri[i].apex*=4;
            LeftTri[i].hei*=LeftTri[i].tan*4;
        }
        for (int i=1; i<=m; i++)
        {
         //   cin>>RightTri[i].apex>>RightTri[i].tan>>RightTri[i].hei;
            scanf("%I64d%I64d%I64d", &RightTri[i].apex, &RightTri[i].tan, &RightTri[i].hei);
            RightTri[i].apex*=4;
            RightTri[i].hei*=RightTri[i].tan*4;
        }
        std::sort(LeftTri+1, LeftTri+n+1);
        std::sort(RightTri+1, RightTri+m+1);

        memset(MaxHeight, 0, sizeof(MaxHeight));
        for (long long i=MaxLen, j=n, One=0, Three=0; i>0; i--, One-=2, Three-=6)
        {
            while (j&&LeftTri[j].apex==i)
            {
                if (LeftTri[j].tan==1)
                    One=std::max(One, LeftTri[j].hei*2-1);
                else
                    Three=std::max(Three, LeftTri[j].hei*2-3);
                j--;
            }
            MaxHeight[i]=std::max(MaxHeight[i], std::max(One, Three));
        }
        for (long long i=1, j=1, One=0, Three=0; i<=MaxLen; i++, One-=2, Three-=6)
        {
            while (j<=m&&RightTri[j].apex==i-1)
            {
                if (RightTri[j].tan==1)
                    One=std::max(One, RightTri[j].hei*2-1);
                else
                    Three=std::max(Three, RightTri[j].hei*2-3);
                j++;
            }
            MaxHeight[i]=std::max(MaxHeight[i], std::max(One, Three));
        }
        long long ans=0;
        if (h>MaxLen)
            for (long long i=0; i<=h; i++)
                ans+=MaxHeight[i];
        else
        {
            long long sum=0;
            for (long long i=0; i<=h; i++)
                sum+=MaxHeight[i];
            ans=sum;
            for (long long i=h+1; i<=MaxLen; i++)
            {
                sum=sum-MaxHeight[i-h]+MaxHeight[i];
                ans=std::max(sum, ans);
            }
        }
        printf("Case #%d: ", T);
        printf("%.6f\n",ans/32.0);

        //long long temp=gcd(ans, 32);
      //  printf("%I64d/%I64d\n", ans/temp, 32/temp);
       // cout<<ans/temp<<"/"<<32/temp<<endl;

    }
    return 0;
}
