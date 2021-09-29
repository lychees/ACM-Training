//By ytl 2014-1-6
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 550
#define M (N*4)
using namespace std;

const int xo[]={-1,1,0,0};
const int yo[]={0,0,-1,1};

int Sx,Sy,Tx,Ty,n,allX,allY,COLOR;
int vis[M][M],cant[M][M][4];

void read(int &a){
    a=0;
    char c=getchar();
    while (c<=32) c=getchar();
    while (c>32){
        a=a*10+c-'0';
        c=getchar();
    }
}

struct Line{
    int x1,y1,x2,y2,xa,xb,ya,yb;
    void input(){
        read(x1);read(y1);read(x2);read(y2);
        if (x1>x2) swap(x1,x2);
        if (y1>y2) swap(y1,y2);
        xa=x1+1;xb=x2+1;
        ya=y1+1;yb=y2+1;
    }
    
}line[N];

struct data{
    int x,y;
    data(int x=0,int y=0):x(x),y(y){};
}Q[M*M];

namespace LSH{
    int od[M];
    int look(int x){
        int l=1,r=od[0],mid;
        while (l<r){
            mid=(l+r)>>1;
            if (od[mid+1]>x) r=mid;else l=mid+1;
        }
        return l;
    }
    void lsh(){
        od[++od[0]]=Sx;od[++od[0]]=Sx+1;
        od[++od[0]]=Tx;od[++od[0]]=Tx+1;
        for (int i=1;i<=n;i++){
            od[++od[0]]=line[i].x1;
            od[++od[0]]=line[i].xa;
            od[++od[0]]=line[i].x2;
            od[++od[0]]=line[i].xb;    
        }
        sort(od+1,od+od[0]+1);
        od[0]=unique(od+1,od+od[0]+1)-(od+1);
        allX=od[0];
        Sx=look(Sx);Tx=look(Tx);
        for (int i=1;i<=n;i++){
            line[i].x1=look(line[i].x1);
            line[i].xa=look(line[i].xa);
            line[i].x2=look(line[i].x2);
            line[i].xb=look(line[i].xb);
        }
        
        od[0]=0;
        od[++od[0]]=Sy;od[++od[0]]=Sy+1;
        od[++od[0]]=Ty;od[++od[0]]=Ty+1;
        for (int i=1;i<=n;i++){
            od[++od[0]]=line[i].y1;
            od[++od[0]]=line[i].ya;
            od[++od[0]]=line[i].y2;
            od[++od[0]]=line[i].yb;    
        }
        sort(od+1,od+od[0]+1);
        od[0]=unique(od+1,od+od[0]+1)-(od+1);
        allY=od[0];
        Sy=look(Sy);Ty=look(Ty);
        for (int i=1;i<=n;i++){
            line[i].y1=look(line[i].y1);
            line[i].ya=look(line[i].ya);
            line[i].y2=look(line[i].y2);
            line[i].yb=look(line[i].yb);
        }
    }
}
using namespace LSH;

void preDeal(){
    COLOR+=2;
    for (int i=0;i<=allY;i++) vis[0][i]=COLOR,vis[allX+1][i]=COLOR;
    for (int i=0;i<=allX;i++) vis[i][0]=COLOR,vis[i][allY+1]=COLOR; 
    for (int i=1;i<=n;i++){
        if (line[i].x1==line[i].x2){
            int x=line[i].x1;
            for (int y=line[i].y1+1;y<=line[i].y2;y++){
                cant[x][y][1]=1;
                cant[x+1][y][0]=1;
            }
        }
        if (line[i].y1==line[i].y2){
            int y=line[i].y1;
            for (int x=line[i].x1+1;x<=line[i].x2;x++){
                cant[x][y][3]=1;
                cant[x][y+1][2]=1;
            } 
        }
    }
}
int bfs(){
    int p2=0;
    vis[Sx][Sy]=COLOR;
    vis[Sx+1][Sy]=COLOR;
    vis[Sx][Sy+1]=COLOR;
    vis[Sx+1][Sy+1]=COLOR;
    Q[++p2]=data(Sx,Sy);
    Q[++p2]=data(Sx+1,Sy);
    Q[++p2]=data(Sx,Sy+1);
    Q[++p2]=data(Sx+1,Sy+1);
    if (vis[Tx][Ty]==COLOR||vis[Tx+1][Ty]==COLOR||vis[Tx][Ty+1]==COLOR||vis[Tx+1][Ty+1]==COLOR) return 0;
    vis[Tx][Ty]=COLOR+1;
    vis[Tx+1][Ty]=COLOR+1;
    vis[Tx][Ty+1]=COLOR+1;
    vis[Tx+1][Ty+1]=COLOR+1;
    for (int p1=1;p1<=p2;p1++){
        int x=Q[p1].x,y=Q[p1].y;
        for (int i=0;i<4;i++) if (!cant[x][y][i]){
            int nx=x+xo[i];
            int ny=y+yo[i];
            if (vis[nx][ny]!=COLOR){
                if (vis[nx][ny]==COLOR+1){
                    return 0;
                }
                vis[nx][ny]=COLOR;
                Q[++p2]=data(nx,ny);
            }
        }    
    }
    int step=0;
    while (1){
        step++;
        int el=p2;
        for (int i=1;i<=el;i++){
            int x=Q[i].x,y=Q[i].y;
            for (int i=0;i<4;i++){
                int nx=x+xo[i];
                int ny=y+yo[i];
                if (vis[nx][ny]!=COLOR){
                    if (vis[nx][ny]==COLOR+1){
                        return step;
                    }
                    vis[nx][ny]=COLOR;
                    Q[++p2]=data(nx,ny);
                }
            }
        }
        int er=p2;p2=0;
        for (int i=el+1;i<=er;i++) Q[++p2]=Q[i];
        for (int p1=1;p1<=p2;p1++){
            int x=Q[p1].x,y=Q[p1].y;
            for (int i=0;i<4;i++) if (!cant[x][y][i]){
                int nx=x+xo[i];
                int ny=y+yo[i];
                if (vis[nx][ny]!=COLOR){
                    if (vis[nx][ny]==COLOR+1){
                        return step;
                    }
                    vis[nx][ny]=COLOR;
                    Q[++p2]=data(nx,ny);
                }
            }            
        }       
    }
    return -1;
}
void lastDeal(){
    for (int i=1;i<=n;i++){
        if (line[i].x1==line[i].x2){
            int x=line[i].x1;
            for (int y=line[i].y1+1;y<=line[i].y2;y++){
                cant[x][y][1]=0;
                cant[x+1][y][0]=0;
            }
        }
        if (line[i].y1==line[i].y2){
            int y=line[i].y1;
            for (int x=line[i].x1+1;x<=line[i].x2;x++){
                cant[x][y][3]=0;
                cant[x][y+1][2]=0;
            } 
        }
    }
}
int main(){
    freopen("cross.in","r",stdin);
    freopen("cross.out","w",stdout);
    int cas=0;
    while (scanf("%d",&n)!=EOF&&n){
        for (int i=1;i<=n;i++){
            line[i].input();
        }
        read(Sx);read(Sy);read(Tx);read(Ty);
        lsh();
        preDeal();
        printf("City %d\nPeter has to cross %d streets\n",++cas,bfs());
        lastDeal();
    }
    return 0;
}
