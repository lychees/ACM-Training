# GCD of Sequence

## Description

Alice is playing a game with Bob.

Alice shows $N$ integers $a_1, a_2, \dots, a_N$, and $M$, $K$. She says each integers $1 \leq a_i \leq M$.

And now Alice wants to ask for each d = 1 to M, how many different sequences $b_1, b_2, \dots, b_N$. which satisfies :

1. For each $i = 1 \dots N$, $1 \leq b[i] \leq M$
2. $\mathrm{gcd}(b_1, b_2, \dots, b_N) = d$
3. The number of difference between ${a_n}$ and ${b_n}$ will be exactly $K$

Alice thinks that the answer will be too large. In order not to annoy Bob, she only wants to know the answer modulo 1000000007.

Bob can not solve the problem. Now he asks you for HELP!

***Notes***: $\mathrm{gcd}(x_1, x_2, \dots, x_n$) is the greatest common divisor of $x_1, x_2, \dots, x_n$

##Input

The input contains several test cases, terminated by EOF.

The first line of each test contains three integers $N$, $M$, $K$. ($1 \leq N, M \leq 300000, 1 \leq K \leq N$)

The second line contains $N$ integers: $a_1, a_2, \dots, a_N$, ($1 \leq a_i \leq M$) which is regional sequence.

## Output
For each test contains 1 lines :

The line contains M integer, the i-th integer is the answer shows above when d is the i-th number.

## Sample Input
	2
	3 3 3
	3 3 3
	3 5 3
	1 2 3

## Sample Output
	7 1 0
	59 3 0 1 1

## Hint

In the first test case :

when d = 1, {b} can be :

1. (1, 1, 1)
2. (1, 1, 2)
3. (1, 2, 1)
4. (1, 2, 2)
5. (2, 1, 1)
6. (2, 1, 2)
7. (2, 2, 1)

when d = 2, {b} can be :

1. (2, 2, 2)

And because {b} must have exactly K number(s) different from {a}, so {b} can't be (3, 3, 3), so Answer = 0
