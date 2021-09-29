#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 55;
int n, len, half, f[N][N];
char a[N*2], b[N], fres[256];
void flip(int len, char a[], char b[]) {
	for (int i=1; i<=len; ++i) b[i] = a[i];
	reverse(b+1, b+len+1);
	for (int i=1; i<=len; ++i) b[i] = fres[b[i]];
}
bool match(int s1, int e2) {
	for (int l1=1; l1<half; ++l1) {
		if (f[s1][e2-l1+1] >= l1) {
			if (f[s1+l1][e2-half+1] >= half-l1) return true;
			for (int l2=l1+1; l2<half; ++l2)
				if (f[s1+l1][e2-l2+1] >= l2-l1 && f[s1+l2][e2-half+1] >= half-l2)
					return true;
		}
	}
	return false;
}
void run(int T) {
	char ch[5]; int num;
	len = 0;
	for (int i=1; i<=n; ++i) {
		scanf("%s%d", ch, &num);
		while (num--) a[++len] = ch[0];
	}
	half = len >> 1;
	for (int i=1; i<=half; ++i) a[len + i] = a[i];
	flip(len, a+half, b);
	
	for (int i=len; i; --i)
		for (int j=len; j; --j)
			if (a[i] == b[j]) {
				if (i<len && j<len)
					f[i][j] = f[i+1][j+1] + 1; else
					f[i][j] = 1;
			} else
				f[i][j] = 0;
				
	bool ans = false;
	for (int i=1; !ans && i<=half; ++i)
		ans = match(i, len-i+1);
	printf("Polygon %d: ", T);
	puts(ans ? "Possible" : "Impossible");
}
int main() {
	fres['N'] = 'S', fres['S'] = 'N', fres['E'] = 'W', fres['W'] = 'E';
	int T = 0;
	while (scanf("%d", &n) && n) run(++T);
	return 0;
}
