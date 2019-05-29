# Weekly Algorithm Contest 4.29 - 5.06
[Read Me in HackMD](https://hackmd.io/s/BJLrY8N9V)

CF：
GCJ 1B：
TCO 1B：

我比赛时的代码有两处 bug。。。

https://community.topcoder.com/stat?c=problem_solution&rm=332485&rd=17509&pm=15422&cr=22727863

1. 没有正确处理自环。导致一旦出现自环，标记会永远无法清除。
2. n++ 的时候被遮盖，导致外面的全局变量没有加上。

grumpy_gordon

https://community.topcoder.com/stat?c=problem_solution&rm=332480&rd=17510&pm=15422&cr=40234235
