

- [http://dreamoon4.blogspot.com/2015/05/2015-google-code-jam-round-2.html](http://dreamoon4.blogspot.com/2015/05/2015-google-code-jam-round-2.html)
- [https://codingcompetitions.withgoogle.com/codejam/round/0000000000433651](https://codingcompetitions.withgoogle.com/codejam/round/0000000000433651)

# Problem A
简单扫一遍，对每个箭头，上下左右扫描，如果有孤立的结点那么显然无解。否则如果该箭头不指向其他箭头，那么答案 +=1。

# Problem B
贪心即可，注意精度。

# Problem C
最小割。对每个 word 拆点，流量为 1。对每个 sentence 连所有关联的 word，流量无穷大。然后直接求 sentence0 到 sentence1 的最小割即可。

为啥？这样建模后，考察所有 s 到 t 的路径，中间相邻的每个 word 必定属于同一种语言，且第一个单词必属于 s 语言，最后一个单词必属于 t 语言，则中间必有一个单词同时属于 s、t 语言，此时的最小割既最少有多少种语言同时属于 s、t。

# Problem D
TBD。
计数题，分类讨论比较复杂，Polay 计数法或者 DP 加维。
