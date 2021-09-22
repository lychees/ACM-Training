#include<cstdio>
#include<cstring>
const int N = 205;
const int M = 9;
const int INF = 1000000005;
int px[M],py[M],dp[N][N][4],k,d[M][4][M][4];
int c[4][2]={1,0,0,1,-1,0,0,-1},n,m;   
char g[N][N];
int q[N*N*4+10][3],ddp[1<<7][M][4];
void work(int x,int y,int zt)
{
    int i,j,h;
    for(i=0;i<m;i++)for(j=0;j<n;j++)for(h=0;h<4;h++)dp[i][j][h]=INF;
    dp[x][y][zt]=0;
    int tx=x+c[zt][0];
    int ty=y+c[zt][1];
    int tz=zt;
    while(tx>=0&&tx<m&&ty>=0&&ty<n&&g[tx][ty]!='#')
    {
        if(dp[tx][ty][tz]<=0)break;
        dp[tx][ty][tz]=0;
        if(g[tx][ty]=='L'&&tz!=3)
        {
            tz=3;
        }
        else if(g[tx][ty]=='R'&&tz!=1)
        {
            tz=1;
        }
        else if(g[tx][ty]=='U'&&tz!=2)
        {
            tz=2;
        }
        else if(g[tx][ty]=='D'&&tz!=0)
        {
            tz=0;
        }
        else
        {
            tx+=c[tz][0];
            ty+=c[tz][1];
        }
    }
    if(tx>=0&&tx<m&&ty>=0&&ty<n&&g[tx][ty]=='#')
    {
        tx-=c[tz][0];
        ty-=c[tz][1];
    }
    else return ;
    int t=0,w=1;
    q[0][0]=tx;
    q[0][1]=ty;
    q[0][2]=tz;
    //printf("x:%d y:%d zt:%d tx:%d ty:%d tz:%d \n",x,y,zt,tx,ty,tz);
    while(t<w)
    {
        int nx=q[t][0],ny=q[t][1],nz=q[t][2],dep=dp[nx][ny][nz]+1;
        t++;
        for(i=0;i<4;i++)if(i!=nz)
        {
            if(dp[nx][ny][i]<=dep)continue;
            dp[nx][ny][i]=dep;
            int tx=nx+c[i][0];
            int ty=ny+c[i][1];
            int tz=i;
            while(tx>=0&&tx<m&&ty>=0&&ty<n&&g[tx][ty]!='#')
            {
                if(dp[tx][ty][tz]<=dep)break;
                dp[tx][ty][tz]=dep;
                //printf("tx:%d ty:%d tz:%d dep:%d \n",tx,ty,tz,dep);
                if(g[tx][ty]=='L'&&tz!=3)
                {
                    tz=3;
                }
                else if(g[tx][ty]=='R'&&tz!=1)
                {
                    tz=1;
                }
                else if(g[tx][ty]=='U'&&tz!=2)
                {
                    tz=2;
                }
                else if(g[tx][ty]=='D'&&tz!=0)
                {
                    tz=0;
                }
                else
                {
                    tx+=c[tz][0];
                    ty+=c[tz][1];
                }
            }
            if(tx>=0&&tx<m&&ty>=0&&ty<n&&g[tx][ty]=='#')
            {
                tx-=c[tz][0];
                ty-=c[tz][1];
                q[w][0]=tx;
                q[w][1]=ty;
                q[w][2]=tz;
                w++;
            }
        }
    }
}
int main()
{
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int i,j,h;
    while(~scanf("%d%d",&m,&n))
    {
        k=1;
        int ex,ey;
        for(i=0;i<m;i++)scanf("%s",g[i]);
        for(i=0;i<m;i++)
        {
            for(j=0;j<n;j++)
            {
                if(g[i][j]=='S')
                {
                    px[0]=i;
                    py[0]=j;
                }
                else if(g[i][j]=='K')
                {
                    px[k]=i;
                    py[k]=j;
                    k++;
                }
                else if(g[i][j]=='E')
                {
                    ex=i;
                    ey=j;
                }
            }
        }
        px[k]=ex;
        py[k]=ey;
        for(i=0;i<k;i++)
        {
            for(j=0;j<4;j++)
            {
                work(px[i],py[i],j);
                for(int i1=0;i1<=k;i1++)
                {
                    for(int j1=0;j1<4;j1++)
                    {
                        d[i][j][i1][j1]=dp[px[i1]][py[i1]][j1];
                        /*if(dp[px[i1]][py[i1]][j1]!=INF)
                        {
                            printf("i:%d j:%d i1:%d j1:%d dis:%d \n",i,j,i1,j1,dp[px[i1]][py[i1]][j1]);
                        }*/
                    }
                }
            }
        }
        for(i=0;i<(1<<(k-1));i++)for(j=0;j<k;j++)for(h=0;h<4;h++)ddp[i][j][h]=INF;
        for(i=0;i<4;i++)
        {
            ddp[0][0][i]=1;
        }
        for(i=0;i<(1<<(k-1));i++)
        {
            for(j=0;j<k;j++)
            {
                for(h=0;h<4;h++)
                {
                    int v=ddp[i][j][h];
                    if(v==INF)continue;
                    for(int j1=1;j1<k;j1++)
                    {
                        for(int h1=0;h1<4;h1++)
                        {
                            int i1=(i|(1<<(j1-1)));
                            if(ddp[i1][j1][h1]>v+d[j][h][j1][h1])ddp[i1][j1][h1]=v+d[j][h][j1][h1];
                        }
                    }
                }
            }
        }
        int ret=INF;
        for(j=0;j<k;j++)
        {
            for(h=0;h<4;h++)
            {
                for(i=0;i<4;i++)
                {
                    if(ret>ddp[(1<<(k-1))-1][j][h]+d[j][h][k][i])ret=ddp[(1<<(k-1))-1][j][h]+d[j][h][k][i];
                }
            }
        }
        if(ret==INF)ret=-1;
        printf("%d\n",ret);
    }
    return 0;
}
