#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<queue>
#include<list>
#include<stack>
#include<set>
#include<map>
#include<string>
#include<algorithm>
using namespace std;

#define eps 1e-12
#define maxn 1100
#define maxm 1100000
#define inf 0x3f3f3f3f
#define PB push_back
#define MP make_pair

typedef struct{
    int len,sta;
}node;
node r[10],t[10];
int next[10][70000],pck[1010][3];
int mp[120][5];
bool f[5];
int main()
{
    freopen("network.in","r",stdin);
    freopen("bc.out","w",stdout);
    int n,m,i,j,k,l,p,q,ans,tmp,now,cnt=1;
    memset(f,true,sizeof(f));
    i=0;
    for(j=0;j<5;j++)
    {
        f[j]=false;
        for(k=0;k<5;k++)
            if(f[k])
            {
                f[k]=false;
                for(l=0;l<5;l++)
                    if(f[l])
                    {
                        f[l]=false;
                        for(p=0;p<5;p++)
                            if(f[p])
                            {
                                f[p]=false;
                                for(q=0;q<5;q++)
                                    if(f[q])
                                    {
                                        mp[i][0]=j;
                                        mp[i][1]=k;
                                        mp[i][2]=l;
                                        mp[i][3]=p;
                                        mp[i][4]=q;
                                        i++;
                                    }
                                f[p]=true;
                            }
                        f[l]=true;
                    }
                f[k]=true;
            }
        f[j]=true;
    }
    while(scanf("%d %d",&n,&m)!=EOF)
    {
        if(n==0&&m==0) break;
        for(i=0;i<n;i++)
        {
            scanf("%d",&r[i].len);
            r[i].sta=1;
        }
        for(i=0;i<m;i++)
        {
            scanf("%d %d %d",&pck[i][0],&pck[i][1],&pck[i][2]);
            pck[i][0]--;
        }
        ans=1000000000;
        for(i=0;i<120;i++)
        {
            memcpy(t,r,sizeof(node)*10);
            memset(next,0,sizeof(next));
            tmp=now=0;
            for(j=0;j<n;j++) f[j]=true;
            for(;j<5;j++) f[j]=false;
            for(j=0;j<5;j++)
                if(f[mp[i][j]])
                {
                    p=mp[i][j];
                    break;
                }
            for(k=0;k<m;k++)
            {
                next[pck[k][0]][pck[k][1]]=pck[k][2];
                if(pck[k][0]==p&&pck[k][1]==t[p].sta)
                {
                    for(q=pck[k][2]+1;next[p][q];q=next[p][q]+1);
                    now-=(q-pck[k][2]-1);
                    t[p].sta=q;
                    if(q<=t[p].len) continue;
                    f[p]=false;
                    while(1)
                    {
                        for(j+=1;j<5;j++)
                            if(f[mp[i][j]])
                            {
                                p=mp[i][j];
                                break;
                            }
                        if(j==5) break;
                        for(q=1;next[p][q];q=next[p][q]+1);
                        now-=(q-t[p].sta);
                        t[p].sta=q;
                        if(q<=t[p].len) break;
                        f[p]=false;
                    }
                }
                else{
                    now+=(pck[k][2]-pck[k][1]+1);
                    tmp=max(tmp,now);
                }
            }
            ans=min(ans,tmp);
        }
        printf("Case %d: %d\n\n",cnt++,ans);
    }
}
