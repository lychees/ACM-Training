#include <iostream>
using namespace std;

int main(){
    srand(time(NULL));
    freopen("number.in","w",stdout);
    for (int i=1;i<=10;i++) printf("%d\n",rand()+rand()+rand());
    //for (int i=90000;i<=90200;i++) printf("%d\n",i);
    printf("0\n");
    return 0;
}
