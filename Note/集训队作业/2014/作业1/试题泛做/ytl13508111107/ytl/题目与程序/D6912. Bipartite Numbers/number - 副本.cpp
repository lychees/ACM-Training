//By ytl 2014-1-7
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;

int n,x1,y1,a1,b1,len1,FLAG;
int one[5000],zero[5000];

bool cmp(int x,int a,int y,int b,int i,int u,int j,int v){
    if (x==-1) return true;
    if (x!=i) return i<x;
    if (a==u) return j<y;
    if (a<u) return i<y;
    return j<x;
}
inline bool calc(int len,int i,int u,int j,int v){
    return (one[u]*zero[v]*i+one[v]*j)%n==0&&!(FLAG&&len==len1&&i==x1&&j==y1&&u==a1&&v==b1);
}
bool getAns(int len,int &x,int &a,int &y,int &b){
    one[len]=(one[len-1]*10+1)%n;
    zero[len]=(zero[len-1]*10)%n;
    x=-1;int t=0;
    for (int i=1;i<=9;i++)
        for (int j=0;j<=9;j++) if (j!=i){
            if (len<100000){
                for (int u=1;u<len;u++){
                    int v=len-u;
                    if (calc(len,i,u,j,v)){
                        if (cmp(x,a,y,b,i,u,j,v)){x=i;a=u;y=j;b=v;}
                        t=1;
                    }
                }
            }else{
                for (int u=1;u<=5;u++){
                    int v=len-u;
                    if (calc(len,i,u,j,v)){
                        if (cmp(x,a,y,b,i,u,j,v)){x=i;a=u;y=j;b=v;}
                        t=1;
                    }
                }
                for (int u=len-5;u<len;u++){
                    int v=len-u;
                    if (calc(len,i,u,j,v)){
                        if (cmp(x,a,y,b,i,u,j,v)){x=i;a=u;y=j;b=v;}
                        t=1;
                    }
                }
            }
        }
    return t;
}
void work(){
    FLAG=0;
    len1=0;
    for (int i=n;i;i/=10) len1++;
    if (n>=10){
        int a=n;
        y1=a%10;b1=0;
        while (a%10==y1&&a>0){
            b1++;
            a/=10;
        }
        if (a%10!=0){
            x1=a%10;a1=0;
            while (a%10==x1&&a>0){
                a1++;
                a/=10;
            }
            if (!a) FLAG=1;
        }
    }
    one[1]=1%n;
    zero[0]=1%n;zero[1]=10%n;
    for (int len=2;;len++){
        int x,a,y,b; 
        if (getAns(len,x,a,y,b)){
            printf("%d: %d %d %d %d\n",n,a,x,b,y);
            return;
        }
    }
}
int main(){
    freopen("number.in","r",stdin);
    freopen("number.out","w",stdout);
    while (scanf("%d",&n)!=EOF&&n){
        if (n>50000){
            printf("!!!\n");
            return 0;
        }
        work();
    }
    return 0;
}
