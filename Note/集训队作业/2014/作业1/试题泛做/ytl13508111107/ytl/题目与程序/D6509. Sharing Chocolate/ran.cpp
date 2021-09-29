#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

int rand(int x){
    return rand()%x;
}
int t=5,l=10,nn=15;
int a[100];
int main(){
    srand(time(NULL));
    freopen("chocolate.in","w",stdout);
    for (int cas=1;cas<=t;cas++){
        int x=rand(l)+1,y=rand(l)+1;
        a[1]=x*y;
        int n=min(x*y,nn);
        for (int i=1;i<n;i++){
            do{
                random_shuffle(a+1,a+i+1);
            }while (a[i]==1);
            a[i+1]=rand(a[i]-1)+1;
            a[i]-=a[i+1];
        }
        printf("%d\n",n);
        printf("%d %d\n",x,y);
        for (int i=1;i<=n;i++) printf("%d ",a[i]);
        printf("\n");
    }
    printf("0\n");
}
