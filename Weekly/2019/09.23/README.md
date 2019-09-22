# Weekly Algorithm Contest 09.09 - 09.16
[Read Me in HackMD](https://hackmd.io/@E-5gxTGiSByBOKpvsaKa_g/H1Jg_HC8B)

# The Preliminary Contest for ICPC Asia Shanghai 2019

2019 ICPC Asia 上海赛区邀请赛

* 比赛地址：[https://www.jisuanke.com/contest/3003?view=challenges](https://www.jisuanke.com/contest/3003?view=challenges)
* 知乎吐槽：[https://www.zhihu.com/question/346118242](https://www.zhihu.com/question/346118242)

## A. Lightning Routing I

### 题意
给定一个边权树，要求支持动态修改边权，询问到某个点最远的点的距离。

### 解法
我们知道，树的直径可以通过两次 dfs() 的方法求得。换句话说，到任意点最远的点，一定是直径的某个端点（反证法）。因此原问题转化为动态维护直径，然后再支持询问两个点的距离，后者可以 dfs 序 + lca + 树状数组。

动态维护直径可以用点分治（点分树），具体做法是，考虑过分治中心的最长路径，我们只需要查询分别以分治中心的每个儿子为根，所在子树的最长链，从中再找到最长和次长即可，这个星状图可以用 set 维护。每个子树则可以使用 dfs 序 + 线段树维护。复杂度 O(nlog2n)。

对于动态维护直径，存在一个基于树的全 DFS 序的非常巧妙的做法，可以把复杂度改进到 O(nlogn)。具体可以看 [这篇博客](https://www.cnblogs.com/TinyWong/p/11260601.html)。[First Blood](https://gist.github.com/lychees/cb9b788f82399071d251d9c182a8e0ba) 中，雅礼中学就是采用这种做法。

当然事实上我们可以使用子集动态树直接维护最远的距离，完全不用考虑直径，均摊复杂度为 O(nlogn)，代码也会更短。

## B. Light bulbs
### 题意 
编号为 0~n-1 的灯泡，初始都是关闭的，m 次操作，每次 操作把一个区间的灯泡就像翻转，问最后打开的灯有多少个。
### 解法
签到题。注意复杂度应该是 O(mlogm)，把区间进行排序(或者区间端点 进行排序)，左区间+1, 右区间-1, 然后求前缀和得出每一段的状态。


https://www.cnblogs.com/Hugh-Locke/p/11523676.html
https://www.cnblogs.com/nervendnig/p/11525240.html


## C. Triple
### 题意 
从三个数组中各选一个数，要求这三个数:任意两个数差的绝对值小于等于第三个数。

### 解法
也就是三个数当中最大的数要小于等于另外两个数的和。
- 对于N <= 1000, 使用O(N^2)暴力解法即可。
- 对于N>1000, 用FFT做。枚举其中最大的数，另外两个用FFT进行 组合，注意去除重复的情况。

分享几个程序作为参考: https://paste.ubuntu.com/p/mRM8XKdRwC/

G
https://www.cnblogs.com/hua-dong/p/11523646.html
L
https://blog.csdn.net/qq_43627087/article/details/100861122


https://wutao18.github.io/2019/09/15/2019-ACM-ICPC-%E4%B8%8A%E6%B5%B7%E7%BD%91%E7%BB%9C%E8%B5%9B-B-Light-bulbs-%E5%B7%AE%E5%88%86/#more


## The Preliminary Contest for ICPC Asia Shenyang 2019


* 比赛地址：[https://www.jisuanke.com/contest/3007?view=challenges](https://www.jisuanke.com/contest/3007?view=challenges)
* 知乎吐槽：[https://www.zhihu.com/question/345978132/answer/823854996](https://www.zhihu.com/question/345978132/answer/823854996)

### A. Maomao's candy