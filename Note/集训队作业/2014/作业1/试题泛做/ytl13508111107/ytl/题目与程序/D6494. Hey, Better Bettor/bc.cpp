
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
 
using namespace std;

double lambda, alpha;
int upper;

double calc(int a, int b) {
    return (pow(alpha, a) - 1) * (a * lambda + b) / (pow(alpha, a + b) - 1) - a * lambda;
}

double calc(int a) {
    int head = 1, tail = upper;
    while (head <= tail) {
        int mid = (head + tail) / 2;
        double t1 = calc(a, mid);
        double t2 = calc(a, mid + 1);
        if (t1 < t2) head = mid + 1; else tail = mid - 1;
    }
  //  printf("!%d %d\n",a,head);
    return calc(a, head);
}

int main() {
   	freopen("hey.in","r",stdin);
	freopen("bc.out","w",stdout);
	 double x, p;
    scanf("%lf%lf", &x, &p);
    p /= 100;
    if (fabs(p) < 1e-5) {
        printf("%.10lf\n", 0.0);
        return 0;
    }

    lambda = 1 - x / 100;
    alpha = (1 - p) / p;

    upper = (int)(10 / log10(alpha));
    
    //calc(1);exit(0);
    
	//printf("!%d\n",upper);
    int head = 1, tail = upper;
    while (head <= tail) {
        int mid = (head + tail) / 2;
        double t1 = calc(mid);
        double t2 = calc(mid + 1);
        if (t1 < t2) head = mid + 1; else tail = mid - 1;
    }
	//printf("!%d\n",head);
    printf("%.10lf\n", max(0.0, calc(head)));
 
    return 0;
}
