#include<stdio.h>

#include<iostream>

#include<algorithm>

#include<string.h>

#include<vector>

using namespace std;



//************************************************

const int MAXN=2505;//这个值要超过两边个数的较大者，因为有linker
int linker[MAXN];
bool used[MAXN];
vector<int>map[MAXN];
int uN;
bool dfs(int u)
{
    for(int i=0;i<map[u].size();i++)
    {
        if(!used[map[u][i]])
        {
            used[map[u][i]]=true;
            if(linker[map[u][i]]==-1||dfs(linker[map[u][i]]))
            {
                linker[map[u][i]]=u;
                return true;
            }
        }
    }
    return false;
}
int hungary()
{
    int u;
    int res=0;
    memset(linker,-1,sizeof(linker));
    for(u=0;u<uN;u++)
    {
        memset(used,false,sizeof(used));
        if(dfs(u)) res++;
    }
    return res;
}
pair<int,int>p1[MAXN];
pair<int,int>p2[MAXN];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    int x,y;
    while(scanf("%d%d",&n,&m)==2)
    {
        if(n==0 &&m==0)break;
        for(int i = 0;i < n;i++)
        {
            scanf("%d%d",&x,&y);
            p1[i]= make_pair(x,y);
        }
        for(int i = 0;i < m;i++)
        {
            scanf("%d%d",&x,&y);
            p2[i]= make_pair(x,y);
        }
        uN = n;
        for(int i = 0;i < n;i++)
            map[i].clear();
        for(int i = 0;i < n;i++)
        {
            for(int j = 0;j < m;j++)
            {
                int x1 = p1[i].first;
                int y1 = p1[i].second;
                int x2 = p2[j].first;
                int y2 = p2[j].second;
                if( (x1==x2 && y1==y2)
                   ||(x1==x2 && y1==y2+1)
                   ||(x1+1==x2 && y1==y2)
                   ||(x1+1==x2 && y1==y2+1)
                   )
                    map[i].push_back(j);
            }
        }
        int ans = n+m-hungary();
        printf("%d\n",ans);
    }
    return 0;
}







