#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <set>
#include <vector>
#include <unordered_set>
#include <time.h>

const int T = 20;
const int MaxM = 1005 << 2;
const int MaxN[2] = {100, 1000};
const int MinV[2] = {32, 64};
const int MaxV[2] = {256, 100000};

int candidates[100005];
int diff;

/** start solution */
int a[1005], idx[1005], n;
std::vector<int> pos[1005];
int max_len[1005];
std::unordered_set<int> set;

struct interval_t {
    int l, r, max;
    interval_t(int _l, int _r, int _max) : l(_l), r(_r), max(_max) {}
};

bool comp_with_max = false;
struct comparator_t {
    inline bool operator()(const interval_t& lhs, const interval_t& rhs) const {
        if (comp_with_max) {
            return lhs.max < rhs.max;
        } else if (lhs.l != rhs.l) {
            return lhs.l < rhs.l;
        } else {
            return lhs.r < rhs.r;
        }
    }
};

std::set<interval_t, comparator_t> ordered_intervals;
int next[1005];

struct seg_t {
    int l, r, max, filled;
} seg[MaxM];

inline bool comp(const int& i, const int& j) {
    return a[i] < a[j];
}

void make_unique() {
    for (int i = 0; i < n; i++) idx[i] = i;
    std::sort(idx, idx + n, comp);
    int last = a[idx[0]], m = 0;
    a[idx[0]] = m++;
    for (int i = 1; i < n; i++) {
        if (a[idx[i]] == last) {
            a[idx[i]] = m - 1;
        } else {
            last = a[idx[i]];
            a[idx[i]] = m++;
        }
    }
    
    for (int i = 0; i < m; i++) {
        pos[i].clear();
    }
    
    next[n] = n;
    for (int i = n - 1; i >= 0; i--) {
        if (!pos[a[i]].empty()) next[i] = pos[a[i]].back();
        else next[i] = n;
        next[i] = std::min(next[i], next[i + 1]);
        pos[a[i]].push_back(i);
    }
}

inline void push_down(int k) {
    if (seg[k].filled != -1) {
        seg[k << 1].max = seg[k << 1].filled = seg[k].filled;
        seg[k << 1 | 1].max = seg[k << 1 | 1].filled = seg[k].filled;
        seg[k].filled = -1;
    }
}

inline void init(int k, int l, int r) {
    seg[k].l = l;
    seg[k].r = r;
    seg[k].filled = -1;
    if (l == r) {
        seg[k].max = max_len[l];
        return;
    }
    int mid = (l + r) >> 1;
    init(k << 1, l, mid);
    init(k << 1 | 1, mid + 1, r);
    seg[k].max = std::max(seg[k << 1].max, seg[k << 1 | 1].max);
}

inline void update(int k, int l, int r, int value) {
    if (seg[k].l > r || seg[k].r < l) return;
    if (seg[k].l >= l && seg[k].r <= r) {
        seg[k].max = seg[k].filled = value;
        return;
    }
    push_down(k);
    update(k << 1, l, r, value);
    update(k << 1 | 1, l, r, value);
    seg[k].max = std::max(seg[k << 1].max, seg[k << 1 | 1].max);
}

inline int read(int k, int l, int r) {
    if (seg[k].l > r || seg[k].r < l) return -1;
    if ((seg[k].l >= l && seg[k].r <= r) || seg[k].filled != -1) return seg[k].max;
    return std::max(read(k << 1, l, r), read(k << 1 | 1, l, r));
}

inline void handle_with_one_point(int pos) {
    comp_with_max = true;
    auto left_most = ordered_intervals.lower_bound({0, 0, pos});
    comp_with_max = false;
    auto right_most = ordered_intervals.lower_bound({pos + 1, -1, -1});
    right_most--;
    int left_bound = left_most->l;
    int right_bound = right_most->r;
    int right_bound_max = right_most->max;
    right_most++;
    ordered_intervals.erase(left_most, right_most);
    update(1, left_bound, right_bound, 0);
    if (left_bound < pos) {
        update(1, left_bound, left_bound, pos - left_bound);
        ordered_intervals.insert({left_bound, pos - 1, pos});
    }
    if (right_bound > pos) {
        update(1, pos + 1, pos + 1, right_bound_max - (pos + 1));
        ordered_intervals.insert({pos + 1, right_bound, right_bound_max});
    }
}

