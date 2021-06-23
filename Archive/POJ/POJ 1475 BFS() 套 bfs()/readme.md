# POJ 1475. Pushing Boxes

## 传送门
- [https://vjudge.net/problem/POJ-1475](https://vjudge.net/problem/POJ-1475
)

## 题意
超级经典推箱子问题，要求在 push 操作最小的情况下，move 操作也最小。

## 解法
先简化状态，只需要记录箱子位置和人所在的方向。
然后直接开 `priority_queue` 无脑暴搞就好了，[速度还快](https://vjudge.net/solution/31455829)...

不开 `priority_queue` 的话好像也能搞，我们根据 push 操作划分阶段，
然后在这个分层图上转移即可，注意这样并不能保证第一次访问的时候是最优解，要把上一层的转移全枚举完才行。

但是看网上代码好像直接默认第一次访问就是最优解了。。。总感觉可以构造数据 cha 了它们。。。

此题还有一个 [加强版](https://byvoid.com/zhs/blog/poi-1999-mag/) ...
