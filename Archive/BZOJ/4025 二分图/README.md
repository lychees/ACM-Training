
# BZOJ 4025. 二分图

[DarkBZOJ 传送门](https://darkbzoj.tk/problem/4025)
[https://www.cnblogs.com/ZeonfaiHo/p/7502056.html](https://www.cnblogs.com/ZeonfaiHo/p/7502056.html)
[HackMD](https://hackmd.io/@E-5gxTGiSByBOKpvsaKa_g/BylGaSkbP)

## 题意
给定一个 n 个点, m 条边的无向图, 每条边在一定时间范围内存在. 要你判断每个时间点这张图是否为二分图。(n ≤ 1e5，m≤2e5)

## 题解
我们可以用 Link-Cut Tree 离线的维护图的连通性，方法是我们把图当成树来处理，维护出路径上最脆弱的边（也就是最早消失的边）即可，当新插入的边连接的两个点已经处在一个连通分量时，如果新的边更加健康，我们就去替换掉那条边，关于 Link-Cut Ttre 维护路径最值的操作，参考 [HDU 4010](http://www.shuizilong.com/house/archives/hdu-4010-query-on-the-trees/)，这里因为还要找到那条边，我用了 `pair<int, node*>`。

（这好像其实也就是 Link-Cut Tree 最正经的用途之，优化网络流！）

回到这个题，我们只需要再维护一下路径的 size，判断一下是否有奇数个点（或者偶数条边）即可，由于现在考察的对象既有边又有点，还有换根操作，着实容易写错，干脆的把原图中的边也放进 Link-Cut Tree 里去维护。

[代码](https://github.com/lychees/ACM-Training/blob/master/Archive/BZOJ/4025%20%E4%BA%8C%E5%88%86%E5%9B%BE/A.cpp)。
