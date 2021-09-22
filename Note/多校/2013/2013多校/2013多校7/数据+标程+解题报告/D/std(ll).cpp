#include <cstdio>
#include <cstring>

//Assume n<=3*10^4, mod<=10^3
const int maxn = 50005, maxmod=205;
int n, mod, number[maxn], digits[maxn], e[maxn * 3];
int count[maxn][maxmod];

inline int count_digits(int number) {
	if (!number) return 1;
	int ret = 0;
	while (number) ret++, number /= 10;
	return ret;
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt","w",stdout);
	e[0] = 1;
	while (scanf("%d%d", &n, &mod) != EOF) {
		memset(count,0,sizeof(int) * maxmod * n);

		for (int i = 1; i < n * 3; i++) 
			e[i] = e[i - 1] * 10 % mod;

		for (int i = 0; i < n; i++) {
			scanf("%d", number + i);
			digits[i] = count_digits(number[i]);
		}
		number[n] = number[0];
		digits[n] = digits[0];

		int s = 0, length = 0, answer = 0;
		for (int i = n; i; i--) {
			s = (s + number[i] * e[length]) % mod;
			length += digits[i];
			count[0][s]++;
		}
		answer += count[0][0];

		for (int i = 1; i < n; i++) {
			for (int r = 0; r < mod; r++)
				count[i][(r * e[digits[i]] + number[i]) % mod] += count[i - 1][r];
			s = (s * e[digits[i]] + number[i]) % mod;
			count[i][s]--;
			count[i][number[i] % mod]++;
			s = ((s - number[i] * e[length]) % mod + mod) % mod;
			answer += count[i][0];
		}

		printf("%d\n", answer);
	}
}
