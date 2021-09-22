# Finding string

## Description

Richard is a smart data analyst in a famous company. One of his daily boring work is to find how many times does a pattern string occur in a very long string.

Luckily, Richard notices that there are many consecutive repeated substrings in this very long string, so he uses the following compression algorithm to make the string shorter:

a) Find a **non-compressed** consecutive repeated substring of the original string, e.g. “ab” in “cabababd”.

b) Replace the repeating part with the bracketed repetend, followed by the times the repetend appears in the original string. e.g. Write “cabababd” as “c[ab]3d”. Note she can also write it as “c[ab]1ababd” or “ca[ba]2bd” and so on, although these string are not compressed as well as the first one is.

c) Repeat a) and b) several times until the string is short enough.

However, Richard finds it still a bit hard for him to do his work after the compression. So he orders you to write a program to make his work easier. Can you help him?

## Input

The input contains several test cases, terminated by EOF. The number of test cases does not exceed 10000.

Each test case contains two lines, denote the compressed text and pattern string. The decompressed text and pattern string contain lowercase letter only. The first line contains only lowercase letters (a-z), square brackets ([]) and numbers (0-9), and the second line contains only lowercase letters (a-z). The brackets must be followed with an integer $t$($1 \leq t \leq 2^31-1$) indicating the times the string in the brackets repeat. The brackets **won't** be nested.

You can assume the length of the compressed string and pattern string won't exceed $500$.

Please note that for most test cases, the length of the pattern string is relatively very small.

## Output

For each test case, print a single line containing the times this pattern string occurs in the very long string.

## Sample Input
	[ab]10aaba
	ba

## Sample Output
	11