int solve() {
    int res = 1;
    
    make_unique();
    
    for (int i = 0; i < n; i++) {
        comp_with_max = false;
        ordered_intervals.clear();
        std::fill(max_len, max_len + n, 0);
        for (int j = i, k = i; j < n; j = k) {
            while (k < n && next[k] == next[j]) k++;
            ordered_intervals.insert({j, k - 1, next[j]});
            max_len[j] = next[j] - j;
        }
        init(1, 0, n - 1);
        set.clear();
        for (int j = i; j < n; j++) {
            if (set.count(a[j])) break;
            set.insert(a[j]);
            for (const int& p : pos[a[j]]) {
                if (p < j) break;
                handle_with_one_point(p);
            }
            int cur = 0;
            comp_with_max = false;
            auto iter = ordered_intervals.lower_bound({j + 1, -1, -1});
            if (iter != ordered_intervals.begin()) {
                iter--;
                if (j + 1 > iter->l && j + 1 <= iter->r) {
                    cur = iter->max - (j + 1);
                }
            }
            res = std::max(res, j - i + 1 + read(1, j + 1, n - 1) + cur);
        }
    }
    return res;
}

/** end of solution */

struct test_case_t {
    std::vector<int> arr;
    
    test_case_t() {}
    test_case_t(const std::vector<int>& _arr) : arr(_arr) {}
    
    void print_input() const {
        printf("%lu\n", arr.size());
        bool ok = false;
        for (const int& a : arr) {
            if (ok) putchar(' ');
            else ok = true;
            printf("%d", a);
        }
        puts("");
    }
    
    void print_output(int cas) const {
        n = arr.size();
        for (int i = 0; i < n; i++) a[i] = arr[i];
        fprintf(stderr, "Case #%d: %d\n", cas, solve());
    }
};
std::vector<test_case_t> test_cases;

void generate_muanl_test_cases() {
    if (diff == 0) {
        test_cases.push_back(test_case_t({1, 2, 3}));
        test_cases.push_back(test_case_t({3, 1, 2, 1, 6, 1, 2, 5}));
    }
    
    // all same
    test_case_t test0;
    for (int i = 0; i < MaxN[diff]; i++) test0.arr.push_back(candidates[i % 2]);
    test_cases.push_back(test0);
    
    // only two numbers
    test_case_t test1;
    for (int i = 0; i < MaxN[diff]; i++) test1.arr.push_back(candidates[i]);
    test_cases.push_back(test1);
}

void generate_random_test_case(bool small_data_set) {
    test_case_t cur;
    for (int i = 0; i < MaxN[diff]; i++) {
        if (small_data_set) cur.arr.push_back(candidates[rand() % MinV[diff]]);
        else cur.arr.push_back(candidates[rand() % MaxV[diff]]);
    }
    test_cases.push_back(cur);
}

int main(int argc, char** argv) {
    if (argc == 3) {
        diff = atoi(argv[1]);
        srand(atoi(argv[2]));
    } else {
        diff = 0;
        srand(time(NULL));
    }
    
    for (int i = 0; i < MaxV[diff]; i++) candidates[i] = i + 1;
    
    generate_muanl_test_cases();
    
    int remain_tests = T - test_cases.size();
    for (int i = 0; i < remain_tests; i++) {
        generate_random_test_case(i & 1);
    }
    
    std::random_shuffle(test_cases.begin(), test_cases.end());
    printf("%lu\n", test_cases.size());
    int cas = 0;
    for (const auto& test_case : test_cases) {
        test_case.print_input();
        test_case.print_output(++cas);
    }
    return 0;
}