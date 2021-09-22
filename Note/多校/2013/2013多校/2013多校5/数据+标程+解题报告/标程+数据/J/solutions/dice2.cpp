#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<algorithm>
#include<string>
#include<queue>
#include <iostream>
#include<vector>
#include<map>
#include<set>
#include<complex>
using namespace std;
int t,n,m;
typedef complex<double> dcomp;
dcomp s[1000010];
int main()
{
//	freopen("1010.in","r",stdin);
//	freopen("1010.out","w",stdout);
    int T; scanf("%d", &T); while (T--){
        scanf("%d%d%d", &t, &m, &n);
        if (!t){
            printf("%.9lf\n", (double)((pow((double)m, n) - 1) / (m - 1)));
        }
        else {
            s[1]=dcomp(1,0);
            for(int i=2;i<=n;i++)s[i]=-s[i-2]*dcomp((double)m/(m-i+1),0)+s[i-1]*dcomp((double)(m+m-i)/(m-i+1),0)-dcomp(0,(double)m/(m-i+1));
            double ans=-(imag(s[n])-imag(s[n-1]))/(real(s[n])-real(s[n-1]))+1;
            printf("%.9lf\n",ans);
        }
    }
	return 0;
}
