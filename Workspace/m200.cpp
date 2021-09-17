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

const long long MAX = 1e7;
long long n, m, c, v;
long long dp[MAX];

int main(){

    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    //freopen("/Users/minakokojima/Documents/GitHub/ACM-Training/Workspace/out.txt", "w", stdout);
#endif
    cin >> n >> m;
    while(m--){
        cin >> c >> v;
        for(long long i = c; i <= n; i++) dp[i] = max(dp[i], dp[i-c] + v);
    }
    cout << dp[n];
}
