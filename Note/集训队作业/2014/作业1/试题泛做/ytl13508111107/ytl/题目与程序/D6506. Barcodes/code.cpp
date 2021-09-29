//By ytl 2014-1-10
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 505
using namespace std;

int rec[12][5]={
{0,0,0,0,1},
{1,0,0,0,1},
{0,1,0,0,1},
{1,1,0,0,0},
{0,0,1,0,1},
{1,0,1,0,0},
{0,1,1,0,0},
{0,0,0,1,1},
{1,0,0,1,0},
{1,0,0,0,0},
{0,0,1,0,0},
{0,0,1,1,0}
};
char stt[]={'0','1','2','3','4','5','6','7','8','9','-','$'};

int n;
int ans1[N],ans2[N],b[N];
double a[N],W1,W2;
const double EPS=1e-6;
int dcmp(const double &a,double b){
    if (a-b>EPS) return 1;
    if (b-a>EPS) return -1;
    return 0;
}
bool check(int i,int k){
    for (int j=0;j<5;j++) if (rec[k][j]!=b[i+j]) return false;
    return true;
}
int getID(int a){
    for (int i=0;i<=11;i++) if (check(a,i)) return i;
    return -1; 
}
void print(int a[],int n){
    for (int i=1;i<=n;i++) printf("%d ",a[i]);printf("\n");
}
bool tryWide(double w){
    for (int i=1;i<=n;i++){
        if (dcmp(w*0.95,a[i])<=0&&dcmp(a[i],w*1.05)<=0){
            b[i]=0;
        }
        else if (dcmp(w*2*0.95,a[i])<=0&&dcmp(a[i],w*2*1.05)<=0){
            b[i]=1;
        }
        else return false;
    }
    W1=w;W2=w*2;
    return true;
}
void getWide(){
    for (int i=1;i<=n;i++)
        for (double j=0.95;j<=1.05;j+=0.001)
            if (tryWide(a[i]/j)) return;
}

//bad code 0 
//bad C 1
//bad K 2
//success 3 
int uncode(int ans[]){
    ans[0]=0;
    for (int i=6;i<=n;i+=6) if (b[i]!=0) return 0;
    for (int i=1;i<=n;i+=6){
        ans[++ans[0]]=getID(i);
    }
    if (ans[1]!=11||ans[ans[0]]!=11) return 0;  
    for (int i=2;i<ans[0];i++) if (ans[i]==11) return 0;
    int C=0;
    for (int i=2;i<=ans[0]-3;i++) C=(C+(((ans[0]-4)-(i-1))%10+1)*ans[i])%11;
    if (C!=ans[ans[0]-2]) return 1;
    int K=0;
    for (int i=2;i<=ans[0]-2;i++) K=(K+(((ans[0]-4)-(i-1)+1)%9+1)*ans[i])%11;
    if (K!=ans[ans[0]-1]) return 2;
    return 3;
    
}
void output(int ans[],int t){
    switch(t){
        case 3 :for (int i=2;i<=ans[0]-3;i++) printf("%c",stt[ans[i]]);
                printf("\n");
                break;
        case 2 :printf("bad K\n");
                break;
        case 1 :printf("bad C\n");
                break;
        case 0 :printf("bad code\n");
                break;
    }
}
void work(){
    for (int i=1;i<=n;i++) scanf("%lf",&a[i]);
    if (n%6!=5||n<29){
        printf("bad code\n");
        return;
    }
    W1=-1;
    getWide();
    
    if (W1==-1){
        printf("bad code\n");
        return;
    }
    int t1=uncode(ans1);
    if (t1==3){
        output(ans1,t1);
        return;
    }
    reverse(b+1,b+n+1);
    int t2=uncode(ans2);
    if (t1==1&&t2==0&&n==29){
        printf("bad code\n");
        return;
    }
    output(ans2,max(t1,t2));
}
int main(){
    freopen("code.in","r",stdin);
    freopen("code.out","w",stdout);
    int cas=0;
    while (scanf("%d",&n)!=EOF&&n){
        printf("Case %d: ",++cas);
        work();
    }
    return 0;
}
