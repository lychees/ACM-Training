- [Leader Board](https://twitter.com/TangFeihu/status/1151589024676495361)

这把有幸和教主一个房，250 可以比较无脑，500 比较考验树形 DP 基本功，1000 和上次 Beijing Onsite 的第三题一样，是个求数学期望的题目，但是难度要大很多。

### 250 CutCutCut
#### Brief Description
一个矩形纸片上给 n 条切痕，问纸片被切割为多少块。数据保证不会有三线共点的情况。

#### Analysis
直接无脑给线段相交模板即可。由于数据没有各种 Conner Case，所以更好的方法应该是把矩形边界映射到数轴上，然后排序判断。（教主）

### 500 RootItRight

#### Brief Description
给定一颗树，每个节点的权值为 val(x)。定义 f(x) 表示以 x 为根时，从根节点走到每个其他节点的代价的和。
走过去的代价，路径上每个点的权值与距离的乘积。求所有 f(x) 的最小值。

#### Analysis
树形 DP。
一般我们可以 dfs 两次，先统计 f(0)，然后每次把根换到子节点时的 delta。

第一部非常简单，就是：
 > dp[u] = dep[u]*val[u]*sz[u] + sigma dp[v]

考虑第二部，我们还需要一些辅助变量，我们用 sv[u] 记录这个节点的 val[u]*sz[u] + sigma sv[v]。
有了 sv 我们就可以轻易的计算出每次的 delta 了。