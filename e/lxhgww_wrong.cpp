#include<stdio.h>
#include<algorithm>

using namespace std;

double c[101];

int main() {
    int t,p;
    int n,i;
    scanf("%d",&t);
    for (p=1;p<=t;p++) {
        scanf("%d",&n);
        for (i=1;i<=n;i++) {
            double a,b;
            scanf("%lf:%lf",&a,&b);
            c[i]=a/(a+b);
        }
        sort(c+1,c+n+1);
        double sum=0;
        for (i=1;i<=n;i++) {
            sum+=c[i];
            if (sum>=1.0) break;
        }
        printf("Case #%d: %d\n",p,i-1);
    }
    return 0;
}