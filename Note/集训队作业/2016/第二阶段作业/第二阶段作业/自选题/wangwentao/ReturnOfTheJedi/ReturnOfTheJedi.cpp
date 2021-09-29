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

const db oo=db(1)/0;

const int N=405;

int n;

db k;

struct vec{
	db x,y;
	vec(){
	}
	vec(db _x,db _y):x(_x),y(_y){
	}
	friend vec operator + (const vec &a,const vec &b){
		return vec(a.x+b.x,a.y+b.y);
	}
	db calck() const{
		return x+k*y;
	}
	db calc() const{
		return exp(x)*y;
	}
} a[N],sum[N];

db ord[N*N],*top=ord;

db ans[N];

struct ReturnOfTheJedi{
	vector <double> minimalExpectation(vector <int> val, vector <int> prob){
		n=val.size();
		for(int i=1;i<=n;i++) a[i]=vec(log(prob[i-1]/1e5),val[i-1]);
		top=ord;
		for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) if(a[i].x!=a[j].x&&a[i].y!=a[j].y){
			k=-(a[j].x-a[i].x)/(a[j].y-a[i].y);
			if(k>0) *top++=k;
		}
		*top++=0;
		*top++=1e50;
		sort(ord,top);
		for(int i=1;i<=n;i++){
			sum[i]=sum[i-1]+a[i];
			ans[i]=sum[i].calc();
		}
		for(db *cur=ord;cur+1<top;cur++){
			k=(cur[0]+cur[1])/2;
			for(int i=1;i<=n;i++)
				for(int j=i;j>1&&a[j].calck()<a[j-1].calck();j--){
					swap(a[j],a[j-1]);
					sum[j-1]=sum[j-2]+a[j-1];
					sum[j]=sum[j-1]+a[j];
					ans[j-1]=min(ans[j-1],sum[j-1].calc());
					ans[j]=min(ans[j],sum[j].calc());
				}
		}
		return vector<double>(ans+1,ans+n+1);
	}
};
