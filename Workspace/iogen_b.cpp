/**
 * IO generator.
 * Problem: Hemi Palindrome.
 * Author: Yiming Li (yimingli@google.com)
 **/

#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
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
#include <cctype>
#include <string>
#include <cstring>
#include <ctime>
#include <assert.h>

using namespace std;

#define _int64 long long

const int MAX_T[]={100,100};
const int MAX_N[]={20,100000};
const _int64 MAX_K[]={1000000000000000000LL,1000000000000000000LL};

int diff, t;

struct testcase
{
    int n;
    _int64 k;
    string answer;
};


int osum;
int esum;
int a[200000];

_int64 pow2(_int64 x)
{
    if (x>=60) return 1LL<<60;
    else return 1LL<<x;
}

_int64 pow1(_int64 x,_int64 y,_int64 z)
{
    int i;
    if (x==z) return pow2(y);
    if (y==z) return pow2(x);
    if (x>=61) return 1LL<<60;
    if (y>=61) return 1LL<<60;
    return (1LL<<x)+(1LL<<y)-(1LL<<z);
}

void solve(testcase *t)
{
    int cano,cane,n,tmp,dy,op,ep,midop,midep,i;
    _int64 k,cnt;
    n=t->n;k=t->k;
    k--;
    if (n%2==0)
    {
        esum=0+n-2;
        osum=1+n-1;
    }
    else
    {
        esum=0+n-1;
        osum=1+n-2;
    }
    cano=1;cane=1;
    op=0;ep=0;midep=(n+1)/2;midop=n/2;
    for (i=0;i<n;i++)
    {
        a[i]=0;
        if (i%2==0) dy=esum-i;
        else dy=osum-i;
        if (dy>=i)
        {
            if (i%2==0)
            {
                if (dy==i) midep--;
                else
                {
                    ep++;
                    midep-=2;
                }
            }
            else
            {
                if (dy==i) midop--;
                else
                {
                    op++;
                    midop-=2;
                }
            }
            cnt=pow1(op+midop+(midep+1)/2,ep+midep+(midop+1)/2,(midep+1)/2+(midop+1)/2);
        }
        else
        {
            if (i%2==0) ep--;
            else op--;
            if (a[dy]!=0)
            {
                if (i%2==0)
                {
                    tmp=cane;
                    cane=0;
                }
                else
                {
                    tmp=cano;
                    cano=0;
                }
            }
            
            if ((cano==0)&&(cane==0)) cnt=0;
            else if (cano==0) cnt=pow2(op);
            else if (cane==0) cnt=pow2(ep);
            else cnt=pow1(ep,op,0);
            
            if (a[dy]!=0)
            {
                if (i%2==0)
                {
                    cane=tmp;
                }
                else
                {
                    cano=tmp;
                }
            }
        }
        //cout<<i<<" "<<cnt<<" "<<k<<" "<<cane<<" "<<cano<<" "<<ep<<" "<<op<<endl;
        if (cnt<=k)
        {
            k-=cnt;
            a[i]=1;
        }
        else a[i]=0;
        if ((dy<i)&&(a[dy]!=a[i]))
        {
            if (i%2==0) cane=0;
            else cano=0;
        }
        //cout<<i<<" "<<cnt<<" "<<k<<" "<<a[i]<<" "<<cane<<" "<<cano<<" "<<ep<<" "<<op<<endl;
        //cout<<i<<" "<<a[i]<<endl;
    }
    if (k>0) t->answer="NOT FOUND!";
    else
    {
        t->answer="";
        for (i=0;i<n;i++)
            t->answer.push_back('0'+a[i]);
    }
}

int getrand(int x)
{
    int ret;
    ret=rand();
    ret%=x;
    return ret;
}

void GenerateManualCases(vector<testcase>* cases)
{
    {
        testcase t;
        t.n=2;t.k=1;
        t.answer="00";
        cases->push_back(t);
    }
    {
        testcase t;
        t.n=3;t.k=3;
        t.answer="010";
        cases->push_back(t);
    }
    {
        testcase t;
        t.n=3;t.k=5;
        t.answer="100";
        cases->push_back(t);
    }
    {
        testcase t;
        t.n=3;t.k=100;
        t.answer="NOT FOUND!";
        cases->push_back(t);
    }
}

void GenerateCornerCases(vector<testcase>* cases)
{
    int i;
    {
        testcase t;
        t.n=1;
        t.k=1;
        t.answer="0";
        cases->push_back(t);
    }
    {
        testcase t;
        t.n=1;
        t.k=2;
        t.answer="1";
        cases->push_back(t);
    }
    {
        testcase t;
        t.n=1;
        t.k=3;
        t.answer="NOT FOUND!";
        cases->push_back(t);
    }
    {
        testcase t;
        t.n=MAX_N[diff];
        t.k=1;
        t.answer="";
        for (i=0;i<t.n;i++)
            t.answer.push_back('0');
        cases->push_back(t);
    }
    if (diff==1)
    {
        testcase t;
        t.n=77;
        t.k=576460202547609600LL;
        t.answer="";
        for (i=0;i<t.n;i++)
            t.answer.push_back('1');
        cases->push_back(t);
    }
    if (diff==1)
    {
        testcase t;
        t.n=77;
        t.k=576460202547609601LL;
        t.answer="NOT FOUND!";
        cases->push_back(t);
    }
    if (diff==1)
    {
        testcase t;
        t.n=78;
        t.k=1000000000000000000LL;
        solve(&t);
        cases->push_back(t);
    }
    if (diff==1)
    {
        testcase t;
        t.n=77;
        t.k=1000000000000000000LL;
        t.answer="NOT FOUND!";
        cases->push_back(t);
    }
    {
        testcase t;
        t.n=MAX_N[diff];
        t.k=getrand(1000000000)*1000000000LL+getrand(1000000000)+1;
        solve(&t);
        cases->push_back(t);
    }
}

void GenerateRandomCases(vector<testcase>* cases, int num)
{
    int i;
    for (i=0;i<num;i++)
    {
        testcase t;
        t.n=getrand(MAX_N[diff])+1;
        if (diff==1)
            t.k=getrand(1000000000)*1000000000LL+getrand(1000000000)+1;
        else t.k=getrand(1LL<<(t.n-1))+1;
        solve(&t);
        cases->push_back(t);
    }
}

void OutputCases(vector<testcase> cases)
{
    int i,j,k;
    printf("%d\n",(int)cases.size());
    for (i=0;i<cases.size();i++)
    {
        printf("%d %lld\n",cases[i].n,cases[i].k);
        fprintf(stderr,"Case #%d: %s\n",i+1,cases[i].answer.c_str());
    }
}

int main(int argc, char **argv)
{
    int i,j;
    assert(argc == 3);
    diff = atoi(argv[1]);
    int seed = atoi(argv[2]);
    srand(seed);
    vector<testcase> cases;
    cases.clear();
    GenerateManualCases(&cases);
    GenerateCornerCases(&cases);
    GenerateRandomCases(&cases,MAX_T[diff]-cases.size());
    random_shuffle(cases.begin(),cases.end());
    OutputCases(cases);
}