## Ref
- [ICPC Finals 2019, Codeforces](https://codeforces.com/blog/entry/66365)
- [地球队 Mirror Live Stream，ICPC World Finals 2019 mirror live stream with tourist and Endagorion](https://www.youtube.com/watch?v=X6YdKQspOBk)
- https://judge.icpc.global/problem-sources/ACM-ICPC%20World%20Finals%202019
- https://www.zhihu.com/question/318037136/answer/641749693

## A. Azulejos
分批丢进 set，贪心判断每次较小的一个 set 能否被满足。

反复执行以上操作，直到全部检查完毕。

## B. Beautiful Bridges

## C. Checks Post Facto

## D. Circular DNA
考虑只有一组括号序列的做法。

左括号 '(' + 1, 右括号 ')' - 1，求和后如果等于 0 显然不合法。

否则求和过程中的最小值，所有等于最小值的位置都是合法状态。

有多组括号序列时同理，预处理之后 O(n) 扫描过去即可，每个位置只会影响一组序列的状态。

## E. Dead-End Detector
分类讨论：
- 树：找叶子。
- 图：从叶子开始染色，找染色的边界。

注意输出的方向。

## F. Directing Rainfall

## G. First of Her Name
多模式串匹配。对每个询问翻转建立 AC 自动机，在文本树上跑一遍标记每个位置对答案的贡献，
注意每个位置除了自己还会影响所有 fail 树的祖先，最后再 dfs() 一遍统计答案即可。


## H. Hobson's Trains

## I. Karel the Robot

## J. Miniature Golf

## K. Traffic Blights

数轴上有 n 盏红绿灯，每个红绿灯有 x, r, g 三个参数分别表示，位置，红灯和绿灯的持续时间。每盏灯将会周期性的在红灯和绿灯两种状态之间切换，在 0 时刻，所有灯恰好都处在红灯刚刚开始的状态。某一辆小车，随机某个时刻从 0 点出发，速度为 1，
求小车第一次停留发生在分别发生在每盏红绿灯位置，或者顺利通过所有 n 盏灯而不发生停留的概率。

n <= 500, x <= 1e5, r+g <= 100, 红绿灯按照 x 递增的顺序给出




