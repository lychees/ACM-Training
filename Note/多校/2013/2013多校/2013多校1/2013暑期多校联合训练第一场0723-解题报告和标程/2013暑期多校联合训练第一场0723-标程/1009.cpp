#include <cstdio>
#include <cstring>

const int N = 200000;

char string[N];
int a[N], length;

int main() {
    int test;
    scanf("%d", &test);
    while (test --) {
        scanf("%s", string);
        length = strlen(string);
        for (int i = 1; i <= length; ++ i) {
            a[i] = string[length - i] - '0';
        }
        while (1) {
            a[1] ++;
            int pivot = 1;
            while (a[pivot] >= 10) {
                if (pivot == length) {
                    length ++;
                    a[length] = 0;
                }
                a[pivot] -= 10;
                a[pivot + 1] ++;
                pivot ++;
            }

            int sum = 0;
            for (int i = 1; i <= length; ++ i) {
                sum += a[i];
                if (sum >= 10) {
                    sum -= 10;
                }
            }
            if (sum == 0) {
                break;
            }
        }
        for (int i = length; i >= 1; -- i) {
            printf("%d", a[i]);
        }
        puts("");
    }
    return 0;
}
