# Asia Hong Kong Online Preliminary # 

___


- [Board](https://asiahk16prel.kattis.com/problems/palindromes "Board")
- [Trainning](https://open.kattis.com/problem-sources/Hong%20Kong%20Regional%20Online%20Preliminary%202016 "Trainning")


## Problem A. A+B Problem ##
### Brief description ###
.

### Analysis ###
FFT.

## Problem B. Boxes ##
### Brief description ###
...

### Analysis ###
dfs()

## Problem C. Classrooms ##
### Brief description ###
.

### Analysis ###
.

## Problem D. Curious Cupid ##
### Brief description ###
.

### Analysis ###
莫队算法。



## Problem E. 	Dim Sum ##
### Brief description ###
.


### Analysis ###

.

## Problem F. 	Crazy Driver ##
### Brief description ###
.

### Analysis ###
贪心，如果当前时间不够通过关卡，那么只要通过在当前途径过的最小的边反复横跳来拖延时间即可。


## Problem G. 	k-Colouring of a Graph ##
### Brief description ###
给个无向图，满足每个联通快的边数最多是点数 + 2，现在给这个图染色，相邻的点颜色不能相同，输出染色的方案数 %p，点数 1 <= n <= 50000，颜色数 1 <= k <= 1e9。

### Analysis ###
[https://async.icpc-camp.org/d/549-2016-g/6](https://async.icpc-camp.org/d/549-2016-g/6)

## Problem G. 	Let's Meet ##
### Brief description ###
.

### Analysis ###
.

## Problem I. 	Palindromes ##
### Brief description ###
.

### Analysis ###
考虑用 manacher 处理出了每个位置的回文半径 r[i]。。
那么对于每组询问 (l, r)，只需要统计..
 \sigma_{i=l}^r min(r[i], i-l+1, r-i+1) 即可。

（注意 manacher 中我们加了额外的字符。。要把询问的区间映射过去。。）
（最后算答案时再去掉多出来部分即可。。）

    Rush{
        int l, r; RD(l, r); l = l * 2; r = r * 2; --a; ++b;
        LL z = 0;
        for (int i=1;i<n;++i){
            z += max(0, min(::r[i], i-l+1, r-i+1));
        }
        z -= (r-l)/2+1;
        z /= 2;
    }

注意到可以分类讨论去掉 min 里面的一个条件。
再离线用两个树状数组维护即可。

- [http://blog.jisuanke.com/?p=56](http://blog.jisuanke.com/?p=56)
- [http://yyy.is-programmer.com/posts/202954.html](http://yyy.is-programmer.com/posts/202954.html)

## Problem I. 	Take Two Stones ##
### Brief description ###
...

### Analysis ###
考虑不变量，因为总是两个两个取。
所以无论怎么取都不影响结果的奇偶性。