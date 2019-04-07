## Ref
https://judge.icpc.global/problem-sources/ACM-ICPC%20World%20Finals%202019
https://www.zhihu.com/question/318037136/answer/641749693
[地球队 Mirror Live Stream，ICPC World Finals 2019 mirror live stream with tourist and Endagorion](https://www.youtube.com/watch?v=X6YdKQspOBk)


## A. Azulejos
分批丢进 set，贪心判断每次较小的一个 set 能否被满足。

反复执行以上操作，直到全部检查完毕。

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

## F. 

## G. First of Her Name
多模式串匹配。对每个询问翻转建立 AC 自动机，在文本树上跑一遍标记每个位置对答案的贡献，
注意每个位置除了自己还会影响所有 fail 树的祖先，最后再 dfs() 一遍统计答案即可。


## H. Hobson's Trains
