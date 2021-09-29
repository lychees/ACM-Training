#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long LL;
const int maxn=303;
bool a[maxn][maxn];
short s[maxn][maxn],u[maxn][maxn][maxn],d[maxn][maxn][maxn];
int f[maxn][maxn],n;
LL ans=0;
inline int get()
{
    int f=0,v=0;char ch;
    while(!isdigit(ch=getchar()))if(ch=='-')break;
    if(ch=='-')f=1;else v=ch-48;
    while(isdigit(ch=getchar()))v=v*10+ch-48;
    if(f==1)return -v;else return v;
}
int main()
{
    n=get();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            char ch;while(ch=getchar(),ch!='.'&&ch!='*');
            a[i][j]=ch=='.';s[i][j]=s[i][j-1]+(ch=='*');
        }
    for(int i=1;i<=n;i++)
        for(int j1=1;j1<=n;j1++)
            for(int j2=j1+1;j2<=n;j2++)
            {
                if(!(a[i][j1]&&a[i][j2])){u[i][j1][j2]=-1;continue;}
                if(i>1&&u[i-1][j1][j2]!=-1)u[i][j1][j2]=u[i-1][j1][j2]+1;
                else u[i][j1][j2]=s[i][j2]==s[i][j1-1]?0:-1;
            }
    for(int i=n;i>=1;i--)
    {
        memset(f,-1,sizeof(f));
        for(int k=2;k<=n;k++)
            for(int j1=1;j1+k<=n;j1++)
            {
                int j2=j1+k,t=(k-1)*int(u[i][j1][j2]-1);
                if(u[i][j1][j2]<=1||s[i][j2]!=s[i][j1-1])t=-1;
                f[j1][j2]=max(f[j1][j2-1],f[j1+1][j2]);
                f[j1][j2]=max(f[j1][j2],t);
            }
        for(int j1=1;j1<=n;j1++)
            for(int j2=j1+1;j2<=n;j2++)
            {
                if(!(a[i][j1]&&a[i][j2])){d[i][j1][j2]=-1;continue;}
                if(i<n&&d[i+1][j1][j2]!=-1)d[i][j1][j2]=d[i+1][j1][j2]+1;
                else d[i][j1][j2]=s[i][j2]==s[i][j1-1]?0:-1;
                if(j2-j1<2||d[i][j1][j2]<=1||f[j1][j2]<=0||s[i][j2]!=s[i][j1-1])continue;
                int t=(j2-j1-1)*int(d[i][j1][j2]-1);
                ans=max(ans,LL(t)*f[j1][j2]);
            }
    }
    if(ans==0)ans--;
    cout<<ans<<endl;
    return 0;
}
