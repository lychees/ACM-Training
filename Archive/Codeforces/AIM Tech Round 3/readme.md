# Codeforces AIM Tech Round 3 # 

___

- [http://codeforces.com/contest/708](http://codeforces.com/contest/708 "http://codeforces.com/contest/708")
- [https://async.icpc-camp.org/d/530-aim-tech-round-3](https://async.icpc-camp.org/d/530-aim-tech-round-3 "https://async.icpc-camp.org/d/530-aim-tech-round-3")

## Problem A. Letters Cyclic Shift ##
### Brief description ###
给定一个字符串，可以选择一个非空的连续的区间，将每个字符向前 shift 一位（'a'->'z'，'b'->'a', 'c'->'b', etc），问所能得到的字符串字典序最小是多少。

### Analysis ###
贪心。

## Problem B. Recover the String ##
### Brief description ###
给定 a00, a01, a10, a11 四个数，问你是否存在一个 01 串，使得长度为 2 的子序列中 00, 01, 10, 11 的出现次数恰好是那四个数。如果是，构造任意一个符合要求的解。

### Analysis ###
构造。

## Problem C. Centroids ##

### Brief description ###
给定一颗树，问每个节点是否能通过至多一次边替换操作，变成重心的潜力。边替换操作指的是，删除一条边，再添加一条边，使得仍然为一棵树。

### Analysis ###
考察一个点 u 是否具有成为重心的潜力，如果是重心，那么满足条件。如果不是，那么至多只会有一个子树过于臃肿，设这棵子树为 v，我们肯定从那棵子树中裁剪去一个更小的子树 w，并把 w 直接接到 u 上。

还需要满足两个条件：

- 子树 w 本身不能太大。
- 子树 v 减去 w 后要足够小。

这样我们只要找到满足条件的最大的 w 剪去就可以了。

【C1.cpp】

进一步分析，设树的重心为 c，不难证明（反证），c 一定包含于子树 v 之中，我们以 c 为根，c 的孩子分别为 u0、u1、u2... 考察以 u0 为根的子树中的某个点 v0，我们要裁去的边一定在 v0 所在的子树之外。进一步，因为这些子树本身一定都不超过 n/2，如果这条边在某个子树内部，
我们一定可以往上移动它到与 c 相连的地方。

我们希望裁去一棵最大的子树 u_max，如果此时 v0 之上的点也合法，那么 v0 即时符合要求的解。

但如果 u_max 就是 u0，那么： 

- 如果 u\_max 的 size 恰好为 n/2，也就是整棵树恰好有两棵重心 (c 和 u_max），那么当然也是合法的（在有两个重心的情况下，所有点都是合法的）。

- 否则，直接减取 u_max 肯定不合法，这种情况下我们还要尝试次大的子树。

【C2.cpp】



## Problem D. Incorrect Flow ##
### Brief description ###
D：给定一个网络流的 容量函数 c 和 流量函数 f，在 c 和 f 上做最小的修改，使得 f 是合法的流量函数。

### Analysis ###

最小费用可行流，仿照上下界可行流中的方法来解决流量平衡的问题即可。

[http://www.cnblogs.com/kane0526/archive/2013/04/05/3001108.html](http://www.cnblogs.com/kane0526/archive/2013/04/05/3001108.html "http://www.cnblogs.com/kane0526/archive/2013/04/05/3001108.html")


## Problem E. Student's Camp ##
### Brief description ###
给定一个 n*m 的墙，每天白天，左边裸露出来的部分有 p 概率被风摧毁，晚上，右边裸露的部分有 p 概率被摧毁，问最后墙体不发生坍塌的概率。

### Analysis ###
动态规划。

先考虑 Naive 的方法，首先层与层之间相互独立。

    Int pr(int n){
    	return binom(k, n)*pow(a, n)*pow(b-a, k-n)/pow(b, k);
    }
    Int pr(int l, int r){ //于是有每层最后的剩下的区间为 [l, r] 的概率。
    	return pr(l)*pr(m-1-r);
    }

按照层数划分阶段，我们有

	dp[i][l][r] = pr(l,r) * \sum dp[i-1][ll][rr]

这里要求区间 [l, r] 与 [ll, rr] 有重叠部分。

设 sr[l] 表示右端点小于 l 的和，sl[r] 表示左端点大于 r 的和。

	dp[i][l][r] = pr(l,r) * (all-sr[l]-sl[r])

至此状态为 O(n3)，转移为 O(1)，进一步，注意到 sl, sr 彼此对称。
我们直接用 sr 表示状态。

	sr[i][r] = sl[i][r-1] + \sum pr(l, r) * (all-sr[l]-sr[m-1-l])

最后将转移方程中的 l 和 r 分离，再用一次前缀和，至此状态 O(n2)，转移 O(1)。




