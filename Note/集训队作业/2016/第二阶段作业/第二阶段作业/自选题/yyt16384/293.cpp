#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <vector>
#include <list>
#include <bitset>
#include <string>
#include <numeric>
#include <limits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cctype>
using namespace std;
#ifndef ONLINE_JUDGE
ifstream fin("293.in");
ofstream fout("293.out");
#else
#define fin cin
#define fout cout
#endif
const int MAXN=2009;
int n;
bool a[2*MAXN];
void init()
{
	string s;
	fin>>n>>s;
	for (int i=0;i<2*n-1;++i)
		a[i]=(s[i]=='Q'?true:false);
}
void solve()
{
	bool e,mide;
	int s;
	fout<<"Qc"<<endl<<"0 0"<<endl;
	for (int i=1;i<n;++i)
	{
		if (a[2*i]==a[2*i-1])
		{
			if (i==1)
			{
				fout<<"1 2"<<endl<<"0 0"<<endl;
				e=a[2];
				mide=a[0];
				s=1;
				continue;
			}
			if (e!=a[2*i]&&s<2)
			{
				e^=1;s^=1;
			}
			if (e==a[2*i])
			{
				if (s<=i-2)
				{
					if ((i+s+1)%2)
						if (s>0)
							fout<<i<<" "<<i+1<<endl<<i+s+1<<" "<<2*i+1<<endl;
						else
							fout<<i<<" "<<i+s+1<<endl<<i<<" "<<2*i+1<<endl;
					else fout<<i+s+1<<" "<<2*i<<endl<<i<<" "<<i+1<<endl;
				}
				else fout<<i<<" "<<i+1<<endl<<"0 0"<<endl;
				++s;
			}
			else
			{
				fout<<i<<" "<<i+1<<endl<<i-s+1<<" "<<2*i+(i-s)%2<<endl;
				--s;
			}
		}
		else
		{
			if (i==1)
			{
				fout<<"0 0"<<endl;
				if (a[0]==a[1])
				{
					fout<<"2 3"<<endl;
					e=a[1];mide=a[2];
				}
				else
				{
					fout<<"0 0"<<endl;
					e=a[2];mide=a[1];
				}
				s=1;
				continue;
			}
			if (s==0)
			{
				e^=1;s^=1;
			}
			if (s==i-1&&e==mide)
			{
				if (a[2*i]==e)
					fout<<i+1<<" "<<2*i<<endl<<"0 0"<<endl;
				else
					fout<<"0 0"<<endl<<i+1<<" "<<2*i+1<<endl;
			}
			else
			{
				if (e!=mide)
				{
					if (s>1)
						fout<<i-s+1<<" "<<i<<endl;
					else
						fout<<"0 0"<<endl;
				}
				else fout<<i+1<<" "<<i+s+1<<endl;
				if (((i+s+1)%2)^(e!=a[2*i]))
					fout<<2*i<<" "<<2*i+1<<endl;
				else fout<<"0 0"<<endl;
			}
			if (e==mide) ++s;
			else --s;
			mide^=1;
		}
	}
}
int main()
{
	init();
	solve();
	return 0;
}
