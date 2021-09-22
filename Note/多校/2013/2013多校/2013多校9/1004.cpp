/* ***********************************************
Author        :kuangbin
Created Time  :2013/8/20 12:12:11
File Name     :F:\2013ACM¡∑œ∞\2013∂‡–£9\1004.cpp
************************************************ */

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

long long dp[2][1<<22];
char str[100];
//vector<int>vec[21];
int a[50][800000];

int s1[50];

int n;





int calc(int n)
{
	int ret = 0;
	while(n)
	{
		if(n&1)ret++;
		n>>=1;
	}
	return ret;
}

int bit[30];
int b[1<<22];
int num[1<<22];

bool check(int id,int s)
{
    int tcnt = 0;
    s = ((s>>id)<<id);
    //cout<<id<<endl;
    //cout<<s<<endl;
    tcnt = num[s];
    tcnt = n - id + 1 - tcnt;
    if(tcnt < s1[id])return false;
    return true;
}

int main()
{
    //check(2,15);
    freopen("1004.in","r",stdin);
    freopen("out.txt","w",stdout);
    for(int i = 0;i < (1<<20);i++)num[i] = calc(i);
	bit[0] = 1;
	for(int i = 1;i < 22;i++)
		bit[i] = (bit[i-1]<<1);
	for(int i = 0; i <= 22;i++)a[i][0] = 0;
	for(int i = 0;i < bit[21];i++)
	{  // break;
		//	if(!check(i))continue;
			//continue;
			int cnt = 0;
			for(int j = 0;j < 21;j++)
				if(i & bit[j])
					cnt++;
			//vec[cnt].push_back(i);
			a[cnt][++a[cnt][0]] = i;
	}
	int ss,pp,tt;
	int s;
    while(scanf("%s",str)== 1)
	{
		n = strlen(str);

		for(int i = 0;i < n;i++)
        {
            if(str[i]=='+')s1[i] = 1;
            else s1[i] = 0;
        }
        s1[n] = 0;
        for(int i = n-2;i >= 0;i--)
            s1[i] += s1[i+1];



		int tot = bit[n];
		int now = 0;
		dp[now][0] = 1;
		for(int i = 0;i < n;i++)
		{
		//	cout<<"**"<<sz<<endl;
		    int nows = now^1;
			for(int j = 1;j <= a[i][0];j++)
			{
			    s = a[i][j];
				//cout<<"*"<<s<<endl;
				if(s >= tot)break;
		        if(dp[now][s] == 0)continue;

                //if(!check(i,s))
                //{
                //    dp[now][s] = 0;
                //    continue;
                //}
					if(str[i] == '+')
					{
						continue;
					//	int tt = ((tot-1)^s);
					   // int tt = s|((bit[i+1])-1);
					//	while(b[tt]<n)
					//	{
					//		int ss = bit[b[tt]];
					//		dp[now^1][s|ss] += dp[now][s];
					//		tt |= ss;
					//	}
					    ss = s|(bit[i+1]-1);
						ss ^= (tot-1);
						while(ss)
						{
							pp = (ss&(ss-1));
							tt = (ss&(~pp));
							dp[nows][s|tt] += dp[now][s];
							ss = pp;
						}
						/*
						continue;
						for(int k = i+1;k < n;k++)
							if((s&bit[k]) == 0)
								dp[now^1][s|bit[k]]+=dp[now][s];
								*/
					}
					else
					{
						continue;
					    ss = (s&(bit[i]-1));
						ss ^= (bit[i]-1);
						while(ss)
						{
							pp = (ss&(ss-1));
							tt = ss&(~pp);
							dp[nows][s|tt] += dp[now][s];
							ss = pp;
						}
						/*
						continue;

						for(int k = i-1;k >= 0;k--)
							if((s&bit[k]) == 0)
								dp[now^1][s|bit[k]]+=dp[now][s];
								*/
					}
					dp[now][s] = 0;
			}
			now ^= 1;
			//for(int j = 1;j <= sz;j++)
			//	dp[now^1][a[i][j]] = 0;
		}
		//cout<<n<<" "<<tot<<endl;
		printf("%I64d\n",dp[now][tot-1]);
		dp[now][tot-1] = 0;
	}
    return 0;
}
