#include<cstdio>
#include<cstring>
const int N = 105;
int a[N][N];
int main()
{
    int T,n,m,i,j;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=m;j++)
            {
                scanf("%d",&a[i][j]);
            }
        }
        if(a[n][m])puts("Alice");
        else puts("Bob");
    }
    return 0;
}
