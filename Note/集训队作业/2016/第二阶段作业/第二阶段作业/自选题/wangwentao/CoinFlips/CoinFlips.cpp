#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef double db;
typedef pair<int,int> pii;

const int N=305;

int n;

db p,pw[N];

db f[N][N][N];

struct CoinFlips{
	double getExpectation(vector <int> vals, int prob){
		n=vals.size();
		vals.insert(vals.begin(),0);
		p=prob/1e9;
		pw[0]=1;
		for(int i=1;i<=n;i++) pw[i]=pw[i-1]*(1-p);
		for(int i=1;i<=n;i++)
			for(int j=1;j<i;j++){
				f[i][j][j+1]=1;
				for(int k=j+2;k<=i;k++)
					f[i][j][k]=(1-pw[j-1]+(j>1?pw[i]:0))*f[i-1][j-1][k-1]+pw[j]*(1-pw[k-j-1])*f[i-1][j][k-1]+pw[k]*(1-pw[i-k])*f[i-1][j][k];
			}
		db ans=0;
		for(int i=1;i<=n;i++)
			for(int j=i+2;j<=n;j++)
				ans+=vals[i]*vals[j]*f[n][i][j];
		return ans;
	}
};
