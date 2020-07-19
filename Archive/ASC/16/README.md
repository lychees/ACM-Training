[toc]

# Problem A. Cactusability
定义一个一棵树的仙人掌力（Cactusability）为有多少种添加边的方案，使得可以将其转化为仙人掌（cactus）。
给定一棵树，求其仙人掌力。

非常 nice 的树形 DP。

# Problem B. Darts
？？？

# Problem C. Domino in Casino
给定一个 nxm 的矩阵，你可以往其中放置 k 枚多米诺骨牌，每块骨牌的得分是覆盖的两个格点的全值的乘积。
求一种覆盖方案，最大化 k 枚骨牌的得分之和。

k 比较大，状态压缩 DP 会爆，所以用费用流。

# Problem D. Young Hackers
给定一个文本串 T，一个模式串 P，对文本串的每个后缀，求出其与模式串每个后缀的 LCP 的最大值。

这里面最大的那个值，显然就是最长公共子串（LCS）。所以我们用 SPOJ LCS2 的代码改改就好了。
文本串和模式串都反过来跑后缀自动机。

# Problem E. Mazes Exit Guide
给定两个有向图，每条边都有一个颜色，保证每个点出发的边，颜色两两不同。
问是否存在一个颜色序列，使得两个图分别从各自的起点出发，沿着该序列的边遍历，均可以到达各自的终点。

记忆化搜索，dp[100][100]。类似 [ZOJ 的那道 double maze](https://vjudge.net/problem/ZOJ-3420)。

# Problem F. Nonequal Parts
分硬币游戏，Alice 和 Bob 轮流从当前状态中选出任意一堆，并拆分成任意多堆，要求本次拆分出的堆中，没有两个硬币数是相同的。不能拆分时判负。求初始为一堆 n 个硬币的胜负态，并构造一组初始的操作方案。
SG 函数基本功。

# Problem G. Primitive Product
？？

# Problem H. Rent A Car
费用流裸题。

# Problem I. Roundtrip
# Problem J. Yet Another Minimal Triangle
给定一组点集，从中选取三个点，使得形成的三角形面积最小（不可退化）。

O(n3) 居然能暴过去。。。不知道是不是 intended behavior。
正解可以看 [peter50216](https://codeforces.com/gym/100218/submission/4004043) 的。
