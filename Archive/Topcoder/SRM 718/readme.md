# SRM 718

## Ref
- http://codeforces.com/blog/entry/53266

## Div 1 250 InterleavingParenthesis
给定两组括号序列 s1, s2。问有多少种将它们 Interleave 的方法，
使得新的序列是合法的括号序列，只要 Interleave 的方法不同，就算做不同。

DP。
首先统计 s1, s2 的每个前缀包含多少 '('，用来判断每个状态是否合法。
dp[i][j] 表示在 s1 中选了前 i 个，在 j 中选择了前 j 个的方案数。
dp[i][j] = 0 如果不合法。
           dp[i-1][j] + dp[i][j-1] 合法。

## Div 1 500 CircleCity
一个圆环上分布着 n 座城市，给定相邻城市间的距离。
你可以设置至多 k 个传送门，传送门之间可以瞬间移动，求该图的直径的最小值。

二分答案，贪心。
注意到传送门的位置可以是任意两座城市的中点，这样 DP 就显得不太可行。(O(n6)?)
于是我们考虑二分答案，然后破环为链，枚举一个端点，贪心看可以分成多少段，每段把传送门放在中点即可。

## Div 1 1000 PermutationSubsequence
给定一个排列，我们定义一个排列的 k-diversity 为，对于它的所有长度为 k 的子序列取相对大小后多少种不同的排列。

显然，一个长度为 n 的排列的 k-diversity 最大为 \Binom(n, k)。
现在给定一个不完整的排列 P，问如何填数，使得它的 k-diversity 达到最大值的 k 最大。







