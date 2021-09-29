#include <stdio.h>
#include <string.h>
#include <queue>
#define MAXD 13
#define MAX 100003

using namespace std;

int vis[MAX][2][MAXD];
int preva[MAX][2][MAXD][2],prevb[MAX][2][MAXD][2],prevc[MAX][2][MAXD][2],prevd[MAX][2][MAXD][2];

int main()
{
    freopen("number.in","r",stdin);
    freopen("bc.out","w",stdout);
    int n,n1,cnt,prev,i,a,b,c,d,j,k,l,i1,j1,k1,l1,na,nb,nc,nd,dig1,dig2,cnt1,cnt2;
    bool fl;
    while (scanf("%d",&n)==1&&n)
    {
        n1=n;
        cnt=0;
        prev=-1;
        while (n1)
        {
            if (n1%10!=prev) cnt++;
            prev=n1%10;
            n1/=10;
        }
        fl=0;
        if (cnt==2) fl=1;
        memset(vis,0,sizeof(vis));
        memset(preva,-1,sizeof(prev));
        queue<int> q1,q2,q3,q4;
        for (i=1;i<10;i++)
        {
            vis[i%n][0][i]=1;
            q1.push(i%n);
            q2.push(0);
            q3.push(i);
            q4.push(0);
        }
        while (!q1.empty())
        {
            a=q1.front();
            b=q2.front();
            c=q3.front();
            d=q4.front();
            q1.pop();
            q2.pop();
            q3.pop();
            q4.pop();
            if (a==0&&b==1)
            {
                if (fl) fl=0;
                else
                {
                    i=a;
                    j=b;
                    k=c;
                    l=d;
                    break;
                }
            }
            for (i=0;i<10;i++)
            {
                if (i!=c&&b==1) continue;
                if (i==c)
                {
                    na=(a*10+i)%n;
                    nb=b;
                    nc=i;
                    if (!vis[na][nb][nc])
                    {
                        vis[na][nb][nc]=1;
                        nd=0;
                        preva[na][nb][nc][nd]=a;
                        prevb[na][nb][nc][nd]=b;
                        prevc[na][nb][nc][nd]=c;
                        prevd[na][nb][nc][nd]=d;
                        q1.push(na);
                        q2.push(nb);
                        q3.push(nc);
                        q4.push(nd);
                    }
                    else if (vis[na][nb][nc]==1)
                    {
                        vis[na][nb][nc]=2;
                        nd=1;
                        preva[na][nb][nc][nd]=a;
                        prevb[na][nb][nc][nd]=b;
                        prevc[na][nb][nc][nd]=c;
                        prevd[na][nb][nc][nd]=d;
                        q1.push(na);
                        q2.push(nb);
                        q3.push(nc);
                        q4.push(nd);
                    }
                }
                else
                {
                    na=(a*10+i)%n;
                    nb=1;
                    nc=i;
                    if (!vis[na][nb][nc])
                    {
                        vis[na][nb][nc]=1;
                        nd=0;
                        preva[na][nb][nc][nd]=a;
                        prevb[na][nb][nc][nd]=b;
                        prevc[na][nb][nc][nd]=c;
                        prevd[na][nb][nc][nd]=d;
                        q1.push(na);
                        q2.push(nb);
                        q3.push(nc);
                        q4.push(nd);
                    }
                    else if (vis[na][nb][nc]==1)
                    {
                        vis[na][nb][nc]=2;
                        nd=1;
                        preva[na][nb][nc][nd]=a;
                        prevb[na][nb][nc][nd]=b;
                        prevc[na][nb][nc][nd]=c;
                        prevd[na][nb][nc][nd]=d;
                        q1.push(na);
                        q2.push(nb);
                        q3.push(nc);
                        q4.push(nd);
                    }
                }
            }
        }
        cnt1=cnt2=0;
        while (preva[i][j][k][l]!=-1)
        {
            if (j==1)
            {
                dig2=k;
                cnt2++;
            }
            else
            {
                dig1=k;
                cnt1++;
            }
            i1=preva[i][j][k][l];
            j1=prevb[i][j][k][l];
            k1=prevc[i][j][k][l];
            l1=prevd[i][j][k][l];
            i=i1;
            j=j1;
            k=k1;
            l=l1;
        }
        //dig1=k;
        //cnt1++;
        printf("%d: %d %d %d %d\n",n,cnt1,dig1,cnt2,dig2);
    }
    return 0;
}
