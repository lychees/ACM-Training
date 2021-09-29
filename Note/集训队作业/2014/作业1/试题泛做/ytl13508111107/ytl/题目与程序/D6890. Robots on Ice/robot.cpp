//By ytl 2014-1-13
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 15
using namespace std;

const int xo[]={0,0,1,-1};
const int yo[]={1,-1,0,0};

int n,m,ans;
int checkStep[10],checkX[10],checkY[10],bj[N][N],use[N][N],recx[N*N],recy[N*N];

void printWay(int n){
    for (int i=1;i<=n;i++) printf("%d %d\n",recx[i]-1,recy[i]-1);
    printf("\n");
}
inline bool check(int x,int y){
    if (!use[x+1][y]&&!use[x-1][y]&&use[x][y-1]&&use[x][y+1]) return false;
    if (use[x+1][y]&&use[x-1][y]&&!use[x][y-1]&&!use[x][y+1]) return false;
    return true;
}
void search(int x,int y,int step,int jd){ 
    int dis=abs(x-checkX[jd])+abs(y-checkY[jd]);
    if (dis>checkStep[jd]-step) return;
    if (!dis&&bj[x][y]!=jd) return;
    if (bj[x][y]){
        if (bj[x][y]!=jd) return;
        if (step!=checkStep[jd]) return;
        else jd++;
    }
    //if (step==checkStep[jd]) jd++;
    if (jd==5){
        ans++;
        return;
    }
    use[x][y]=1;
    for (int k=0;k<4;k++){
        int nx=x+xo[k],ny=y+yo[k];
        if (!use[nx][ny]&&check(nx,ny)){
            use[nx][ny]=1;
            search(nx,ny,step+1,jd);
            use[nx][ny]=0;        
        }
    }
}
void init(){
    for (int i=0;i<=n+1;i++)
        for (int j=0;j<=m+1;j++)
            use[i][j]=2;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            use[i][j]=bj[i][j]=0;
    ans=0;
}
int main(){
    freopen("robot.in","r",stdin);
    freopen("robot.out","w",stdout);
    int cas=0;
    while (scanf("%d%d",&n,&m)!=EOF&&(n||m)){
        init();
        for (int i=1;i<=3;i++){
            checkStep[i]=n*m*i/4;
            scanf("%d%d",&checkX[i],&checkY[i]);
            checkX[i]++;checkY[i]++;
        }
        checkStep[4]=n*m;
        checkX[4]=1;
        checkY[4]=2;
        for (int i=1;i<=4;i++) bj[checkX[i]][checkY[i]]=i;
        search(1,1,1,1);
        printf("Case %d: %d\n",++cas,ans);
    }
    return 0;
}

