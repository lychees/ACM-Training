//By ytl 2013-12-17
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 105
using namespace std;

int map[N][N];
int line[N*N],w[N],tot,n;

void printMap(int map[N][N]){
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++)
            printf("%d ",map[i][j]);
        printf("\n");
    }
}
void printLine(int line[N]){
    printf("$");for (int i=1;i<=tot;i++) printf("%d ",line[i]);printf("\n");
}
void trans(int x1,int y1,int x2,int y2,int deep){
    int t=map[x1][y1],flag=1;
    for (int i=x1;i<=x2;i++) if (flag)
        for (int j=y1;j<=y2;j++) if (flag)
            if (map[i][j]!=t){
     //           printf("#%d %d %d\n",i,j,map[i][j]);
                flag=0;
                break;
            }
    if (flag){
        int x=0;
        for (int i=deep-1;i>=1;i--) x=x*5+w[i];
   //     printf("%d: %d %d %d %d %d\n",t,flag,x1,y1,x2,y2);
        if (t==1) line[++tot]=x;
        return;    
    } 
    int mx=(x1+x2)>>1;
    int my=(y1+y2)>>1;
    w[deep]=1;
    trans(x1,y1,mx,my,deep+1);
    w[deep]=2;
    trans(x1,my+1,mx,y2,deep+1);
    w[deep]=3;
    trans(mx+1,y1,x2,my,deep+1);
    w[deep]=4;
    trans(mx+1,my+1,x2,y2,deep+1);
}
bool tpMap(){
    int t=map[1][1],flag=1;
    for (int i=1;i<=n;i++) if (flag)
        for (int j=1;j<=n;j++) if (flag)
            if (map[i][j]!=t){
                flag=0;
                break;
            }
    if (flag){
        if (t==1){
            printf("0\n");
            printf("Total number of black nodes = 1\n");
        }else{
            printf("Total number of black nodes = 0\n");
        }
        return true;
    }
    return false;
}
void deal1(){
    char ch;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            scanf("%c",&ch);
            map[i][j]=ch-'0';
        }
        scanf("\n");
    }
    if (tpMap()) return;
    tot=0;
    trans(1,1,n,n,1);
    sort(line+1,line+tot+1);
    
    //printf("%d\n",-n);
    //for (int i=1;i<=tot;i++) printf("%d ",line[i]);printf("-1\n");
    for (int i=1;i<=tot;i++){
        printf("%d ",line[i]);
        if (i%12==0) printf("\n");
    }
    if (tot%12!=0) printf("\n");
    printf("Total number of black nodes = %d\n",tot);
}

bool tpLine(){
    if (tot==0){
        for (int i=1;i<=n;i++){
            for (int j=1;j<=n;j++)
                printf(".");
            printf("\n");
        }
        return true;
    }
    if (tot==1&&line[1]==0){
        for (int i=1;i<=n;i++){
            for (int j=1;j<=n;j++)
                printf("*");
            printf("\n");
        }
        return true;
    }
    return false;
}
void put(int w[N]){
    int x1=1,y1=1,x2=n,y2=n;
    for (int i=1;i<=w[0];i++){
        int mx=(x1+x2)>>1;
        int my=(y1+y2)>>1;
        switch(w[i]){
            case 1 :x2=mx;y2=my;
                    break;
            case 2 :y1=my+1;x2=mx;
                    break;
            case 3 :x1=mx+1;y2=my;
                    break;
            case 4 :x1=mx+1;y1=my+1;
                    break;
        }
    }
    for (int i=x1;i<=x2;i++)
        for (int j=y1;j<=y2;j++)
            map[i][j]=1;   
}
void trans(int x,int w[N]){
    w[0]=0;
    for (int i=x;i;i/=5) w[++w[0]]=i%5;
}
void output(){
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++)
            printf("%c",map[i][j]?'*':'.');
        printf("\n");
    }
}
void output22(){
    printf("%d\n",n);
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++)
            printf("%c",map[i][j]?'1':'0');
        printf("\n");
    }
}
void deal2(){
    tot=0;
    while (scanf("%d",&line[tot+1])!=EOF&&line[tot+1]!=-1) tot++;
    if (tpLine()) return;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            map[i][j]=0;
    for (int i=1;i<=tot;i++){
        trans(line[i],w);
        put(w);
    }
    output();
    //output22();
}
int main(){
    freopen("structure.in","r",stdin);
    freopen("structure.out","w",stdout);
    int cas=0;
    while (scanf("%d\n",&n)!=EOF&&n){
        printf("Image %d\n",++cas);
        if (n>0){
            deal1();
        }else{
            n=-n;
            deal2();
        }
        printf("\n");
    }
    return 0;
}
