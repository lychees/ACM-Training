[toc]

- [https://codeforces.com/gym/100217](https://codeforces.com/gym/100204)
- [http://blog.watashi.ws/640/andrew-stankevich-8-solution/](http://blog.watashi.ws/640/andrew-stankevich-8-solution/)
- [http://david.is-programmer.com/posts/22227.html](http://david.is-programmer.com/posts/22227.html)

# Problem A. Nonoptimal Assignments
给定 n，构造一个 n*n 的矩阵，使得按题目所给的“贪心”算法，不能得到正确解。

# Problem B. Cryptography
有 n 个 2×2 矩阵，m 次询问，每次询问需要快速回答区间 [i, j] 内矩阵的积 (mod r)。
(n<30000, m<30000)

矩阵乘法满足结合律，因而同样可以使用线段树。

# Problem C. Fibonacci Subsequence
给定一个长度为 n<=3000 的序列，要求满足 Fibonacci 性质的最长的子序列。

枚举前两个元素，那么下一个元素的位置显然是满足 Fibonacci 性质的最近的位置。但这样假设给定的序列就是 Fibonacci 序列，复杂度会退化到 O(n3)，于是考虑动态规划。dp[i][j] 表示末尾下标为 i 和 j 元素时，满足条件的最长子序列的长度。

一般说来这样就可以了，但是这个题有点 old school 时限和记忆体都给的很紧，很容易 TLE 和 MLE，需要使用 unordered_map，以及 倒着转移，避免开额外的记忆体进行二分查找和构造答案。中间的 map 也需要注意不要下标引用不存在的元素，即使那不影响复杂度也会导致 MLE。

# Problem D. Equations System
在多项式上跑扩展欧几里得。

# Problem E. Fool’s Game
Hall’s marriage theorem 

# Problem F. Lottery
直接组合 DP 就好。

# Problem G. Two Pipelines
简单几何。

# Problem J. Great Siberian Wall
平面点集最小三角形覆盖

[https://zhuanlan.zhihu.com/p/129273001](https://zhuanlan.zhihu.com/p/129273001)
