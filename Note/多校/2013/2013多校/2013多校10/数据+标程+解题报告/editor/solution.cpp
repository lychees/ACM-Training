#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define SIZE(v) ((int)(v).size())

const int INF = 1000000000;

struct Data {
    int sum, min_sum, max_sum;

    Data(int sum, int min_sum, int max_sum) : sum(sum), min_sum(min_sum), max_sum(max_sum) {}
};

void push(std::vector <Data> &stack, int value) {
    Data &last = stack.back();
    int sum = last.sum + value;
    stack.push_back(Data(sum, std::min(last.min_sum, sum), std::max(last.max_sum, sum)));
}

int pop(std::vector <Data> &stack) {
    Data last = stack.back();
    stack.pop_back();
    return last.sum - stack.back().sum;
}

int main() {
    int q;
    while (scanf("%d", &q) == 1) {
        assert(1 <= q && q <= 1000000);
        std::vector <Data> prefix, suffix;
        prefix.push_back(Data(0, INF, -INF));
        suffix.push_back(Data(0, 0, 0));
        while (q --) {
            char buffer[2];
            assert(scanf("%s", buffer) == 1);
            if (*buffer == 'I') {
                int x;
                assert(scanf("%d", &x) == 1);
                assert(std::abs(x) <= 1000);
                push(prefix, x);
            } else if (*buffer == 'D') {
                assert(SIZE(prefix) > 1);
                pop(prefix);
            } else if (*buffer == 'L') {
                //assert(SIZE(prefix) > 1);
                if (SIZE(prefix) > 1) {
                    push(suffix, pop(prefix));
                }
            } else if (*buffer == 'R') {
                //assert(SIZE(suffix) > 1);
                if (SIZE(suffix) > 1) {
                    push(prefix, pop(suffix));
                }
            } else if (*buffer == 'Q') {
                int k;
                assert(scanf("%d", &k) == 1);
                assert(1 <= k && k <= SIZE(prefix) - 1);
                printf("%d\n", prefix[k].max_sum);
            } else {
                assert(false);
            }
        }
    }
    return 0;
}
