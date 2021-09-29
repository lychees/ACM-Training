#include <stdio.h>
#include <string.h>
#define abs(x) ((x)>0?(x):-(x))
int ans;

int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};
int mark[10][10],oX[10],oY[10],pos[10];
int should[10][10];
int N,M;
bool isin(int x,int y){
    return x>=0&&x<N&&y>=0&&y<M;
}
bool cut(int x,int y){
    int can[4],i;
    for (i=0;i<4;i++)
    {
        int nx = x+dx[i], ny = y+dy[i];
        if (isin(nx,ny)&&mark[nx][ny]==0)
            can[i] = 1;
        else can[i] = 0;
    }
    if (can[0]&&can[2]&&!can[1]&&!can[3]) return 1;
    if (can[1]&&can[3]&&!can[0]&&!can[2]) return 1;
    return 0;
}
void dfs(int x,int y,int dep){
    int i;
    //printf("%d %d : %d\n",x,y,dep);
    //scanf("%d",&i);
    for (i=0;i<4;i++)
        if (pos[i]>=dep) break;
    int dis = abs(x-oX[i])+abs(y-oY[i]);
    if (dis>pos[i]-dep) return ;
    if (dep!=pos[i]&&dis==0) return ;
    if (should[x][y]>0&&dis!=0) return ;
    if (dep==N*M){
        ans++;
        return ;
    }
    for (i=0;i<4;i++){
        int nx = x+dx[i], ny = y+dy[i];
        if (isin(nx,ny)&&
        !cut(nx,ny)&&
        !mark[nx][ny]){
            mark[nx][ny] = 1;
            dfs(nx,ny,dep+1);
            mark[nx][ny] = 0;
        }
    }
}
int main(){
    freopen("robot.in","r",stdin);
    freopen("bc.out","w",stdout);
    int i,tcas = 1;
    while(scanf("%d%d",&N,&M)!=EOF){
        if (N==0&&M==0) break;
        memset(should,0,sizeof(should));
        for (i=0;i<3;i++)
            scanf("%d%d",&oX[i],&oY[i]);
        for (i=1;i<4;i++)
            pos[i-1] = i*N*M/4;
        
        pos[3] = N*M;
        oX[3] = 0, oY[3] = 1;
        memset(should,0,sizeof(should));
        for (i=0;i<4;i++)
            should[oX[i]][oY[i]] = pos[i];
        ans = 0;
        memset(mark,0,sizeof(mark));
        mark[0][0] = 1;
        dfs(0,0,1);      
        printf("Case %d: %d\n",tcas++, ans);
    }
}  
