# Hyperspace

## Description

The great Mr.Smith has invented a hyperspace particle generator. The device is very powerful. The device can generate a hyperspace. In the hyperspace, particle may appear and disappear randomly. At the same time a great amount of energy.

However, the device is in test phase, often in a unstable state. Mr.Smith worried that it may cause an explosion when testing it. The energy of the device is related to the maximum manhattan distance between particle.

Particle may appear and disappear any time. Mr.Smith wants to know the maxmium manhattan distance between particle when particle appears or disappears.

## Input

The input contains several test cases, terminated by EOF.

In each case: In the first line, there are two integer $q$(number of particle appear and disappear event) and $k$(dimensions of the hyperspace that the hyperspace the device generated).
Then follows $q$ lines. In each line, the first integer '$od$' represents the event: $od=0$ means this is an appear event. Then follows $k$ integer(with absolute value less then $4 \times 10^7$). $od=1$ means this is an disappear event. Follows a integer $p$ represents the disappeared particle appeared in the pth event.

## Output

Each test case should contains `q` lines. Each line contains a integer represents the maximum manhattan distance between particle.

## Sample Input

	10 2
	0 208 403
	0 371 -180
	1 2
	0 1069 -192
	0 418 -525
	1 5
	1 1
	0 2754 635
	0 -2491 961
	0 2954 -2516

## Sample Output

	0
	746
	0
	1456
	1456
	1456
	0
	2512
	5571
	8922
