/*
ID:huangta3
PROG:first
LANG:C++
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <list>
#include <queue>
#include <vector>
#include <ctime>
#include <set>
#include <bitset>
#include <deque>
#include <fstream>
#include <stack>
#include <map>
#include <utility>
#include <cassert>
#include <string>
#include <iterator>
#include <cctype>
using namespace std;
const int maxn=300100,root=0;
struct data
{
    int flag,next[26];
}g[maxn];
char a[maxn],s[maxn];
bool Map[30][30];
int n,len[30003],N=0,tot=0,ans[30003],cnt=0,st[30003];
int vis[30],dfn[30],low[30],stk[30],ind,top,Link[30],pre[900],t[900];
bool flag;
int get()
{
    int f=0,v=0;char ch;
    while(!isdigit(ch=getchar()))if(ch=='-')break;
    if(ch=='-')f=1;else v=ch-48;
    while(isdigit(ch=getchar()))v=v*10+ch-48;
    if(f==1)return -v;else return v;
}
 
void tarjan(int x)
{
    low[x]=dfn[x]=++ind;
    stk[++top]=x;vis[x]=1;
    for(int i=Link[x];i>0;i=pre[i])
    {
        if(!vis[t[i]])
        {
            tarjan(t[i]);
            low[x]=min(low[x],low[t[i]]);
        }if(vis[t[i]]==1)low[x]=min(low[x],low[t[i]]);
    }
    if(low[x]==dfn[x])
    {
        int size=0;
        while(stk[top]!=x)vis[stk[top--]]=2,size++;
        size++,vis[stk[top--]]=2;
        if(size>1)flag=0;
    }
}
 
int main()
{
    n=get();
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s+1);
        len[i]=strlen(s+1);st[i]=N+1;
        int k=root,data;
        for(int j=1;j<=len[i];j++)
        {
            a[++N]=s[j];
            data=s[j]-'a';
            if(g[k].next[data]==0)g[k].next[data]=++tot;
            k=g[k].next[data];
        }
        g[k].flag=1;
    }
    int p=0;
    for(int i=1;i<=n;i++)
    {
        memset(Map,0,sizeof(Map));
        int node=root,st=p+1;
        flag=1;
        for(int j=1;j<=len[i];j++)
        {
            int data=a[++p]-'a';
            for(int k=0;k<26;k++)
                if(g[node].next[k]!=0&&k!=data)Map[data][k]=1;
            node=g[node].next[data];
            if(g[node].flag&&j!=len[i])flag=0;
        }
        if(!flag)continue;
        memset(Link,0,sizeof(Link));tot=0;
        for(int j=0;j<26;j++)
            for(int k=0;k<26;k++)
                if(Map[j][k])pre[++tot]=Link[j],Link[j]=tot,t[tot]=k;
        memset(vis,0,sizeof(vis));
        ind=top=0;
        for(int j=0;j<26&&flag;j++)
            if(!vis[j])tarjan(j);
        if(flag)ans[++cnt]=i;
    }
    printf("%d\n",cnt);
    for(int i=1;i<=cnt;i++)
    {
        for(int j=1;j<=len[ans[i]];j++)putchar(a[st[ans[i]]+j-1]);
        puts("");
    }
    return 0;
}
