#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <bitset>
#include <ctime>
#include <map>
#include <queue>
#include <set>
using namespace std;
 
const int maxn=200000+15;
int n,a[maxn];
int getint()
{
    char ch;
    for (ch=getchar();!isdigit(ch);ch=getchar());
    int maxx=0;
    for (;isdigit(ch);maxx=maxx*10+ch-'0',ch=getchar());
    return maxx;
}
priority_queue <int> que;
int main()
{
    int G;
    G=getint();
    while (G--)
    {
        n=getint();
        for (int i=1;i<=n;i++) a[i]=getint();
        while (!que.empty()) que.pop();
        if (n==1)
        {
            printf("0\n");
            continue;
        }
        int ans=1;
        int last=a[1]-1;
        for (int i=2;i<=n;i++)
         if (last) last--,que.push(a[i]);
          else
          {
            ans++;
            if (que.empty() || que.top()<2)
            {
                ans=-1;
                break;
            }
            last=que.top()-2;
            que.pop();
            que.push(a[i]);
          }
        printf("%d\n",ans);
    }
    return 0;
}
