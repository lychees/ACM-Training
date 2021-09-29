//By ytl 2014-1-5
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define L 2500
#define N 200005
using namespace std;

const int montho[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
int n,m,po,totAns;
int idYear[N],idNum[L][L],da[N],db[N],v[N];

int getDays(int year,int month){
    if (month==2&&((year%4==0&&year%100!=0)||(year%400==0))) return 29;
    return montho[month]; 
}
int transNum(int a){
    return idNum[a/10000][a%10000];
}
int transYear(int a){
    return idYear[a];
}
void addA(int a,int b){
    da[a]++;da[b+1]--;
} 
void addB(int a,int b){
    db[a]++;db[b+1]--;
}
void preDeal(){
    for (int year=1700;year<=2100;year++)
        for (int month=1;month<=12;month++){
            int DD=getDays(year,month); 
            for (int day=1;day<=DD;day++){
                po++;
                int x=year,y=month*100+day;
                idNum[x][y]=po;
                idYear[po]=x*10000+y;
            }
        }
}
void init(){
    for (int i=1;i<=po+1;i++) da[i]=db[i]=0;
    totAns=0;
}
void output(int x){
    int year=x/10000,month=(x%10000)/100,day=x%100;
    printf("%d/%d/%d",month,day,year);
}
void work(){
    init();
    for (int i=1;i<=n;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        a=transNum(a);b=transNum(b);
        addA(a,b);
    }
    for (int i=1;i<=m;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        a=transNum(a);b=transNum(b);
        addB(a,b);
    }
    int l=0;
    for (int i=1;i<=po+1;i++){
        da[i]+=da[i-1];
        db[i]+=db[i-1];
        v[i]=(db[i]?1:0)-(da[i]?1:0);
        if (v[i]==1&&v[i-1]!=1) l=i;
        if (v[i]!=1&&v[i-1]==1){
            if (l!=i-1){
                printf("    ");
                output(transYear(l));
                printf(" to ");
                output(transYear(i-1));
                printf("\n");
            }else{
                printf("    ");
                output(transYear(l));
                printf("\n");
            }
            totAns++;
        }
    }
    if (!totAns) printf("    No additional quotes are required.\n");
}
int main(){
    freopen("insert.in","r",stdin);
    freopen("insert.out","w",stdout);
    preDeal();
    int cas=0;
    while (scanf("%d%d",&n,&m)!=EOF&&(n||m)){
        printf("Case %d:\n",++cas);
        work();
        printf("\n");
    }
    return 0;
}
