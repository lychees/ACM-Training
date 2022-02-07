/**
 * IO generator.
 * Problem: World Cup.
 * Author: Xianghong Luo (lxhgww@google.com)
 **/

#include <assert.h>
#include <algorithm>
#include <bitset>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

#define _int64 long long

const int MAX_T[] = {100, 100};
const int MAX_N[] = {100, 100};

int diff, t;

struct testcase {
    int a[4];
    string answer;
};

int c[4];
int b[4];
int tot;
int game1[6] = {0, 0, 0, 1, 1, 2};
int game2[6] = {1, 2, 3, 2, 3, 3};

void sol(int x) {
    int i;
    if (x == 6) {
        for (i = 0; i < 4; i++)
            if (c[i] != b[i]) break;
        if (i == 4) tot++;
        return;
    }
    
    b[game1[x]] += 3;
    if (b[game1[x]] <= c[game1[x]]) sol(x + 1);
    if (tot > 1) return;
    b[game1[x]] -= 3;
    
    b[game2[x]] += 3;
    if (b[game2[x]] <= c[game2[x]]) sol(x + 1);
    if (tot > 1) return;
    b[game2[x]] -= 3;
    
    b[game1[x]] += 1;
    b[game2[x]] += 1;
    if (b[game1[x]] <= c[game1[x]] && b[game2[x]] <= c[game2[x]]) sol(x + 1);
    if (tot > 1) return;
    b[game1[x]] -= 1;
    b[game2[x]] -= 1;
}

void solve(testcase* t) {
    int i;
    for (i = 0; i < 4; i++) c[i] = t->a[i];
    for (i = 0; i < 4; i++)
        if (c[i] > 9) break;
    if (i < 4) {
        t->answer = "Wrong Scoreboard";
        return;
    }
    tot = 0;
    for (i = 0; i < 4; i++) b[i] = 0;
    sol(0);
    if (tot == 0)
        t->answer = "Wrong Scoreboard";
    else {
        if (tot == 1)
            t->answer = "Yes";
        else
            t->answer = "No";
    }
}

int getrand(int x) {
    int ret;
    ret = rand();
    ret %= x;
    return ret;
}

void GenerateManualCases(vector<testcase>* cases) {
    {
        testcase t;
        t.a[0] = 9;
        t.a[1] = 6;
        t.a[2] = 3;
        t.a[3] = 1;
        t.answer = "Wrong Scoreboard";
        cases->push_back(t);
    }
    {
        testcase t;
        t.a[0] = 3;
        t.a[1] = 3;
        t.a[2] = 3;
        t.a[3] = 3;
        t.answer = "Yes";
        cases->push_back(t);
    }
    {
        testcase t;
        t.a[0] = 7;
        t.a[1] = 7;
        t.a[2] = 2;
        t.a[3] = 0;
        t.answer = "Wrong Scoreboard";
        cases->push_back(t);
    }
    {
        testcase t;
        t.a[0] = 9;
        t.a[1] = 6;
        t.a[2] = 0;
        t.a[3] = 0;
        t.answer = "Wrong Scoreboard";
        cases->push_back(t);
    }
    {
        testcase t;
        t.a[0] = 7;
        t.a[1] = 7;
        t.a[2] = 0;
        t.a[3] = 0;
        t.answer = "Wrong Scoreboard";
        cases->push_back(t);
    }
    {
        testcase t;
        t.a[0] = 5;
        t.a[1] = 5;
        t.a[2] = 5;
        t.a[3] = 0;
        t.answer = "Yes";
        cases->push_back(t);
    }
    {
        testcase t;
        t.a[0] = 7;
        t.a[1] = 7;
        t.a[2] = 3;
        t.a[3] = 0;
        t.answer = "Yes";
        cases->push_back(t);
    }
    {
        testcase t;
        t.a[0] = 9;
        t.a[1] = 4;
        t.a[2] = 3;
        t.a[3] = 1;
        t.answer = "Yes";
        cases->push_back(t);
    }
    {
        testcase t;
        t.a[0] = 7;
        t.a[1] = 6;
        t.a[2] = 3;
        t.a[3] = 1;
        t.answer = "Yes";
        cases->push_back(t);
    }
    {
        testcase t;
        t.a[0] = 7;
        t.a[1] = 6;
        t.a[2] = 4;
        t.a[3] = 0;
        t.answer = "Yes";
        cases->push_back(t);
    }
    {
        testcase t;
        t.a[0] = 7;
        t.a[1] = 4;
        t.a[2] = 4;
        t.a[3] = 1;
        t.answer = "No";
        cases->push_back(t);
    }
    {
        testcase t;
        t.a[0] = 9;
        t.a[1] = 4;
        t.a[2] = 2;
        t.a[3] = 1;
        t.answer = "Yes";
        cases->push_back(t);
    }
    {
        testcase t;
        t.a[0] = 9;
        t.a[1] = 9;
        t.a[2] = 3;
        t.a[3] = 0;
        t.answer = "Wrong Scoreboard";
        cases->push_back(t);
    }
    {
        testcase t;
        t.a[0] = 9;
        t.a[1] = 4;
        t.a[2] = 2;
        t.a[3] = 11;
        t.answer = "Wrong Scoreboard";
        cases->push_back(t);
    }
    {
        testcase t;
        t.a[0] = 9;
        t.a[1] = 4;
        t.a[2] = 2;
        t.a[3] = 100;
        t.answer = "Wrong Scoreboard";
        cases->push_back(t);
    }
}

void GenerateRandomCases(vector<testcase>* cases, int num) {
    int i, l;
    for (l = 0; l < num; l++) {
        testcase t;
        for (i = 0; i < 4; i++) {
            t.a[i] = getrand(10);
        }
        solve(&t);
        cases->push_back(t);
    }
}

void OutputCases(vector<testcase> cases) {
    int i, j;
    cout << (int)cases.size() << endl;
    for (i = 0; i < cases.size(); i++) {
        for (j = 0; j < 3; j++) {
            cout << cases[i].a[j] << " ";
        }
        cout << cases[i].a[3] << endl;
        fprintf(stderr, "Case #%d: %s\n", i + 1, cases[i].answer.c_str());
    }
}

int main(int argc, char** argv) {
    assert(argc == 3);
    diff = atoi(argv[1]);
    int seed = atoi(argv[2]);
    srand(seed);
    vector<testcase> cases;
    cases.clear();
    GenerateManualCases(&cases);
    GenerateRandomCases(&cases, MAX_T[diff] - cases.size());
    random_shuffle(cases.begin(), cases.end());
    OutputCases(cases);
}