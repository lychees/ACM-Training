# Present Day, Present Time

## Description

Sangxin and Bicycle play games everyday, but no matter what they play, Sangxin always loses.
Sangxin found that there is no chance to beat Bicycle even playing dice.

One day, Sangxin came up with a brand new game with stones. In this game there are $n$ piles of stones and $m$ recycling centers,
each pile of stones has $A_i$ stones and each recycle center could process ***exactly*** $B_i$ (which is pre-assigned) stones at a time.
Sangxin and Bicycle operate by turns. Each turn the player must pick one piles of stones and recycle some stones.
Note that they can use recycling centers *unlimited times* in one turn. The one couldn't do anything during his turn loses.

After thinking a while Sangxin thought the game is too easy and appended a weird rule:
***After*** someone's turn if there are no way to completely recycle any pile of stones, he loses immediately.

Now, given the initial state of the game, Sangxin wants to know that who will win. Assume they will play in optimal strategy.
The players' name and who will play first is given.

## Input

The input contains several test cases, terminated by EOF. Most of test cases are rather small.

Each case has 4 lines, the first line contains two integer $n$($1 \leq n \leq 100000$) and $m$ ($1 \leq m \leq 100$),
which denotes the number of stone piles and recycling centers.
The second line contains two string (length not greater than $20$ and contains only lowercase letters) indicating the players' name.
The first player in that line plays first.
The third line contains $n$ integers, i-th denotes $A_i$($1 \leq A_i \leq 1000000000$) and next line contains $m$ integer, i-th denotes $B_i$($1 \leq B_i \leq 100$).

## Output

For each case output the winner's name on separate lines.

## Sample Input
	2
	3 2
	sangxin bike
	1 2 3
	2 3
	3 1
	bike sangxin
	3 4 9
	1

## Sample Output
	bike
	bike
