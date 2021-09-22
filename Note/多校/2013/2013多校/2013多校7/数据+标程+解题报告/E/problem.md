# Cube number on a tree

## Problem Discription

The country Tom living in is famous for traveling. Every Year, many tourists from all over the world have interests in traveling there.

There are n provinces in the country. According to the experiences from the tourists came before, every province has its own preference value. A route’s preference value from one province to another is defined as the product of all the preference value of the provinces on the route. It’s guaranteed that for each two provinces in the country there is a unique route from one to another without passing any province twice or more.

Tom is a boy crazy about cube number. A cube number is a positive integer whose cube root is also an integer. He is planning to travel from a province to another in the summer vacation and he will only choose the route with the cube number preference value. Now he want to know the number of routes that satisfies his strange requirement.

## Input

The input contains several test cases, terminated by EOF.

Each case begins with a number $n$($1 \leq n \leq 50000$), the number of the provinces.

The second line begins with a number $K$($1 \leq K \leq 30$), and $K$ difference prime numbers follow. It’s guaranteed that all the preference number can be represented by the product of some of this $K$ number(a number can appear multiple times).

The third line consists of $n$ integer numbers, the ith number indicating the preference value $P_i$ of the ith province.

Then $n-1$ lines follow. Each line consists of two integers $x$, $y$, indicating there is a road connecting province $x$ and province $y$.

## Output

For each test case, print a number indicating the number of routes that satisfies the requirement.

## Sample Input

	5
	3 2 3 5
	2500 200 9 270000 27
	4 2
	3 5
	2 5
	4 1

## Sample Output

	1
