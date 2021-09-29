#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

int n,i,j,k;
string s[100005];

inline bool cmp(const string &a,const string &b)
{
	if(a.size()!=b.size())return a.size()<b.size();
	return a<b;
}

int main()
{
	while(scanf("%d",&n)!=EOF)
	{
		for(i=1;i<=n;++i)cin>>s[i];
		if(n%2){printf("first player\n");continue;}
		sort(s+1,s+n+1,cmp);
		for(i=1;i<=n;++i)if(i%2==0&&s[i]!=s[i-1]){printf("first player\n");break;}
		if(i>n)printf("second player\n");
	}
} 

