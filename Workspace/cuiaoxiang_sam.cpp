#define _USE_MATH_DEFINES
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <complex>
#include <cmath>
#include <numeric>
#include <bitset>

using namespace std;

typedef long long int64;
typedef pair<int, int> ii;
const int INF = 1 << 30;

const int SIGMA = 27;

struct Node {
    Node *child[SIGMA];
    Node *fail;
    int len;
    
    bool visit;
    Node* pre;
    int c;
    int mask;
    int deg;
};

const int N = 25e4 + 10;
Node pool[N << 1], *last;
char s[N];

struct Sam {
    Node *head, *tail;
    Sam() {
        head = new_node(-1, 0, 0);
        tail = head;
    }
    Node *new_node(int c, int len, int mask) {
        Node *p = last++;
        p->len = len;
        fill(p->child, p->child + SIGMA, (Node *)nullptr);
        p->fail = nullptr;
        
        p->visit = false;
        p->c = c;
        p->pre = nullptr;
        p->mask = mask;
        p->deg = 0;
        return p;
    }
    void add(int c, int len, int mask) {
        Node *p = tail, *np = new_node(c, len, mask);
        tail = np;
        for (; p && !p->child[c]; p = p->fail) {
            p->child[c] = np;
        }
        if (!p) {
            np->fail = head;
        } else {
            Node *q = p->child[c];
            if (q->len == p->len + 1) {
                np->fail = q;
            } else {
                Node *r = last++;
                *r = *q;
                r->len = p->len + 1;
                np->fail = q->fail = r;
                for (; p && p->child[c] == q; p = p->fail) {
                    p->child[c] = r;
                }
            }
        }
    }
};

int main() {
    int cas;
    scanf("%d", &cas);
    for (int num = 1; num <= cas; ++num) {
        int n;
        scanf("%d", &n);
        last = pool;
        Sam A;
        for (int i = 0; i < n; ++i) {
            scanf("%s", s);
            int mask = i == 0 ? 1 : 2, j;
            for (j = 0; s[j]; ++j) {
                A.add(s[j] - 'a', j + 1, mask);
            }
            A.add(SIGMA - 1, j + 1, 0);
        }
        
        vector<Node*> V;
        for (Node* p = pool + 1; p != last; ++p) {
            Node* q = p->fail;
            q->deg++;
        }
        for (Node* p = pool + 1; p != last; ++p) {
            if (p->deg == 0) V.push_back(p);
        }
        for (int i = 0; i < V.size(); ++i) {
            Node* p = V[i];
            if (p->fail && --p->fail->deg == 0) V.push_back(p->fail);
        }
        for (int i = 0; i < V.size(); ++i) {
            Node* p = V[i];
            if (p->fail) p->fail->mask |= p->mask;
        }
        
        queue<Node*> Q;
        Q.push(A.head);
        A.head->visit = true;
        string ret;
        while (!Q.empty()) {
            Node* p = Q.front();
            Q.pop();
            for (int i = 0; i < SIGMA; ++i) {
                if (p->child[i]) {
                    Node* q = p->child[i];
                    if (!q->visit) {
                        q->visit = true;
                        q->pre = p;
                        Q.push(q);
                        if (q->mask == 1) {
                            while (q != A.head) {
                                ret += 'a' + q->c;
                                q = q->pre;
                            }
                            reverse(ret.begin(), ret.end());
                            break;
                        }
                    }
                }
            }
            if (!ret.empty()) break;
        }
        printf("Case #%d: ", num);
        puts(ret.empty() ? "Impossible" : ret.c_str());
        fflush(stdin);
    }
    return 0;
}