#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

const int MAXN = 100010;
int a[MAXN];
int dp1[MAXN],dp2[MAXN];
int num1[MAXN],num2[MAXN];

int n;

void getDP(int dp[],int num[])
{
    vector<int>vec;
    vec.push_back(a[n-1]);
    dp[n-1] = 1;
    num[n-1] = 1;
    for(int i = n-2;i >= 0;i--)
    {
        int sz = vec.size();
        if(a[i] > vec[sz-1])
        {
            dp[i] = sz+1;
            num[i] = 1;
            vec.push_back(a[i]);
        }
        else if(a[i] == vec[sz-1])
        {
            dp[i] = sz+1;
            vec.push_back(a[i]);
            pair<vector<int>::iterator,vector<int>::iterator>range;
            range = equal_range(vec.begin(),vec.end(),a[i]);
            num[i] = range.second - range.first;
        }
        else
        {
            vector<int>::iterator it;
            it = upper_bound(vec.begin(),vec.end(),a[i]);
            dp[i] = it - vec.begin() + 1;
            *it = a[i];
            pair<vector<int>::iterator,vector<int>::iterator>range;
            range = equal_range(vec.begin(),vec.end(),a[i]);
            num[i] = range.second - range.first;
        }
    }
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i = 0;i < n;i++)
            scanf("%d",&a[i]);
        getDP(dp1,num1);
        for(int i = 0;i < n;i++)
            a[i] = -a[i];
        getDP(dp2,num2);
        int ans = 0;
        for(int i = 0;i < n;i++)
            ans = max(ans,dp1[i]+dp2[i]-min(num1[i],num2[i]));
        printf("%d\n",ans);
    }
    return 0;
}



