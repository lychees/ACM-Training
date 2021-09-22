# Pirate's Chest

## Description
Explorer yy feels lucky that he has got N rather valuable chests by chance. But he had problem opening them.
After doing some research for days, he has a clue. Let us number the chests from 1 to N, the chest with number i can be open in three ways:

1) Open it with the key with number Ai.
2) Open it with the crowbar with number Bi.
3) Just open it by force, doing that will decrease yy's HP by Di. yy will die if his HP is less or equal to zero.

Initially, yy has no keys and no crowbars, the tools are stored in a tower which is in the control of monsters.
The tower has M floors, every floor can be considered as a 20x20 grids and contains at most two tools,
and in case that it contains two tools, those two tools must be the same kind (i.e. both keys or crowbars).
Each cell contains either a monster or a tool. If yy stands on a cell with tool, he can pick it up.
But if the cell contains a monster, a fight will take place and cost his HP. After the battle this cell will turn into an empty one.
On each floor there exist **exactly** one special "entry" cell, this cell is empty, when yy get to the floor, he will be teleported to that cell immediately.
Note that yy can move upstairs or downstairs at any cell.

Once a tool get picked, it can be used arbitary times. It is guaranteed that every tool mentioned will appear *at most once*.

yy simply hates moving upstairs, as his friend, you're asked to calculate the minimum number of floors yy should go so that he can open all the N chests and still alive, and the minimum total HP cost in above case.

## Input
The input contains several test cases, terminated by EOF. Most of test cases are rather small.

In each case first line contains three integer N, M, H (1 <= N <= 30000, 0 <= M <= 1000, 1 <= H <= 10^9), denotes number of chests, number of floors, and yy's initial health points (HP).
Next n lines each contains three integers Ai, Bi and Di (1 <= Ai,Bi <= m, 1 <= Di <= 1000).
Next m blocks describing the tower, each block has a 20x20 map describing the floor, the values denotes (suppose the value is x):

+ 0 <= x <= 1000 : a monster, defeating it will decrease yy's HP by x.
+ 100000 < x <= 101000 : a key with number x - 100000.
+ 200000 < x <= 201000 : a crowbar with number x - 200000.
+ -1 : "entry" cell as we mentioned above.

## Output ##
For each case, if yy cannot survive after having opened all N chests, print one line "Impossible." (without quotes).
Otherwise output two integers: the minimum number of floors yy should go and the minimum total HP cost in that case.

## Sample Input ##
	3 2 10
	2 2 11
	1 2 11
	2 1 4
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 200002 1 1 1 1 1 -1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1

	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 100001 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 100002 -1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1

## Sample Output ##
	1 9
