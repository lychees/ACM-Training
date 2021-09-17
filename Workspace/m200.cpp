#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <numeric>
#include <cstring>
#include <climits>
#include <cassert>
#include <complex>
#include <cstdio>
#include <string>
#include <vector>
#include <bitset>
#include <queue>
#include <stack>
#include <cmath>
#include <ctime>
#include <list>
#include <set>
#include <map>

using namespace std;

double m, n;
double ans;

int main(){

    #ifndef ONLINE_JUDGE
    freopen("/Users/minakokojima/Documents/GitHub/ACM-Training/Workspace/in.txt", "r", stdin);
    //freopen("/Users/minakokojima/Documents/GitHub/ACM-Training/Workspace/out.txt", "w", stdout);
#endif

        cin >> m >> n;
        for(int i = 0; i <= m; i++) ans += ((i-1)*2+1)*i;
        for(int i = 1; i < n; i++) m *= m;
        ans *= 1/m;
        cout << ans << endl;
}
