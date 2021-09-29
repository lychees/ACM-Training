#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
using namespace std;
typedef double dll;

const int maxn = 200;
const dll pi = 3.1415926535897932384626433832795;

int n,w,h;
int m[maxn],d[maxn];
dll get_start(int ask){
    int x = ask%100,y = ask/100;
    int posx = d[x],posy = y*h-h;
    dll ans = 0.0;
    for(int i=1;i<x;i++){
        int nowx = d[i]+w,nowy = m[i]*h;
        if(ans < dll(nowy-posy)/dll(posx-nowx))
            ans = dll(nowy-posy)/dll(posx-nowx);
        }
    //cout<<ans<<endl;
    ans = atan(ans)*180.0/pi;
    return ans;
    }
dll get_end(int ask){
    int x = ask%100,y = ask/100;
    int posx = d[x]+w,posy = y*h-h;
    dll ans = 0.0;
    for(int i=x+1;i<=n;i++){
        int nowx = d[i],nowy = m[i]*h;
        if(ans < dll(nowy-posy)/dll(nowx-posx))
            ans = dll(nowy-posy)/dll(nowx-posx);
        }
    ans = 180.0-atan(ans)*180.0/pi;
    return ans;
    }
void output(int second){
    second += 5*3600+37*60;
    printf("%02d:",second/3600);
    second%=3600;
    printf("%02d:",second/60);
    second%=60;
    printf("%02d",second);
    }
bool isok(int ask){
    return ask>=0 && ask%100<=n && ask/100<=m[ask%100];
    }
int main()
{
    freopen("sun.in","r",stdin);
    freopen("sun.out","w",stdout);
    int kase = 0;
    while(scanf("%d",&n)==1 && n){
        printf("Apartment Complex: %d\n",++kase);
        scanf("%d%d",&w,&h);
        scanf("%d",&m[1]);
        for(int i=2;i<=n;i++)
            scanf("%d%d",&d[i],&m[i]);
        for(int i=2;i<=n;i++)
            d[i]+=d[i-1]+w;
        
        int ask;
        while(scanf("%d",&ask)==1 && ask){
            printf("Apartment %d: ",ask);
            if(!isok(ask)){
                printf("Does not exist\n");
                continue;
                }
            dll start=get_start(ask),end = get_end(ask);
            dll pre = (12.0*3600.0+40.0*60.0)/180.0;
            output(floor(start*pre));printf(" - ");output(floor(end*pre));
            printf("\n");
            }
        }
    
    return 0;   
}
