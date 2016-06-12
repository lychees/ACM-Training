/*
    This code has been written by MinakoKojima, feel free to ask me question. Blog: http://www.shuizilong.com/house
    Template Date: 2015.10.12
    Note: ...
*/

#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <queue>

using namespace std;

#define	sqr(a)		((a)*(a))
#define	rep(i,a,b)	for(int i=(a);i<(int)(b);i++)
#define	per(i,a,b)	for(int i=((a)-1);i>=(int)(b);i--)
#define	PER(i,n)	per(i,n,0)
#define	REP(i,n)	rep(i,0,n)
#define	clr(a)		memset((a),0,sizeof (a))
#define	SZ(a)		((int)((a).size()))
#define	ALL(x)		x.begin(),x.end()
#define	mabs(a)		((a)>0?(a):(-(a)))
#define	inf			(0x7fffffff)
#define	eps			1e-6

#define	MAXN
#define MODN		(1000000007)

typedef long long ll;

#define TEST_LOCAL 1

char s[100][51];
char t[51];

int main()
{
#if TEST_LOCAL
	freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
#endif

	int T;
	scanf("%d",&T);

	rep(CASE,1,T + 1)
	{
		int n,m;
		scanf("%d %d",&n,&m);
		int rf = 1;
		REP(i,n)
		{
			scanf("%s",s[i]);
			int l = strlen(s[i]);
			int flag = 1;
			REP(j,l)
			{
				if (s[i][j] == '0')
				{
					flag = 0;
					break;
				}
			}
			if (flag == 1)
			{
				rf = 0;
			}
		}
		scanf("%s",t);

		printf("Case #%d: ",CASE);
		if (rf == 0)
		{
			puts("IMPOSSIBLE");
		}
		else if (m == 1)
		{
			printf("? 0\n");
		}
		else
		{
			string a = "";
			string b = "";
			REP(i,m - 1)
			{
				a += '?';
			}
			REP(i,m / 2 + 1)
			{
				b += "10";
			}
			b += "?";
			REP(i,m / 2 + 1)
			{
				b += "10";
			}
			printf("%s %s\n",a.c_str(),b.c_str());
		}
	}

	return 0;
}
