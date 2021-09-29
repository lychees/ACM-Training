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

const int N=2505,M=6,K=6;

const int inf=int(1e9)+7;

inline void mini(int &a,const int b){
	if(b<a) a=b;
}

int n,m,kk;

int F;

int f[2][2][N][M][K+1];

struct BearPairs{
	int minCost(string s, vector <int> c, int kk){
		n=s.size();
		m=6;
		for(int i=0;i<n;i++) s[i]-='a';
		for(int o=0;o<=1;o++)
			for(int k=0;k<m;k++){
				f[F][o][0][k][0]=0;
				for(int l=1;l<=kk;l++)
					f[F][o][0][k][l]=inf;
			}
		for(int i=0;i<n;){
			for(int o=0;o<=1;o++)
				for(int j=0;j<=i+1;j++)
					for(int k=0;k<m;k++)
						for(int l=0;l<=kk;l++)
							f[F^1][o][j][k][l]=inf;
			for(int j=0;j<=i;j++)
				for(int l=0;l<=kk;l++){
					static int pretmp[M],suftmp[M];
					for(int k=0;k<m;k++) pretmp[k]=suftmp[k]=inf;
					for(int k=0;k<m;k++){
						int now=f[F][0][j][k][l];
						if(now==inf) continue;
						if(l<kk)
							mini(f[F^1][0][j][k][l+1],now);
						if(k==s[i]){
							mini(f[F^1][0][j+1][k][l],now+c[i]-100*i);
						}
						else{
							if(j>0) mini(f[F^1][0][j-1][k][l],now+c[i]+100*i);
							if(k>0) mini(pretmp[k-1],now+c[i]-100*i);
							if(k<m-1) mini(suftmp[k+1],now+c[i]-100*i);
						}
					}
					for(int k=m-2;k>=0;k--) mini(pretmp[k],pretmp[k+1]);
					for(int k=1;k<=m-1;k++) mini(suftmp[k],suftmp[k-1]);
					for(int k=0;k<m;k++) if(k!=s[i]) mini(f[F^1][1][j+1][k][l],min(pretmp[k],suftmp[k]));
				}
			for(int j=0;j<=i;j++)
				for(int k=0;k<m;k++)
					for(int l=0;l<=kk;l++){
						int now=f[F][1][j][k][l];
						if(now==inf) continue;
						if(l<kk)
							mini(f[F^1][1][j][k][l+1],now);
						if(k==s[i]){
							if(j>0)
								mini(f[F^1][1][j-1][k][l],now+c[i]+100*i);
						}
						else{
							mini(f[F^1][1][j+1][k][l],now+c[i]-100*i);
						}
					}
			++i;
			F^=1;
			for(int l=0;l<=kk;l++){
				int now=inf;
				for(int o=0;o<=1;o++)
					for(int k=0;k<m;k++)
						mini(now,f[F][o][0][k][l]);
				for(int o=0;o<=1;o++)
					for(int k=0;k<m;k++)
						mini(f[F][o][0][k][l],now);
			}
		}
		int ans=f[F][0][0][0][kk];
		return ans==inf?-1:ans;
	}
};
