#include <iostream>
using namespace std;

int t=5,n=64;
int main(){
    srand(time(NULL));
    freopen("structure.in","w",stdout);
    for (int i=1;i<=t;i++){
        printf("%d\n",n);
        for (int i=1;i<=n;i++){
            for (int j=1;j<=n;j++)
                printf("%d",rand()%2);
            printf("\n");
        }
    }
    //printf("0\n");
    return 0;
}
