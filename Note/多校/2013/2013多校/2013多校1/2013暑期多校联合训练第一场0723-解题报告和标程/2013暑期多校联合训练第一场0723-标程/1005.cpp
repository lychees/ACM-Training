#include "iostream"
#include "cstring"
#include "cstdio"
#include "vector"
#include "algorithm"
#include "map"
using namespace std;
const int N = 100010;
int a[N];
int num_up[N],num_down[N];
int dp_up[N],dp_down[N];
int n;
void getdp(int dp[],int num[])
{
	dp[n]=1;
	vector<int> v;
	v.push_back(a[n]);
	vector<int>::iterator iter;
	for(int i=n-1;i>=1;i--){
		int sz=v.size();
		if(a[i]>v[sz-1]){
			v.push_back(a[i]);
			dp[i]=sz+1;
			num[i]=1;
		}else if(a[i]==v[sz-1]){
			iter=upper_bound(v.begin(),v.end(),a[i]);
			dp[i]=iter-v.begin()+1;
			v.push_back(a[i]);
			pair<vector<int>::iterator,vector<int>::iterator> bounds;
			bounds=equal_range(v.begin(),v.end(),a[i]);
			num[i]=bounds.second-bounds.first;
		}else{
			iter=upper_bound(v.begin(),v.end(),a[i]);
			dp[i]=iter-v.begin()+1;
			*iter=a[i];
			pair<vector<int>::iterator,vector<int>::iterator> bounds;
			bounds=equal_range(v.begin(),v.end(),a[i]);
			num[i]=bounds.second-bounds.first;
		}
	}		
}
void debug(int a[])
{
	for(int i=1;i<=n;i++){
		printf("%d ",a[i]);
	}
	printf("\n");
}
int main(void)
{
	int T;
	scanf("%d",&T);
	while(T--){
		int ans=0;
		scanf("%d",&n);
		map<int,int> mp;
		mp.clear();
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		getdp(dp_up,num_up);
		for(int i=1;i<=n;i++){
			a[i]=-a[i];
		}
		getdp(dp_down,num_down);
		for(int i=1;i<=n;i++){
			mp[a[i]]++;
			ans=max(ans,dp_down[i]+dp_up[i]-min(num_up[i],num_down[i]));
		}
		printf("%d\n",ans);
	}
	return 0;
}
