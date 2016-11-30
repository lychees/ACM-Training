# Codeforces Round #371 (Div. 1) # 

___

[http://codeforces.com/contest/713](http://codeforces.com/contest/713 "http://codeforces.com/contest/713")


[https://async.icpc-camp.org/d/553-2016](https://async.icpc-camp.org/d/553-2016
                                         "https://async.icpc-camp.org/d/553-2016
")


## Problem A. Sonya and Queries ##
### Brief description ###
维护一个 multiset，支持以下操作：

- 加入一个数 x。 
- 删除一个数 x。
- 询问一个 01 串，问数组中数位的奇偶性和该 01 串相同的数的个数，注意原数字前面可以补 0，比如 "010" 也可以匹配 74。

### Analysis ###
直接用 long long 读取询问，
用 map 记录对应的答案，以避免繁琐的补 0。

## Problem B. Searching Rectangles ##
### Brief description ###
交互题，一个 n*n 的区域，里面有 2 个没有相交部分的矩形。
每次你可以询问一个区域，返回这个区域中有几个（0，1，2）矩形，被询问完全覆盖。
你要在 200 次询问内，确定那那 2 个矩形的位置。

### Analysis ###
二分出每一条边，然后 dfs() 生成所有可能的组合情况，从中筛选出合法的一组，非重叠的条件可以确保不会产生多解，注意 dfs() 的检查过程中提前判断掉不合法的询问。

## Problem C. Sonya and Problem Wihtout a Legend ##
### Brief description ###
给定一个数组，每次编辑可以使一个数 +1s 或 -1s。
求最少的编辑次数，使得该数组严格递增。

### Analysis ###
[http://codeforces.com/blog/entry/47059?#comment-314647](http://codeforces.com/blog/entry/47059?#comment-314647 "http://codeforces.com/blog/entry/47059?#comment-314647")

## Problem D. Animals and Puzzle ##
### Brief description ###
给定一个 01 矩阵，每次询问一个子矩阵里的最大全 1 方阵。

### Analysis ###
dp，二维 RMQ，二分答案。 


fork: [http://vjudge.net/problem/HDU-2888](http://vjudge.net/problem/HDU-2888 "http://vjudge.net/problem/HDU-2888")

我们 dp 预处理出，每个结点为右下角时的最大方阵的边长，用这个来进行二维 RMQ。
最后外面再套一层二分答案，来避免越界。



## Problem E. Sonya Partymaker ##
### Brief description ###
一个环上 m 个点，n 个人在 n 个位置。
在开始时，你给每个人决定一个移动方向，每个回合都会朝那个位置移动一格。
问要经过所有的点，至少需要多少时间。


### Analysis ###

二分答案 + 贪心？
