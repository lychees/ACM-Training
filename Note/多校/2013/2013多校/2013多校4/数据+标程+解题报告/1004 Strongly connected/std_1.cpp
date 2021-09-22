#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#define inf 0x7fffffff
#define CL(a,b) memset(a,b,sizeof(a))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define N 1100
using namespace std;
vector<int >g[N];
bool  instack[N];
int stack[N],low[N],dnf[N],tmp=0,top=0;
int sum[N];
bool in[N],out[N];
int ans=inf;
void dfs(int root)
{
    dnf[root]=low[root]=++tmp;
    stack[top++]=root;
    instack[root]=true;
    vector<int >::iterator it;
    for(it=g[root].begin();it!=g[root].end();it++)
    {
        if(dnf[*it]==0)
        {
            dfs(*it);
            low[root]=MIN(low[root],low[*it]);
        }
        else if(instack[*it])
            low[root]=MIN(low[root],dnf[*it]);
    }
    if(dnf[root]==low[root])
    {
        sum[low[root]]=0;
        do
        {
            sum[low[root]]++;
            instack[stack[top-1]]=false;
         //   printf("%d\n",low[stack[top-1]]);
            top--;
        }while(stack[top]!=root);
    }
}
int main()
{
    int t;
    int cas=1;
    scanf("%d",&t);
    while(t--)
    {
        int x,y,i,j,k;
        int n,m;
        scanf("%d%d",&n,&m);
        ans=inf;tmp=0;top=0;
        CL(instack,false);
        CL(low,0);CL(in,false);
        CL(out,false);
        CL(dnf,0);
        for(i=1;i<=n;i++) 
        {
            g[i].clear();
          
        }
        for(i=0;i<m;i++)
        {
            scanf("%d%d",&x,&y);
            g[x].push_back(y);
        }
        for(i=1;i<=n;i++)
            if(dnf[i]==0)
                dfs(i);
    
        for(i=1;i<=n;i++)
        {
            int p=low[i];
            for(j=0;j<g[i].size();j++)
            {
                int pp=low[g[i][j]];
                if(p!=pp)
                {
                    out[p]=1;
                    in[pp]=1;
                }
            }
        }
        int ans=-1;
        int tn=n-ans;
        bool flag=false;
        for(i=1;i<=n;i++)
        {
            if(in[low[i]]&&out[low[i]]) continue;
            tn=n-sum[low[i]];
            if(tn!=0) flag=true;
           // printf("%d %d\n",sum[low[i]],tn*(tn-1)+sum[low[i]]*(sum[low[i]]-1)+sum[low[i]]*tn-m);
            ans=MAX(ans,tn*(tn-1)+sum[low[i]]*(sum[low[i]]-1)+sum[low[i]]*tn-m);
        }   
        printf("Case %d: ",cas++);
        if(flag==false)
            printf("-1\n");
        else
            printf("%d\n",ans);
        
    }
}