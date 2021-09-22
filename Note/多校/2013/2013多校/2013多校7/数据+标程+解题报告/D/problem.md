# Mutiples on a circle  

## Problem Discription

Tom has a necklace with $n$ jewels. There is a number on each jewel. Now Tom wants to selesct a wonderful chain from the necklace. A chain will be regarded wonderful if the wonderful value of the chain is a multiple of a key number $K$. Tom gets the wonderful value using this way：He writes down the number on the chain in clockwise order and concatenate them together. In this way, he gets a decimal number which is defined as the wonderful value.

For example, consider a necklace with 5 jewels and corresponding numbers on the jewels are 9 6 4 2 8 (9 and 8 are in neighborhood). Assume we take $K=7$, then we can find that only five chains can be multiples of $K$. They are 42, 28, 896, 42896 and 89642.

Now Tom wants to know that how many ways he can follow to select a wonderful chain from his necklace.

## Input

The input contains several test cases, terminated by EOF.

Each case begins with two integers $n$ ($1 \leq n \leq 50000$), $K$ ($1 \leq K \leq 200$), the length of the necklace and the key number.

The second line consists of $n$ integer numbers, the ith number $a_i$ ($1 \leq a_i \leq 10000$)indicating the number on the ith jewel. It’s given in clockwise order.

## Output

For each test case, print a number indicating how many ways Tom can follow to select a wonderful chain.

## Sample Input

	5 7
	9 6 4 2 8

## Sample Output

	5
