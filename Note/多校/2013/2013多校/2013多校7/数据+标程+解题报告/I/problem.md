# Trip Advisor

## Description ##

There is a strange country somewhere which its transportation network was built following some weird rules: Consider the transportation network as a connected undirected graph G with N nodes and M edges(nodes indicate cities,and people can travel from cities to cities by roads connecting them),the condition that every node in G is in at most one simple cycle holds.

One day Q people of the country want to make a travel, i_th people is located at city Ui, wants to move to city Vi(Ui can be equal to Vi),and he especially loves city Pi,so he wonders if there is a path that:

1) starts at Ui;
2) ends at Vi;
3) for every pair of adjacent cities in path,there is a road connecting them.
4) visits every city at most once.
5) ***visits city Pi;***

As a trip advisor,your task is to tell everybody whether there is a path satsifying all his requirements.

## Input ##
The input contains several test cases, terminated by EOF. Most of test cases are rather small.

Each testcase contains $M + Q + 2$ lines, first line contains two integers $N$, $M$ ($1 \leq N, M \leq 200000$),
the number of cities and roads; next $M$ lines each contains two integer $b$, $e$ indicates that there is a bidrictional-road connecting city b and city e;next line an integer $Q$($1 \leq Q \leq 100000$) indicating number of people in that country that want to make a travel, next $Q$ lines each contains three integers $U_i$, $V_i$, $P_i$, denotes the query as we mentioned above.

## Output ##

For each test case output $Q$ lines, for i-th query, if there exists such path, output one line "Yes" without quotes, otherwise output one line "No" without quotes.

## Sample Input ##

	6 7
	1 2
	1 2
	3 4
	2 4
	5 6
	5 6
	4 5
	5
	1 6 3
	1 6 4
	1 2 5
	2 2 2
	2 2 3

## Sample Output ##

	No
	Yes
	No
	Yes
	No
