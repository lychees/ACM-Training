#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <tuple>
#include <cassert>
#include <map>
#include <set>
using namespace std;
const int N = 200005;
const int M = 200005;

int prior[M];
int key[M] , cnt[M] , c[M][2] , tmp;
pair<int , int> mx[M];
int TestCase = 0;
void clear() {
    prior[0] = -1 << 30;
    c[0][0] = c[0][1] = 0;
    mx[0] = make_pair(-1 << 30 , -1 << 30);
    key[0] = cnt[0] = 0;
}
inline void pushup(int p) {
    mx[p] = make_pair(cnt[p] , -key[p]);
    mx[p] = max(mx[p] , max(mx[c[p][0]] , mx[c[p][1]]));
}
inline void rotate (int& x , int t) {
    int y = c[x][t];
    c[x][t] = c[y][!t] , c[y][!t] = x;
    pushup(x) , pushup(y) , x = y;
}
inline void newnode(int p , int w) {
    key[p] = w , cnt[p] = 1 , mx[p] = make_pair(1 , -w);
    prior[p] = rand() , c[p][0] = c[p][1] = 0;
}
void insert(int& p , int w , int C = 1) {
    if (!p) {
        p = tmp;
        newnode(p , w);
        cnt[p] = C;
    } else if (key[p] == w) {
        cnt[p] += C;
    } else {
        int t = key[p] < w;
        insert(c[p][t] , w , C);
        if (prior[c[p][t]] > prior[p])
            rotate(p , t);
    }
    pushup(p);
}
void merge(int& p , int& q) {
    if (!p) return;
    merge(c[p][0] , q);
    merge(c[p][1] , q);
    tmp = p;
    insert(q , key[p] , cnt[p]);
}

int random(int x , int y) {
    if (y == 233)  return x - 1;
    if (y == -233) return 0;
    int ret = rand() % x;
    while (y > 0) {
        ret = max(ret , rand() % x);
        -- y;
    }
    while (y < 0) {
        ret = min(ret , rand() % x);
        ++ y;
    }
    return ret;
}

tuple<int , int , int> E[N] , Q[N];
int f[N] , s[N] , a[N] , ans[N] , root[N];
int getf(int x) {
    return f[x] == x ? x : f[x] = getf(f[x]);
}

void gen(int n , int m , int q , int type , pair<int , int> color = make_pair(0 , 0)) {
    int mcnt = 0;
    for (int i = 1 ; i < n ; ++ i) {
        E[mcnt ++] = make_tuple(rand() % 100000 + 1, i + 1 , random(i , type) + 1);
        if (color.first == -1) {
            get<2>(E[mcnt - 1]) = i;
        }
    }
    while (mcnt < m) {
        int x , y;
        do {
            x = rand() % n + 1;
            y = rand() % n + 1;
        } while (x == y);
        E[mcnt ++] = make_tuple(rand() % 1000000 + 1 , x , y);
        
    }
    sort(E , E + m);
    for (int i = 0 ; i < q ; ++ i) {
        Q[i] = make_tuple(rand() % 100000 + 1 , rand() % n + 1 , i);
    }
    sort(Q , Q + q);
    for (int i = 1 ; i <= n ; ++ i) {
        f[i] = i , s[i] = 1;
        a[i] = rand() % n + 1;
    }
    if (color.first == -1) {
        for (int i = 1 ; i <= n ; ++ i) {
            a[i] = i;
        }
        random_shuffle(a + 1 , a + n + 1);
    }
    for (int i = 1 ; i <= color.first ; ++ i) {
        a[i] = rand() % color.second + 1;
    }
    clear();
    for (int i = 1 ; i <= n ; ++ i) {
        root[i] = i;
        newnode(root[i] , a[i]);
    }
    for (int i = 0 , j = 0 ; i < q ; ++ i) {
        while (j < m && get<0>(E[j]) <= get<0>(Q[i])) {
            int x = getf(get<1>(E[j]));
            int y = getf(get<2>(E[j]));
            if (s[x] < s[y]) swap(x , y);
            if (x != y) {
                f[y] = x;
                s[x] += s[y];
                merge(root[y] , root[x]);
            }
            ++ j;
        }
        int x = getf(get<1>(Q[i]));
        ans[get<2>(Q[i])] = -mx[root[x]].second;
    }
    printf("%d %d\n" , n , m);
    for (int i = 1 ; i <= n ; ++ i) {
        printf("%d%c" , a[i] , " \n"[i == n]);
    }
    random_shuffle(E , E + m);
    for (int i = 0 ; i < m ; ++ i) {
        printf("%d %d %d\n" , get<1>(E[i]) , get<2>(E[i]) , get<0>(E[i]));
    }
    printf("%d\n" , q);
    for (int i = 0 ; i < q ; ++ i) {
        swap(get<0>(Q[i]) , get<2>(Q[i]));
    }
    sort(Q , Q + q);
    for (int i = 0 ; i < q ; ++ i) {
        int last = i ? ans[i - 1] : 0;
        printf("%d %d\n" , get<1>(Q[i]) ^ last , get<2>(Q[i]) ^ last);
    }
    static int ca = 0;
    fprintf(stderr , "Case #%d:\n" , ++ ca);
    for (int i = 0 ; i < q ; ++ i) {
        fprintf(stderr , "%d\n" , ans[i]);
    }
}

int main(int argc, char **argv) {
    assert(argc == 3);
    int diff = atoi(argv[1]);
    srand(atoi(argv[2]));
    assert(RAND_MAX == 2147483647);
    if (diff == 1) {
        printf("%d\n", 15);
        gen(2000, 2500, 5000, 0);
        gen(2000, 2500, 5000, 2, {1000, 20});
        gen(2000, 2500, 5000, -2, {500, 1});
        gen(2000, 2500, 5000, -4, {1000, 5});
        gen(2000, 2500, 5000, 6, {2333, 100});
        
        gen(4000, 4500, 10000, 233, {1000, 20});
        gen(4000, 4500, 10000, 2, {1000, 10});
        gen(4000, 4500, 10000, -6, {1000, 1});
        gen(4000, 4500, 10000, 4, {0, 1});
        gen(4000, 4500, 10000, -4, {3000, 10});
        
        gen(50000, 50000, 50000, 233, {1000, 20});
        gen(50000, 49999, 50000, -233, {1000, 20});
        gen(100000, 100000, 99999, 233, {-1, -1});
        gen(100000, 200000, 100000, 10, {50000, 100});
        gen(100000, 200000, 100000, -10, {50000, 10});
    } else {
        printf("%d\n", 20);
        for (int i = 0; i < 20; ++i) {
            gen(500, 1000, 1000, 0);
        }
    }
}