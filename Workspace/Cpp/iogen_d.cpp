/**
 * IO generator.
 * Problem: Ice Cream.
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
const int MAX_N[]={1000,300000};
const int MAX_K[]={64,64};

int diff, t;

struct testcase
{
    int n,k;
    vector<_int64> a;
    int answer;
};

_int64 a[500000];
int n,k;
_int64 next1[500000];


int can(int x)
{
    int i,j,o;
    for (i=0;i<x;i++)
        next1[i]=(1LL<<62);
    o=0;
    for (i=0;i<k;i++)
        for (j=0;j<x;j++)
        {
            while ((o<n)&&(a[o]+a[o]>next1[j])) o++;
            if (o>=n) return 0;
            next1[j]=a[o];
            o++;
        }
    return 1;
}

void solve(testcase *t)
{
    int left,right,mid,i;
    n=t->n;k=t->k;
    for (i=0;i<n;i++)
        a[i]=t->a[i];
    sort(a,a+n);
    reverse(a,a+n);
    left=0;right=500000;
    while (right-left>1)
    {
        mid=(left+right)/2;
        if (can(mid)==1)
        {
            left=mid;
        }
        else right=mid;
    }
    t->answer=left;
}

int getrand(int x)
{
    int ret;
    ret=rand();
    ret%=x;
    return ret;
}

_int64 getrandv()
{
    _int64 ret;
    ret=getrand(1000000000);
    ret*=1000000000;
    ret+=getrand(1000000000);
    ret++;
    return ret;
}

void GenerateManualCases(vector<testcase>* cases)
{
    {
        testcase t;
        t.n=4;t.k=2;
        t.a.clear();
        t.a.push_back(1);
        t.a.push_back(2);
        t.a.push_back(3);
        t.a.push_back(4);
        t.answer=2;
        cases->push_back(t);
    }
    {
        testcase t;
        t.n=6;t.k=3;
        t.a.clear();
        t.a.push_back(1);
        t.a.push_back(1);
        t.a.push_back(2);
        t.a.push_back(2);
        t.a.push_back(4);
        t.a.push_back(4);
        t.answer=2;
        cases->push_back(t);
    }
    {
        testcase t;
        t.n=6;t.k=3;
        t.a.clear();
        t.a.push_back(1);
        t.a.push_back(1);
        t.a.push_back(2);
        t.a.push_back(2);
        t.a.push_back(3);
        t.a.push_back(4);
        t.answer=1;
        cases->push_back(t);
    }
}

void GenerateCornerCases(vector<testcase>* cases)
{
    int i;
    {
        testcase t;
        t.n=MAX_N[diff];t.k=1;
        t.a.clear();
        for (i=0;i<t.n;i++)
            t.a.push_back(getrandv());
        t.answer=t.n;
        cases->push_back(t);
    }
    {
        testcase t;
        t.n=60;t.k=60;
        t.a.clear();
        for (i=0;i<60;i++)
            t.a.push_back(1LL<<i);
        t.answer=1;
        cases->push_back(t);
    }
    {
        testcase t;
        t.n=MAX_N[diff];t.k=64;
        t.a.clear();
        for (i=0;i<t.n;i++)
            t.a.push_back(getrandv());
        t.answer=0;
        cases->push_back(t);
    }
}

void GenerateRandomCases(vector<testcase>* cases, int num)
{
    int i,l;
    for (l=0;l<num;l++)
    {
        testcase t;
        t.n=getrand(MAX_N[diff])+1;
        t.k=getrand(5)+3;
        t.a.clear();
        for (i=0;i<t.n;i++)
        {
            t.a.push_back(getrandv());
        }
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
        printf("%d %d\n",cases[i].n,cases[i].k);
        for (j=0;j<cases[i].n;j++)
        {
            if (j!=0) printf(" ");
            printf("%lld",cases[i].a[j]);
        }
        printf("\n");
        fprintf(stderr,"Case #%d: %d\n",i+1,cases[i].answer);
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