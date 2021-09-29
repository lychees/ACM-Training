#include <iostream>
using namespace std;

struct data{
    int a,b,c;
    data(int a=0,int b=0,int c=0):a(a),b(b),c(c){};
}bag[10000];
int tot;
int sz[10000],use[10000];
int t=1,n=3,h=10;
int main(){
    freopen("network.in","w",stdout);
    for (int cas=1;cas<=t;cas++){
    for (int i=1;i<=n;i++){
        sz[i]=rand()%h+1;
        for (int j=1;j<=sz[i];j++) use[j]=0;
        use[sz[i]]=1;
        int k=rand()%sz[i]+1;
        for (int j=1;j<k;j++){
            int a;
            do{
                a=rand()%sz[i]+1;
            }while (use[a]);
            use[a]=1;
        }
        int l=1;
        for (int j=1;j<=sz[i];j++) if (use[j]){
            bag[++tot]=data(i,l,j);
            l=j+1;
        }
    }
    random_shuffle(bag+1,bag+tot+1);
    printf("%d %d\n",n,tot);
    for (int i=1;i<=n;i++) printf("%d ",sz[i]);printf("\n");
    for (int i=1;i<=tot;i++) printf("%d %d %d\n",bag[i].a,bag[i].b,bag[i].c);
        tot=0;
    }
    printf("0 0\n");
    return 0;
}
