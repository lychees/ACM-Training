## Brief Description 
给定 n、k。构造序列 a，满足 a 的为 k 为二进制数，且 前缀或 严格单调递增。
求满足要求的方案数，答案对 1e9+7 取模。

　n ≤ 1e18,k ≤ 3e4

## Solution
首先注意到为了让 前缀或 的结果序列递增，每次或出来的数至少需要新增加一位，因此当 n > k 时无解。下文标记时间复杂度时，不再区分 n 和 k。

可以先写一个 O(n3) 暴力 DP。
https://codeforces.com/contest/623/submission/57731850

v += u * $\binom{k-j}{d} \times 2^j$

我们枚举每一轮新增加的位数 d，中间的组合数表示从可用的 k-j 个位置中选出 d 个位置的方案数，右边的 2 次幂表示之前的 j 个已经使用的位置，这一轮可选可不选。

我们注意到上面的转移方程与 i 无关，于是思考使用快速幂整体转移进行加速。https://codeforces.com/contest/623/my

复杂度变为 O(n2logn)（可以多过了一个点。）

到这一步，就很容易观察到卷积形式。
用 [FFT mod 1e9+7](https://sd-invol.github.io/algorithm/2016/02/13/FFT-mod-prime.html) 即可。


## 参考资料
- https://codeforces.com/blog/entry/23278



## 
7 次：[https://codeforces.com/contest/623/submission/15975907](https://codeforces.com/contest/623/submission/15975907)
4 次：[https://codeforces.com/contest/623/submission/20766987](https://codeforces.com/contest/623/submission/20766987)