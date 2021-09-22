# Backup Plan

## Description

Makomuno has $N$ servers and $M$ databases.
All databases are synchronized among all servers and each database has a ordered list denotes the priority of servers to access.
This list is guaranteed to be a valid permutation of all servers.

Every time someone wants to execute queries on a certain database, he will send a request to the first server in the list.
If it's dead, he will simply turn to the next one. Otherwise a working copy of the database is found, and this copy is called active.

Now, given $N$ and $M$, Makomuno wants to find a permutation for each database which could assure that all servers are load-balanced.
Moreover, Makomuno hopes the system will be load-balanced even if ***exactly*** one server is broken.

Note that if we call the number of active copies on i-th server $A_i$, then load-balanced means $\mathrm{max} |A_i - A_j| \leq 1$ for any $i$ and $j$ in non broken servers set.
We won't consider broken servers in this case.

## Input

The input contains several test cases, terminated by EOF.

Each test case has one line containing two integer $N$ ($2 \leq N \leq 100$) and $M$ ($1 \leq M \leq 100$).

## Output

For each case output $M$ lines, the i-th line contains a permutation of all servers, indicating the expected order.
Servers are numbered from $1$ to $N$.

## Sample Input
	5 3

## Sample Output
	2 4 3 1 5
	1 5 4 2 3
	3 5 2 4 1

## Hint
In the sample test case, the active copies of these databases are on server 2,1 and 3 in normal state. A = {1,1,1,0,0}

If server 1 or 3 has broken, server 5 will take its work.
In case we lost server 2, the second database will use server 4 instead. A = {1,BROKEN,1,1,0}

It's clear that in any case this system is load-balanced according to the plan in sample output.