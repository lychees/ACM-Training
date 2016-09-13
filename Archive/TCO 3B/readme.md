# TCO 2016 3B # 

___



[http://codeforces.com/contest/704](http://codeforces.com/contest/704 "http://codeforces.com/contest/704")

[https://async.icpc-camp.org/d/529-codeforces-round-366](https://async.icpc-camp.org/d/529-codeforces-round-366 "https://async.icpc-camp.org/d/529-codeforces-round-366")

## 250. RemoveCharacters ##
### Brief description ###

给定两个字符串 A, B，问最多可以保留多少种字符，能使两个串相同。

### Analysis ###
dfs()，预处理出每个字符和哪些字符排斥。


## 500  ##
### Brief description ###
求构造一个只有  -> () 的布尔表达式（蕴含关系和括号），使得该表达式中恰有 n 个变量，且恰好在 k 种取值上为 true（注意没有 not，变量可以不出现在表达式中，这样它可以取任意值）。


### Analysis ###
构造。


## 1000 ##

### Brief description ###
给定 n 个机器人，选出最大的机器人集合，使得这个集合是相容的。
机器人集合是相容的意思是，其中任意两个机器人是相容的。
每个机器人有一个长度为 n 的猜拳序列，两个机器人开始比赛，它们会进行 n 次猜拳，每次猜拳会按照当前在猜拳序列中的位置依次出拳，
两个机器人相容的意思是，无论两个机器人的初始状态为何，比赛的结果都是固定的。

### Analysis ###

FFT？

